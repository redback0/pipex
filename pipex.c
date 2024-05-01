/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:37:27 by njackson          #+#    #+#             */
/*   Updated: 2024/05/01 15:25:01 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[])
{
	int		in_fd;
	char	*line;
	while (ac-- > 1)
	{
		in_fd = run_command(av[ac]);
		ft_putnbr_fd(1, in_fd);
		ft_putchar_fd(2, '\n');
		line = get_next_line(in_fd);
		while (line)
		{
			ft_printf(line);
			line = get_next_line(in_fd);
		}
	}
}

int	run_command(char *cmd)
{
	int		pipefd[2];
	char	**args;
	int		fd;
	int		signal;

	pipe(pipefd);
	if (fork() == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		args = ft_split(cmd, ' ');
		execve(args[0], args, NULL);
		perror("Error: ");
		exit(1);
	}
	else
	{
		fd = dup(pipefd[0]);
		close(pipefd[1]);
		close(pipefd[0]);
		waitpid(-1, &signal, 0);
		return (fd);
	}
}
