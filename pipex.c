/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:37:27 by njackson          #+#    #+#             */
/*   Updated: 2024/05/08 17:59:05 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *ep[])
{
	int		pfd;
	int		outfd;
	char	**path;

	if (ac < 5)
	{
		ft_printf_fd(2, "USAGE: ./pipex {INFILE CMD [CMDS...] CMD OUTFILE}\n");
		return (1);
	}
	pfd = open(av[1], O_RDONLY);
	outfd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pfd < 0)
		ft_printf_fd(2, "%s: %s\n", strerror(errno), av[1]);
	path = get_path(ep);
	pfd = run_all_commands(ac, av, pfd, path);
	if (pfd >= 0)
		output_to_file(pfd, outfd);
	close(outfd);
	ft_split_free(path, *free);
}

int	run_all_commands(int ac, char **av, int pfd, char **path)
{
	int	i;
	int	npfd;
	int	status;

	i = 2;
	while (i < ac - 1 && pfd >= 0)
	{
		npfd = run_command(av[i], pfd, path);
		close(pfd);
		pfd = npfd;
		i++;
		wait(&status);
	}
	return (pfd);
}

int	run_command(char *cmd, int infd, char **path)
{
	int	pipefd[2];
	int	fd;
	int	signal;

	pipe(pipefd);
	if (fork() == 0)
		run_command_child(cmd, pipefd, infd, path);
	fd = dup(pipefd[0]);
	close(pipefd[1]);
	close(pipefd[0]);
	wait(&signal);
	return (fd);
}

char	*find_command(char *cmd, char **path)
{
	char	*check;
	char	*tmp;
	int		i;

	if (ft_strncmp(cmd, "./", 2) == 0 && access(cmd, F_OK) == 0)
		return (cmd);
	else
	{
		tmp = ft_strjoin("/", cmd);
		i = 0;
		while (path[i])
		{
			check = ft_strjoin(path[i++], tmp);
			if (access(check, F_OK) == 0)
			{
				free(tmp);
				return (check);
			}
			free(check);
		}
		free(tmp);
		return (0);
	}
}

void	output_to_file(int infd, int outfd)
{
	char	*line;

	line = get_next_line(infd);
	while (line)
	{
		write(outfd, line, ft_strlen(line));
		free(line);
		line = get_next_line(infd);
	}
}
