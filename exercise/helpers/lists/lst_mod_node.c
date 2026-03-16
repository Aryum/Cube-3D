/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_mod_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:03:03 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:03:04 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	lst_mod_node(t_list **s, t_list *old, t_list *new, void (*d)(void *))
{
	t_list	*new_last;

	new_last = lst_last(new);
	if (*s == old)
		*s = new;
	else if (old->last != NULL)
	{
		new->last = old->last;
		old->last->next = new;
	}
	if (old->next != NULL)
	{
		new_last->next = old->next;
		old->next->last = new_last;
	}
	d(old->content);
	free(old);
}
