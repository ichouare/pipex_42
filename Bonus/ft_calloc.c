/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:10:23 by ichouare          #+#    #+#             */
/*   Updated: 2023/01/29 16:46:34 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_calloc(size_t number, size_t size)
{
	void			*arr;
	unsigned int	i;

	i = 0;
	arr = (malloc(size * number));
	if (!arr)
		return (NULL);
	ft_bzero(arr, (number * size));
	return (arr);
}
