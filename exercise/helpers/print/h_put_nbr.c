/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_put_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:03:53 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:03:55 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	h_put_int(t_buf *b, int n, int *counter)
{
	int	correction;

	correction = 0;
	if (n < 0)
	{
		h_put_char(b, '-', counter);
		if (n == -2147483648)
			correction = 1;
		n = -1 * (n + correction);
	}
	if (n > 9)
		h_put_int(b, n / 10, counter);
	h_put_char(b, n % 10 + '0' + correction, counter);
}

void	h_put_uint(t_buf *b, unsigned int i, int *counter)
{
	if (i > 9)
		h_put_uint(b, i / 10, counter);
	h_put_char(b, i % 10 + '0', counter);
}
