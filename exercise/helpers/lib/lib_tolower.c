/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tolower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:01:46 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:01:46 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	isclass(int c, int lower, int upper)
{
	return (c >= lower && c <= upper);
}

int	lib_tolower(int c)
{
	if (isclass(c, 'A', 'Z'))
		return (c + 32);
	return (c);
}
