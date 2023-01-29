/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:12:07 by ichouare          #+#    #+#             */
/*   Updated: 2023/01/29 18:28:04 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	first_process(char **argv, int *tab, int *fd1)
{
	*fd1 = open(argv[1], O_RDONLY | O_WRONLY | O_CREAT, 0777);
	if (*fd1 < 0)
		exit(0);
	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		dup2(*fd1, tab[1]);
	else
		dup2(*fd1, 0);
}

void	create_infile(char **argv, int *tab, int *fd2)
{
	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		*fd2 = open (argv[tab[0] - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		*fd2 = open (argv[tab[0] - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
}

void	ft_dup(int *first, int *second)
{
	dup2 (*first, 0);
	dup2 (*second, 1);
}

void	create_file(char *str, t_list *data, int *j)
{
	data->fd = open ("filetmp.txt", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (data->fd < 0)
		exit (0);
	data->line = get_next_line(0);
	while (ft_strcmp(data->line, str) != 0)
	{
		data->line = get_next_line(0);
		write (data->fd, data->line, ft_strlen(data->line));
		free (data->line);
	}
	*j = 3;
}

void	ft_pipe(int *fds, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pipe(fds + i * 2) < 0)
			exit (0);
		i++;
	}
}
