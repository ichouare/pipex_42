/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 11:42:27 by ichouare          #+#    #+#             */
/*   Updated: 2023/01/13 19:15:37 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}