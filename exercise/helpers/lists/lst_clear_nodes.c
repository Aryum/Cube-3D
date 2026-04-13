/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:37:53 by ricsanto          #+#    #+#             */
/*   Updated: 2026/04/13 11:40:09 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

static void	clear(t_list **current)
{
	if ((**current).next != NULL)
		clear(&((**current).next));
	free (*current);
}

void	lst_clear_nodes(t_list **lst)
{
	if (lst != NULL && *lst != NULL)
	{
		clear(lst);
		*lst = NULL;
	}
}