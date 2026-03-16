/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_put_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:04:01 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:04:03 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	h_put_ptr(t_buf *b, void *ptr, int *counter)
{
	if (ptr == NULL)
		h_put_str(b, "(nil)", counter);
	else
	{
		h_put_str(b, "0x", counter);
		h_put_ulongbase(b, (unsigned long)ptr, "0123456789abcdef", counter);
	}
}
