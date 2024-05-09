/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:51:42 by njackson          #+#    #+#             */
/*   Updated: 2024/05/09 17:13:12 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_here_doc(int *pipefd, char *limiter)
{
	int		len;
	char	*line;

	close(pipefd[0]);
	len = ft_strlen(limiter);
	ft_printf_fd(1, "> ");
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, limiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			exit(0);
		}
		ft_printf_fd(pipefd[1], line);
		free(line);
		ft_printf_fd(1, "> ");
		line = get_next_line(0);
	}
	ft_printf_fd(2, HERE_DOC_ERR, limiter);
	exit(1);
}
