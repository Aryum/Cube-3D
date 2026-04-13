/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:02:58 by ricsanto          #+#    #+#             */
/*   Updated: 2026/04/13 11:53:21 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_list	*lst_map(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*cur_node;
	void	*cur_content;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	ret = NULL;
	while (lst != NULL)
	{
		cur_content = f((*lst).content);
		cur_node = lst_new(cur_content);
		if (cur_node == NULL)
		{
			del(cur_content);
			lst_clear_all(&ret, del);
			break ;
		}
		lst_add_back(&ret, cur_node);
		lst = ((*lst).next);
	}
	return (ret);
}
