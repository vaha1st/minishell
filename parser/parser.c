/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 22:47:59 by masharla          #+#    #+#             */
/*   Updated: 2021/05/22 22:01:05 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	retrieve_flags(t_cmd *cmd)
{
	char	*flags;

	if (!cmd->args[0] || cmd->args[0][0] == '-' || !cmd->args[1])
		return ;
	flags = ft_strdup("-");
	while (cmd->args[1] && cmd->args[1][0] == '-')
	{
		flags = ft_strjoin(flags, &cmd->args[1][1]);
		cmd->args = ft_arrdel_str(cmd->args, 1);
	}
	if (ft_strlen(flags) == 1)
	{
		free(flags);
		flags = NULL;
	}
	cmd->flags = flags;
}

static void	retrieve_next_arg(const char *str, t_cmd *cmd, int from, int to)
{
	char	*arg;
	int		arg_num;

	arg = ft_substr(str, from, to - from);
	arg_num = 0;
	while (cmd->args[arg_num])
		arg_num++;
	cmd->args = ft_arradd_str_mod(cmd->args, arg, arg_num);
}

static int	parse_redirects(char **line, t_cmd *tmp, int *i, char **env)
{

	while ((*line)[*i])
	{
		if (!ft_isspace((*line)[*i]))
		{
			if (non_valid_redirect(*line))
				return (-3);
			else if ((*line)[*i] == '>')
				*line = redirect_output(line, i, tmp, env);
			else if ((*line)[*i] == '<')
				*line = redirect_input(*line, i, tmp);
			if (!*line)
				return (-1);
		}
		(*i)++;
	}
	(*i)--;
	return (1);
}

static void	parse_symbols(char **line, char **env, t_cmd *cmd)
{
	int	i;
	int	start;

	i = 0;
	while (ft_isspace((*line)[i]))
		i++;
	start = i;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'')
			*line = single_quotes(*line, &i);
		else if ((*line)[i] == '"')
			*line = double_quotes(*line, env, &i);
		else if ((*line)[i] == '\\')
			*line = backslash(*line, &i);
		else if ((*line)[i] == '$')
			*line = dollar(*line, &i, env);
		else if ((*line)[i] == '>' || (*line)[i] == '<')
			parse_redirects(line, cmd, &i, env);
		if ((*line)[i++] && (!(*line)[i] || ft_isspace((*line)[i])))
		{
			retrieve_next_arg(*line, cmd, start, i);
			while (ft_isspace((*line)[i]))
				i++;
			start = i;
		}
	}
}

int	parser(char *command_line, char **env, t_cmd ***cmd)
{
	int		i;
	int		res;
	char	*line;
	t_cmd	*tmp;

	res = preparser(command_line);
	if (res <= 0)
		return (res);
	i = 0;
	while (!i || command_line[i - 1] == '|')
	{
		tmp = new_cmd();
		tmp->len = find_end(&command_line[i]);
		line = ft_substr(command_line, i, tmp->len);
		parse_symbols(&line, env, tmp);
//		if (parse_redirects(&line, tmp) < 0)
//			return (-1);
		if (command_line[i + tmp->len] == '|')
			tmp->len++;
		i += tmp->len;
		retrieve_flags(tmp);
		free(line);
		*cmd = ft_arrcmd_addelem(*cmd, tmp);
	}
	return (res);
}

//int	main(int argc, char **argv, char **env)
//{
//	t_cmd	**cmd = malloc(sizeof(cmd));
//	cmd[0] = NULL;
//
//	char *case0 = "  			1";
//	char *case1 = "echo co'mma'nd\"000\"\"00\\$00\"'brbrbr'";
//	char *case2 = "echo 12345\" я $USER	\"123 ; \";\" ls ;";
//	char *case3 = "echo $USER";
//	char *case4 = "ls -l -a arg1 arg2 ' ' \" ' \" arg3";
//	char *case5 = "echo \"$USER\"";
//	char *case6 = "echo -n $USER $USER";
//	char *case7 = "echo test > 1";
//	char *case8 = "echo test >&0";
//	char *case9 = "cat 1 < 2 >&1";
//	char *case10 = "echo test > $USER > 3";
//	char *case11 = "cat > 2\\>2";
//	char *case12 = "cat > $USER";
//	char *case13 = "echo > $USER";
//	char *case14 = "cat < 1";
//	char *case15 = "> 1 > 2";
//	char *case16 = "ls | cat";
//	char *case17 = "ls | cat -e | grep 1 ; cd parser";
//	char *case18 = "echo $?$USER";
//	char *case19 = "echo test ; echo test1 ;   echo test2";
//	char *case20 = "echo $?";
//
//
//	printf("%d\n", parser(case16, env, &cmd));
//
//	int i = -1;
//	while (cmd[++i])
//	{
//		printf("Element %d\n", i);
//		int j = -1;
//		while (cmd[i]->args[++j])
//			printf("arg[%d] = %s\n", j, cmd[i]->args[j]);
//		if (cmd[i]->flags)
//			printf("flags = %s\n", cmd[i]->flags);
//		printf("fd_from = %d\n", cmd[i]->fd_from);
//		printf("fd_to = %d\n", cmd[i]->fd_to);
//	}
//}
