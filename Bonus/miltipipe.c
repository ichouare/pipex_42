/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miltipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:16:13 by ichouare          #+#    #+#             */
/*   Updated: 2023/02/02 16:41:20 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	process_child(char **cmd, t_vars *vs, char **env, char **argv)
{
	char	**cmds;

	cmds = NULL;
	cmds = ft_split(cmd[vs->i], ' ');
	vs->agrs = path(cmds[0], vs->path);
	if (vs->i == 0)
		first_process(argv, vs->fds, &vs->fd1);
	else
		ft_dup(&vs->fds[(vs->i - 1) * 2], &vs->fds[(vs->i * 2) + 1]);
	close_fds(vs->fds, vs->num);
	execve (vs->agrs, cmds, env);
	ft_free(cmds);
	exit(0);
}

void	process_parent(char **argv, char **env, t_vars *vs, int *tab)
{
	char	**cmds;

	cmds = NULL;
	wait (NULL);
	cmds = ft_split(vs->cmd[vs->i], ' ');
	create_infile(argv, tab, &vs->fd2);
	ft_dup(&vs->fds[(vs->i - 1) * 2], &vs->fd2);
	close_fds(vs->fds, vs->num);
	execve(path(cmds[0], vs->path), cmds, env);
	ft_free (cmds);
	exit(0);
}

void	ft_multi_pipe(char **argv, char **cmd, char **env, int *tab)
{
	t_vars	vs;

	vs.num = (ft_number_cmd(cmd) - 1);
	vs.fds = malloc(sizeof(int) * (vs.num * 2));
	vs.envpath = ft_pathcmds(env);
	vs.path = ft_split(vs.envpath, ':');
	vs.i = -1;
	ft_pipe(vs.fds, vs.num);
	while (++vs.i < vs.num)
	{
		if (fork() == 0)
		{
			vs.fd1 = tab[1];
			process_child(cmd, &vs, env, argv);
			free_oned(vs.agrs, vs.envpath, vs.fds);
			ft_free(vs.path);
			ft_free(cmd);
		}
	}
	vs.cmd = cmd;
	process_parent (argv, env, &vs, tab);
	free_oned(vs.agrs, vs.envpath, vs.fds);
	ft_free(vs.path);
	ft_free(cmd);
}

void	check_or_create(char **argv, t_list *list, int *j, int argc)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp("here_doc", argv[1], 9) != 0)
	{
		list->fd = open(argv[1], O_RDONLY);
		if (list->fd == -1)
			exit(write(2, "Error open fd\n", 15));
	}
	else
		create_file(argv, list, j);
	list->cmds = ft_strjoin(argv[*j], ":");
	while (*j < (argc - 2))
	{
		tmp = list->cmds;
		list->cmds = ft_strjoin(list->cmds, argv[*j + 1]);
		free(tmp);
		tmp = list->cmds;
		list->cmds = ft_strjoin(list->cmds, ":");
		free(tmp);
		*j = *j + 1;
	}
}

int	main(int argc, char **argv, char **env)
{
	int		tab[2];
	t_list	list;
	int		j;

	j = 2;
	if (argc < 5 || env == NULL)
		exit (write(2, "env or argument not found\n", 26));
	check_or_create(argv, &list, &j, argc);
	list.cmd = ft_split(list.cmds, ':');
	tab[0] = argc;
	tab[1] = list.fd;
	ft_multi_pipe(argv, list.cmd, env, tab);
}
