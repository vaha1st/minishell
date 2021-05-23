/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:18:26 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:18:28 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_environment(char *env, char **envp)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	while (env[len] != '=')
		if (!env[++len])
			return (-2);
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(env, envp[i], len) && envp[i][len] == '=')
			return (i);
	return (-1);
}

void	ft_export(t_cmd *cmd, char *(**envp))
{
	char	**tmp;
	int	 size;
	int		i;
	int		res;

	i = 0;
	if (!cmd->args[0])
	{
		size = ft_arrsize(*envp);
		tmp = (char **)malloc(sizeof(*envp) * (size + 1));
		ft_arrcpy(tmp, *envp);
		ft_qsort_s(tmp, 0, ft_arrsize(tmp) - 1);
		size = 0;
		while (tmp[size])
			printf("%s\n", tmp[size++]);
	}
	else
	{
		while (cmd->args[i])
		{
			res = find_environment(cmd->args[i], *envp);
			if (res >= 0)
				ft_strcpy((*envp)[res], cmd->args[i]); // ft_strcpy is a bad
			else if (res == -1)
				*envp = ft_arradd_str(*envp, cmd->args[i], ft_arrsize(*envp) - 1);
			i++;
		}
	}
}
