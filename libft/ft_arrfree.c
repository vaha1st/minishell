/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etorren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 15:05:53 by etorren           #+#    #+#             */
/*   Updated: 2021/05/23 15:07:35 by etorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrfree(char **arr)
{
	int	i;
	int	size;

	i = 0;
	size = ft_arrsize(arr);
	while (i < size)
		free(arr[i++]);
	free(arr);
}
