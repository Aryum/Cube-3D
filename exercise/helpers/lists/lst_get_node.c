/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:02:46 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:02:47 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_list	*lst_get_node(t_list *lst, void *content, int (*func)(void *, void *))
{
	while (lst != NULL)
	{
		if (func(content, lst->content))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
