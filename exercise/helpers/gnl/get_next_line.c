/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:55:55 by ricsanto          #+#    #+#             */
/*   Updated: 2026/04/13 12:56:04 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlp.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	ssize_t		readbytes;
	char		*ret;

	ret = malloc(1);
	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE < 1 || ret == NULL)
		return (h_updateret(&ret, NULL));
	ret[0] = '\0';
	readbytes = 0;
	if (!h_appendbuffer(&ret, buffer[fd]))
	{
		readbytes = read(fd, buffer[fd], BUFFER_SIZE);
		buffer[fd][readbytes] = '\0';
		while (readbytes > 0)
		{
			if (h_appendbuffer(&ret, buffer[fd]) || readbytes < BUFFER_SIZE)
				break ;
			readbytes = read(fd, buffer[fd], BUFFER_SIZE);
			buffer[fd][readbytes] = '\0';
		}
	}
	if (ret == NULL || ret[0] == '\0' || readbytes < 0)
		return (h_resetbuffer(buffer[fd], 1), h_updateret(&ret, NULL));
	else
		return (h_resetbuffer(buffer[fd], 0), ret);
}
