/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichouare <ichouare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:21:45 by ichouare          #+#    #+#             */
/*   Updated: 2023/01/29 18:43:36 by ichouare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

typedef struct vars
{
	int		fd1;
	int		i;
	int		fd2;
	char	**path;
	int		num;
	char	**pathcmd;
	int		*fds;
}	t_vars;

typedef struct list
{
	char	*line;
	char	*cmds;
	char	**cmd;
	int		fd;
}	t_list;

typedef struct mandatory
{
	int		id;
	char	**pathcmd;
	char	*path;
	int		*fd;
	int		ff2;
	int		ff;
	char	*cmd;
}	t_man;
void	first_process(char **argv, int *tab, int *fd1);
void	create_infile(char **argv, int *tab, int *fd2);
void	ft_dup(int *first, int *second);
void	ft_pipe(int *fds, int num);
void	create_file(char *str, t_list *data, int *j);
void	*ft_calloc(size_t number, size_t size);
void	ft_bzero(void *s, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
int		ft_strncmp(char *p1, char *p2, int len);
int		ft_strcmp( char *p1, char *p2);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	found_nl(const char *str, int c);
#endif
