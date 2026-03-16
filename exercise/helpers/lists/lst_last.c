/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:02:54 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:02:55 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_list	*lst_last(t_list *lst)
{
	if (lst != NULL)
	{
		while ((*lst).next != NULL)
			lst = (*lst).next;
	}
	return (lst);
}
