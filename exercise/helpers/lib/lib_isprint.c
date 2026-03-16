/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_isprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:59:17 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 21:59:17 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_isprint(int c)
{
	if (isclass(c, 32, 126))
		return (16384);
	return (0);
}
