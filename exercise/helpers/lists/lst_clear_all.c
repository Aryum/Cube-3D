/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:02:36 by ricsanto          #+#    #+#             */
/*   Updated: 2026/04/13 11:40:24 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

static void	clear(t_list **current, void (*del)(void*))
{
	if ((**current).next != NULL)
		clear(&((**current).next), del);
	del((**current).content);
	free (*current);
}

void	lst_clear_all(t_list **lst, void (*del)(void*))
{
	if (lst != NULL && *lst != NULL && del != NULL)
	{
		clear(lst, del);
		*lst = NULL;
	}
}
