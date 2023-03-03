/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:42:51 by ichouare          #+#    #+#             */
/*   Updated: 2023/02/03 15:23:28 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

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
	while (str[i] != NULL)
	{
		free (str[i]);
		i++;
	}
	free (str);
	str = NULL;
}

void	child(t_man *vars, char **argv, char **env, char *pathenv)
{
	char	**splt;

	splt = ft_split(argv[2], ' ');
	vars->pathcmd = ft_split(pathenv, ':');
	vars->cmd = path(splt[0], vars->pathcmd);
	ft_free(vars->pathcmd);
	dup2(vars->fd[1], 1);
	close (vars->fd[0]);
	close (vars->fd[1]);
	execve (vars->cmd, splt, env);
	free (vars->cmd);
	ft_free(splt);
	free(vars->fd);
	exit(0);
}

void	parent(t_man *vars, char **argv, char **env, char *pathenv)
{
	char	**cmd;

	wait(NULL);
	vars->pathcmd = ft_split(pathenv, ':');
	cmd = ft_split(argv[3], ' ');
	vars->cmd = path(cmd[0], vars->pathcmd);
	vars->ff2 = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (vars->ff2 < 0)
		exit (0);
	dup2 (vars->fd[0], 0);
	dup2 (vars->ff2, 1);
	close (vars->fd[0]);
	close (vars->fd[1]);
	execve (vars->cmd, cmd, env);
	ft_free(cmd);
	ft_free (vars->pathcmd);
	free (vars->cmd);
	free(vars->fd);
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	t_man	vars;

	if (argc != 5 || env == NULL)
		exit (write(2, "env or argument not found\n", 26));
	vars.fd = malloc(sizeof(int) * 2);
	if (vars.fd == NULL)
		exit (1);
	if (pipe (vars.fd) < 0)
		exit (0);
	vars.ff = open(argv[1], O_RDONLY);
	if (vars.ff == -1)
		exit(write(2, "Eroor : fd not found\n", 21));
	dup2(vars.ff, 0);
	vars.envcmds = ft_pathcmds(env);
	vars.id = fork();
	if (vars.id < 0)
		exit(0);
	if (vars.id == 0)
		child(&vars, argv, env, vars.envcmds);
	else
		parent(&vars, argv, env, vars.envcmds);
	return (0);
}
