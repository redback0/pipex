/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:09:04 by njackson          #+#    #+#             */
/*   Updated: 2024/04/30 16:20:48 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_log(int level, const char *format, ...)
{
	va_list	args;
	int		fd;

	if (level >= LOGERROR)
		fd = 2;
	else if (level >= LOGLEVEL)
		fd = 1;
	else
		return (0);
	return (ft_printf_args(fd, format, args));
}
