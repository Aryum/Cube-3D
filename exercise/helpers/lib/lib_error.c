/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:58:31 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 21:58:35 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	lib_error(char *str)
{
	lib_putstr_fd("Error: ", 2);
	lib_putstr_fd(str, 2);
	lib_putstr_fd("\n", 2);
}
