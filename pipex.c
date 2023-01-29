/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:42:51 by ichouare          #+#    #+#             */
/*   Updated: 2023/01/29 16:26:29 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

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

void	child(t_man *vars, char **argv, char **env)
{
	vars->cmd = path(ft_split(argv[2], ' ')[0], vars->pathcmd);
	dup2(vars->fd[1], 1);
	close (vars->fd[0]);
	close (vars->fd[1]);
	execve (vars->cmd, ft_split(argv[2], ' '), env);
	exit (1);
}

void	parent(t_man *vars, char **argv, char **env)
{
	waitpid (vars->id, NULL, 0);
	vars->cmd = path(ft_split(argv[3], ' ')[0], vars->pathcmd);
	vars->ff2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (vars->ff < 0)
		exit (0);
	dup2 (vars->fd[0], 0);
	dup2 (vars->ff2, 1);
	close (vars->fd[0]);
	close (vars->fd[1]);
	execve (vars->cmd, ft_split(argv[3], ' '), env);
}

int	main(int argc, char **argv, char **env)
{
	t_man	vars;

	vars.fd = malloc (sizeof(int) * 2);
	if (argc != 5)
		exit (0);
	else
	{
		vars.pathcmd = ft_split(env[6], ':');
		vars.path = ft_split(argv[2], ' ')[0];
		if (pipe(vars.fd) < 0)
			exit (0);
		vars.id = fork();
		if (vars.id < 0)
			exit(0);
		vars.ff = open(argv[1], O_RDONLY | O_CREAT, 0777);
		if (vars.ff < 0)
			exit(0);
		vars.cmd = path(ft_split(argv[2], ' ')[0], vars.pathcmd);
		dup2(vars.ff, 0);
		if (vars.id == 0)
			child(&vars, argv, env);
		else
			parent(&vars, argv, env);
		return (0);
	}
}
