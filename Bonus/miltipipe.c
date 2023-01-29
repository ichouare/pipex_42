/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miltipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:16:13 by ichouare          #+#    #+#             */
/*   Updated: 2023/01/29 18:49:04 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*path(char *cmd, char **tabcmd)
{
	int		i;
	char	*path;

	i = 0;
	while (tabcmd[i])
	{
		path = ft_strjoin(tabcmd[i], "/");
		path = ft_strjoin(path, cmd);
		if (access (path, F_OK) == 0)
			return (path);
	i++;
	}
	return (NULL);
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

void	ft_multi_pipe(char **argv, char **cmd, char **env, int *tab)
{
	t_vars	vs;

	vs.num = (ft_number_cmd(cmd) - 1);
	vs.fds = malloc(sizeof(int) * (vs.num * 2));
	vs.path = ft_split(env[6], ':');
	vs.i = -1;
	ft_pipe(vs.fds, vs.num);
	while (++vs.i < vs.num)
	{
		if (fork() == 0)
		{
			if (vs.i == 0)
				first_process(argv, tab, &vs.fd1);
			ft_dup(&vs.fds[(vs.i - 1) * 2], &vs.fds[(vs.i * 2) + 1]);
			close_fds(vs.fds, vs.num);
			execve (path(ft_split(cmd[vs.i], ' ')[0], vs.path), 
				ft_split(cmd[vs.i], ' '), env);
		}
	}
	wait (NULL);
	create_infile(argv, tab, &vs.fd2);
	ft_dup(&vs.fds[(vs.i - 1) * 2], &vs.fd2);
	close_fds(vs.fds, vs.num);
	execve(path(ft_split(cmd[vs.i], ' ')[0], vs.path),
		ft_split(cmd[vs.i], ' '), env);
}

int	main(int argc, char **argv, char **env)
{
	int		tab[2];
	t_list	list;
	int		j;

	j = 2;
	if (argc < 5)
		return (0);
	if (ft_strncmp("here_doc", argv[1], 9) == 0)
		create_file(argv[2], &list, &j);
	list.cmds = ft_strjoin(argv[j], ":");
	while (j < (argc - 2))
	{
		list.cmds = ft_strjoin(list.cmds, argv[j + 1]);
		list.cmds = ft_strjoin(list.cmds, ":");
		j++;
	}
	list.cmd = ft_split(list.cmds, ':');
	tab[0] = argc;
	tab[1] = list.fd;
	ft_multi_pipe(argv, list.cmd, env, tab);
}
