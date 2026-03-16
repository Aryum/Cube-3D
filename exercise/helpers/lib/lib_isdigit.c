/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_isdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:59:13 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 21:59:13 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_isdigit(int c)
{
	if (isclass(c, '0', '9'))
		return (2048);
	return (0);
}
