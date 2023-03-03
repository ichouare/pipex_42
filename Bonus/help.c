/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:37:56 by ichouare          #+#    #+#             */
/*   Updated: 2023/01/31 12:40:45 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_number_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i++;
	}
	return (i);
}

void	close_fds(int *fds, int num)
{
	int	i;

	i = 0;
	while (i < (num * 2))
	{
		close (fds[i]);
		i++;
	}
}

char	*path(char *cmd, char **tabcmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	while (tabcmd[i])
	{
		if (access (cmd, X_OK | F_OK) == 0)
			return (cmd);
		tmp = ft_strjoin(tabcmd[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access (path, X_OK | F_OK) == 0)
			return (path);
		free(path);
	i++;
	}
	write(2, "cmd : not found\n", 16);
	return (NULL);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
	str = NULL;
}
