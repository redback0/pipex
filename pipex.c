/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:37:27 by njackson          #+#    #+#             */
/*   Updated: 2024/05/01 19:13:48 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *ep[])
{
	int		in_fd;
	char	*line; // DEBUG
	char	**path;
	char	*tmp;
	int		i;

	path = 0;
	i = -1;
	while (ep[++i])
	{
		if (ft_strncmp(ep[i], "PATH=", 5) == 0)
		{
			path = ft_split(ep[i], ':');
			tmp = ft_substr(path[0], 5, ft_strlen(path[0]) - 5);
			free(path[0]);
			path[0] = tmp;
			break ;
		}
	}
	while (ac-- > 1)
	{
		in_fd = run_command(av[ac], path);
		ft_putnbr_fd(1, in_fd);
		ft_putchar_fd(2, '\n');
		line = get_next_line(in_fd);
		while (line)
		{
			ft_log(0, line);
			free(line);
			line = get_next_line(in_fd);
		}
	}
}

int	run_command(char *cmd, char **path)
{
	int		pipefd[2];
	char	**args;
	int		fd;

	args = 0;
	pipe(pipefd);
	if (fork() == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		args = ft_split(cmd, ' ');
		args[0] = find_command(args[0], path);
		execve(args[0], args, NULL);
		perror("Error: ");
		exit(1);
	}
	else
	{
		fd = dup(pipefd[0]);
		close(pipefd[1]);
		close(pipefd[0]);
		return (fd);
	}
}

char	*find_command(char *cmd, char **path)
{
	char	*check;
	char	*tmp;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	tmp = ft_strjoin("/", cmd);
	i = 0;
	while (path[i])
	{
		check = ft_strjoin(path[i++], tmp);
		if (access(check, F_OK) == 0)
		{
			free(tmp);
			free(cmd);
			return (check);
		}
		free(check);
	}
	free(tmp);
	return (cmd);
}
