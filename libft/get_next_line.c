/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:29:21 by njackson          #+#    #+#             */
/*   Updated: 2024/04/01 14:10:07 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_buf(int fd, char **sav);
char	*split_buf(char **buf, int fd);
char	*get_sav(char **buf, char *out, size_t nl);
char	*add_buf(char *s1, char *s2);

char	*get_next_line(int fd)
{
	char			**sav;
	char			*out;
	size_t			i;

	sav = get_sav_from_lst(fd);
	i = 0;
	while (!*sav || (*sav)[i] != '\n')
	{
		if (!*sav || !(*sav)[i])
		{
			out = read_buf(fd, sav);
			if (!out)
				break ;
			if (!*sav)
				*sav = out;
			else
				*sav = add_buf(*sav, out);
		}
		else
			i++;
	}
	if (*sav)
		return (split_buf(sav, fd));
	clean_sav_lst(fd);
	return (0);
}

char	*read_buf(int fd, char **sav)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (0);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buf);
		buf = 0;
	}
	else
		buf[bytes_read] = 0;
	if (bytes_read < 0)
	{
		free(*sav);
		*sav = 0;
	}
	return (buf);
}

char	*split_buf(char **buf, int fd)
{
	char	*out;
	size_t	len_out;

	len_out = 0;
	while (*buf && (*buf)[len_out])
	{
		if ((*buf)[len_out++] == '\n')
		{
			out = (char *)malloc((len_out + 1) * sizeof(char));
			if (!out)
				return (0);
			out[len_out] = '\0';
			out = get_sav(buf, out, len_out);
			return (out);
		}
	}
	out = *buf;
	*buf = 0;
	clean_sav_lst(fd);
	if (out && !*out)
	{
		free(out);
		return (0);
	}
	return (out);
}

char	*get_sav(char **buf, char *out, size_t nl)
{
	char	*sav;
	size_t	i;

	i = nl;
	while (i-- > 0)
		out[i] = (*buf)[i];
	i = nl;
	while ((*buf)[i])
		i++;
	sav = (char *)malloc((i - nl + 1) * sizeof(char));
	if (!sav)
	{
		free(out);
		return (0);
	}
	i = 0;
	while ((*buf)[nl])
		sav[i++] = (*buf)[nl++];
	sav[i] = '\0';
	free(*buf);
	*buf = sav;
	return (out);
}

char	*add_buf(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*out;

	if (!s2)
		return (s1);
	len = 0;
	while (s1[len])
		len++;
	i = 0;
	while (s2[i++])
		len++;
	out = (char *)malloc((len + 1) * sizeof(char));
	i = -1;
	while (s1[++i])
		out[i] = s1[i];
	j = 0;
	while (s2[j])
		out[i++] = s2[j++];
	out[i] = '\0';
	free(s1);
	free(s2);
	return (out);
}
