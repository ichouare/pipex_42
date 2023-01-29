/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextLine_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:41:40 by ichouare          #+#    #+#             */
/*   Updated: 2023/01/29 16:39:09 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	found_nl(const char *str, int c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != (char)c)
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	i;
	int		size;

	arr = NULL;
	i = 0;
	if (!s)
		return (NULL);
	if (found_nl(s, '\0') > len)
		size = len;
	else
		size = found_nl(s, '\0') - start;
	arr = (char *)(malloc(sizeof(char) * (size + 1)));
	if (!arr)
		return (NULL);
	while (size--)
	{
		*(arr + i) = *(s + start + i);
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

//fucntion strchr for '\n
char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (char)c)
	{
		if (!*s)
			return (0);
		s++;
	}
	return (s);
}
