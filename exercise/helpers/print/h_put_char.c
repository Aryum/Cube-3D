/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_put_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:03:48 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:03:50 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	h_put_char(t_buf *b, int c, int *counter)
{
	if (*counter != -1)
		(*counter) += 1;
	b->str[b->count] = c;
	b->count++;
	if (c == '\n' || b->count == 1024)
		h_put_buf(b);
}
