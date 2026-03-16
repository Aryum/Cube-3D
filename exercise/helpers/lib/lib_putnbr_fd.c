/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_putnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:00:00 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:00:03 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	print_nbr(int n, int fd)
{
	int		correction;
	char	c;

	correction = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
			correction = 1;
		n = -1 * (n + correction);
	}
	if (n > 9)
		print_nbr(n / 10, fd);
	c = n % 10 + '0' + correction;
	write(fd, &c, 1);
}

void	lib_putnbr_fd(int n, int fd)
{
	if (fd >= 0)
		print_nbr(n, fd);
}
