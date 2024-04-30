/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42adel.o>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:37:27 by njackson          #+#    #+#             */
/*   Updated: 2024/05/01 03:59:47 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"

int	main(void)
{
	char *args[] = {"/bin/ls", 0};
	char *env[] = {"PATH=/bin", 0};
	pid_t	child;
	int		status;

	child = fork();
	if (child == 0)
	{
		execve(args[0], args, env);
		perror("ERROR: ");
	}
	else
	{
		ft_printf("<PARENT> Forked\n");
		waitpid(-1, &status, 0);
	}
}
