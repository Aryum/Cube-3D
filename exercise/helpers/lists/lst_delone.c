/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:02:41 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:02:42 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	lst_delone(t_list **start, t_list *node, void (*del)(void*))
{
	if (start != NULL && *start != NULL && node != NULL && del != NULL)
	{
		if (*start == node)
			*start = (**start).next;
		if (node->last != NULL)
			node->last->next = node->next;
		if (node->next != NULL)
			node->next->last = node->last;
		del(node->content);
		free (node);
	}
}
