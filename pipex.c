/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:37:27 by njackson          #+#    #+#             */
/*   Updated: 2024/05/01 17:15:03 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *env[])
{
	int		in_fd;
	char	*line;
	int		i;

	i = -1;
	while (env[++i])
	{
		//ft_putendl_fd(env[i], 2);
	}
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

	args = 0;
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
		wait(&signal);
		ft_printf("test\n");
		ft_log(3, "%p\n", args);
		return (fd);
	}
}
