/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:18:19 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 21:18:20 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	options_exit(t_cmd *cmd, t_rl *rl)
{
	int	status;

	status = ft_atoi(cmd->args[1]);
	if (status && cmd->args[2])
	{
		put_error("minishell: ", cmd->args[0], NULL,
			"too many arguments");
		rl->status = 1;
	}
	else if (!status)
	{
		put_error("minishell: ", cmd->args[0], cmd->args[1],
			"numeric argument required");
		clear_exit(rl);
		exit(255);
	}
	else
	{
		clear_exit(rl);
		exit(status);
	}
}

void	ft_exit(t_cmd *cmd, t_rl *rl)
{
	if (!cmd->args[1])
	{
		clear_exit(rl);
		exit(0);
	}
	else
		options_exit(cmd, rl);
}
