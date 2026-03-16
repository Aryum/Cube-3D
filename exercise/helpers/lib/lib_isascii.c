/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_isascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:58:54 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 21:58:54 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_isascii(int c)
{
	if (isclass(c, 0, 127))
		return (1);
	return (0);
}
