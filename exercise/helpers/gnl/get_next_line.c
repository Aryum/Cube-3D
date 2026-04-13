/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:55:55 by ricsanto          #+#    #+#             */
/*   Updated: 2026/04/13 14:39:23 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlp.h"

static t_gnl	clean_ret(t_gnl *ret, bool failed)
{
	h_updateline(ret, NULL, failed);
	return (*ret);
}

static t_gnl	ini_gnl(void)
{
	t_gnl	ret;

	ret.line = malloc(1);
	ret.failed = ret.line == NULL;
	if (!ret.failed)
		ret.line[0] = '\0';
	return (ret);
}

t_gnl	get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	ssize_t		readbytes;
	t_gnl		ret;

	ret = ini_gnl();
	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE < 1 || ret.failed)
		return (clean_ret(&ret, true));
	readbytes = 0;
	if (!h_appendbuffer(&ret, buffer[fd]))
	{
		readbytes = read(fd, buffer[fd], BUFFER_SIZE);
		while (readbytes >= 0)
		{
			buffer[fd][readbytes] = '\0';
			if (h_appendbuffer(&ret, buffer[fd]) || readbytes < BUFFER_SIZE)
				break ;
			readbytes = read(fd, buffer[fd], BUFFER_SIZE);
			buffer[fd][readbytes] = '\0';
		}
	}
	if (ret.line == NULL || ret.line[0] == '\0' || readbytes < 0)
		return (h_resetbuffer(buffer[fd], 1), clean_ret(&ret, readbytes < 0));
	else
		return (h_resetbuffer(buffer[fd], 0), ret);
}
