/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:41:39 by njackson          #+#    #+#             */
/*   Updated: 2024/04/01 14:10:23 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_sav_lst(int fd);
t_sav	*new_sav(int fd);
t_sav	*add_sav_end(t_sav *new, t_sav **lst);

t_sav	**get_sav_lst(void)
{
	static t_sav	*lst;

	return (&lst);
}

char	**get_sav_from_lst(int fd)
{
	t_sav	**lst;
	t_sav	*sav;

	lst = get_sav_lst();
	if (!*lst)
		return (&(add_sav_end(new_sav(fd), lst)->buf));
	sav = *lst;
	while (!sav || sav->fd != fd)
	{
		if (!sav)
			return (&(add_sav_end(new_sav(fd), lst)->buf));
		sav = sav->next;
	}
	return (&(sav->buf));
}

void	clean_sav_lst(int fd)
{
	t_sav	**lst;
	t_sav	*prev;
	t_sav	*ptr;

	lst = get_sav_lst();
	ptr = *lst;
	prev = 0;
	while (ptr && ptr->fd != fd)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (!ptr)
		return ;
	if (ptr->buf && !*(ptr->buf))
		return ;
	if (!prev)
		*lst = ptr->next;
	else
		prev->next = ptr->next;
	free(ptr);
	return ;
}

t_sav	*new_sav(int fd)
{
	t_sav	*sav;

	sav = (t_sav *)malloc(sizeof(*sav));
	if (!sav)
		return (0);
	sav->next = 0;
	sav->buf = 0;
	sav->fd = fd;
	return (sav);
}

t_sav	*add_sav_end(t_sav *new, t_sav **lst)
{
	t_sav	*ptr;

	if (!*lst)
	{
		*lst = new;
		return (new);
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	return (new);
}
