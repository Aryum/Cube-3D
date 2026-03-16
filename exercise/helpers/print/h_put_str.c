/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_put_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:04:07 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:04:43 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static void	print_str(t_buf *b, char *str, int *counter)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		h_put_char(b, str[i], counter);
		i++;
	}
}

void	h_put_str(t_buf *b, char *str, int *counter)
{
	if (str != NULL)
		print_str(b, str, counter);
	else
		print_str(b, "(null)", counter);
}
