/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:13:09 by ricsanto          #+#    #+#             */
/*   Updated: 2026/04/13 12:55:33 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hlp.h"

static ssize_t	h_strlen(char *str)
{
	ssize_t	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != '\0' && str[i] != '\n')
			i++;
	}
	return (i);
}

int	h_appendbuffer(char **last, char *buffer)
{
	ssize_t	i;
	ssize_t	h;
	ssize_t	total_len;
	char	*retval;

	i = 0;
	h = h_strlen(buffer);
	total_len = h_strlen(*last) + h + (buffer[h] == '\n');
	retval = malloc(total_len + 1);
	if (retval == NULL)
		return (h_updateret(last, NULL), 1);
	while ((*last)[i] != '\0')
	{
		retval[i] = (*last)[i];
		i++;
	}
	h = 0;
	while (h + i < total_len)
	{
		retval[h + i] = buffer[h];
		h++;
	}
	retval[h + i] = '\0';
	h_updateret(last, retval);
	return (total_len != 0 && retval[h + i - 1] == '\n');
}

void	h_resetbuffer(char *buffer, int failed)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\0' && !failed)
	{
		if (buffer[i] == '\n' && buffer[i + 1] != '\0' && j == 0)
			j = i + 1;
		else if (j != 0)
			buffer[i - j] = buffer[i];
		i++;
	}
	if (j == 0 || failed)
		buffer[0] = '\0';
	buffer[i - j] = '\0';
}

char	*h_updateret(char **last, char *updated)
{
	if (last != NULL && *last != NULL)
	{
		free(*last);
		*last = updated;
		return (*last);
	}
	return (NULL);
}
