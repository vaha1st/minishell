/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:17:12 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:17:43 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/processor.h"

static void	get_paths(char *path, char *bin, char *(**temp))
{
	int		i;
	int		prev;
	char	*sub;

	i = -1;
	prev = 0;
	while (path[++i])
	{
		if (path[i] == ':')
		{
			path[i++] = '/';
			sub = ft_substr(path, prev, i - prev);
			sub = ft_strjoin(sub, bin);
			prev = i;
			(*temp) = ft_arradd_str_mod((*temp), sub, ft_arrsize(*temp));
		}
	}
	path[i++] = '/';
	sub = ft_substr(path, prev, i - prev);
	sub = ft_strjoin(sub, bin);
	prev = i;
	(*temp) = ft_arradd_str_mod((*temp), sub, ft_arrsize(*temp));
	free(path);
}

static void	subprocess(t_cmd *cmd, char **envp)
{
	char	**temp;
	int		ret;
	int		j;

	dup2(cmd->fd_to, 1);
	dup2(cmd->fd_from, 0);
	temp = malloc(sizeof(temp) * 2);
	temp[0] = malloc(ft_strlen(cmd->args[0]) + 1);
	temp[1] = NULL;
	ft_strcpy(temp[0], cmd->args[0]);
	ret = find_environment("PATH", envp);
	if (ret != -1)
		get_paths(ft_strdup(&envp[ret][5]), cmd->args[0], &temp);
	j = 0;
	while (temp[j] && execve(temp[j], cmd->args, envp) == -1 )
		j++;
	if (!temp[j])
	{
		put_error("minishell: ", cmd->args[0], NULL, "command not found");
		ft_arrfree(temp);
		exit(127);
	}
	ft_arrfree(temp);
}

static void	binary_cmd(t_cmd *cmd, t_rl *rl, char **envp)
{
	pid_t	pid;

	pid = fork();
	signal(SIGQUIT, print_ouit);
	signal(SIGINT, ctrl_c_handler);
	if (cmd->flags)
		cmd->args = ft_arradd_str(cmd->args, cmd->flags, 1);
	if (pid == 0)
		subprocess(cmd, envp);
	else if (pid == -1)
	{
		ft_putendl_fd("pid_error", 2);
		rl->status = 1;
	}
	else
	{
		waitpid(pid, &rl->status, 0);
		if (cmd->fd_to > 1)
			close(cmd->fd_to);
		if (cmd->fd_from > 1)
			close(cmd->fd_from);
		if (rl->status == 3 || rl->status == 2)
			rl->status += 128;
	}
}

void	processor(t_cmd *cmd, char *(**envp), t_rl *rl)
{
	if (!cmd->args[0])
		return ;
	if (!ft_strcmp(cmd->args[0], "echo"))
		rl->status = ft_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		rl->status = ft_pwd(cmd->fd_to);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		rl->status = ft_cd(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "env"))
		rl->status = ft_env(cmd, *envp);
	else if (!ft_strcmp(cmd->args[0], "export"))
		rl->status = ft_export(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		rl->status = ft_unset(cmd, envp);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd, rl);
	else
		binary_cmd(cmd, rl, *envp);
	if (rl->status > 255)
		rl->status /= 256;
}
