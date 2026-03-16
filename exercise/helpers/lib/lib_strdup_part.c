/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_strdup_part.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:00:20 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:00:22 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*lib_strdup_part(char *str, size_t start, size_t end)
{
	size_t	delta;
	size_t	i;
	char	*ret;

	i = 0;
	delta = end - start;
	ret = lib_calloc(delta + 1, sizeof(char));
	if (ret != NULL)
	{
		while (start + i < end)
		{
			ret[i] = str[start + i];
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}
