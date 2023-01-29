/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnextLine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 11:34:10 by ichouare          #+#    #+#             */
/*   Updated: 2023/01/18 18:04:39 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

static char	*heandler_next_line(char **svr, char *line)
{
	char	*tmp;
	int		index;

	index = 0;
	if (found_nl(*svr, '\0') == 0)
	{
		free(*svr);
		*svr = NULL;
		return (NULL);
	}
	if (ft_strchr(*svr, '\n'))
	{
		index = found_nl(*svr, '\n');
		line = ft_substr(*svr, 0, index + 1);
		tmp = *svr;
		*svr = ft_substr(*svr, index + 1, found_nl(*svr, '\0') + 1);
		free(tmp);
	}
	else
	{
		line = ft_substr(*svr, 0, found_nl(*svr, '\0') + 1);
		free(*svr);
		*svr = NULL;
	}
	return (line);
}

static char	*handler_line( char **svr, char **buffer, int fd, int BUFFER_SIZE)
{
	char			*tmp;
	ssize_t			sz;

	sz = 1;
	while (ft_strchr(*svr, '\n') == NULL && sz != 0)
	{
		sz = read(fd, *buffer, BUFFER_SIZE);
		if (sz <= 0)
		{
			free(*buffer);
			free(*svr);
			exit(0);
		}
		tmp = *svr;
		*svr = ft_strjoin(*svr, *buffer);
		free(tmp);
		tmp = NULL;
		ft_bzero(*buffer, found_nl(*buffer, '\0') + 1);
	}
	return (*svr);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*svr;
	char		*line;
	int			buffer_size;

	line = NULL;
	buffer_size = 1;
	if (fd < 0 || buffer_size <= 0)
		return (NULL);
	buffer = ft_calloc(sizeof(char), buffer_size + 1);
	if (!buffer)
		return (NULL);
	if (!svr)
		svr = ft_substr(buffer, 0, found_nl(buffer, '\0'));
	svr = handler_line(&svr, &buffer, fd, buffer_size);
	if (!svr)
		return (NULL);
	free(buffer);
	return (heandler_next_line(&svr, line));
}
