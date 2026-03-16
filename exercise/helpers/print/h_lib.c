/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_lib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:03:36 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:03:39 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

int	h_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
			i++;
	}
	return (i);
}

void	*h_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (char)c;
		i++;
	}
	return (s);
}

void	h_put_buf(t_buf *b)
{
	write(b->fd, b->str, b->count);
	h_memset(b->str, 0, 1024);
	b->count = 0;
}
