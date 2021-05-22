/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masharla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:15:58 by masharla          #+#    #+#             */
/*   Updated: 2021/05/22 16:16:44 by ruslan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *prefix, char *body, char *postfix);
char	*backslash(char *str, int *i);
char	*single_quotes(char *str, int *i);
char	*double_quotes(char *str, int *i);
