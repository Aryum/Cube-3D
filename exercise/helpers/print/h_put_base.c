/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_put_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:03:43 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:03:44 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static int	is_base_valid(t_base *base, char *str)
{
	int	i;
	int	j;

	if (str == NULL)
		return (0);
	i = 0;
	j = 1;
	while (str[i] != '\0')
	{
		j = 1;
		while (str[i + j] != '\0')
		{
			if (str[i] == str[i + j])
				return (0);
			if ((str[i] > 8 && str[i] <= '\r') || str[i] == ' ')
				return (0);
			j++;
		}
		i++;
	}
	base->size = i;
	base->str = str;
	return (1);
}

static void	print_base(t_buf *b, unsigned long nbr, t_base base, int *c)
{
	if (nbr / base.size != 0)
		print_base(b, nbr / base.size, base, c);
	h_put_char(b, base.str[nbr % base.size], c);
}

void	h_put_ulongbase(t_buf *b, unsigned long nbr, char *str, int *counter)
{
	t_base	base;

	if (is_base_valid(&base, str))
		print_base(b, nbr, base, counter);
}

void	h_put_uintbase(t_buf *b, unsigned int nbr, char *str, int *counter)
{
	t_base	base;

	if (is_base_valid(&base, str))
		print_base(b, nbr, base, counter);
}
