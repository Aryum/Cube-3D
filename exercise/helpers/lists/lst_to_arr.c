/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:03:11 by ricsanto          #+#    #+#             */
/*   Updated: 2025/12/12 22:03:13 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	**lst_to_arr(t_list *lst)
{
	void	**ret;
	int		i;
	int		size;

	size = lst_size(lst);
	ret = malloc((size + 1) * sizeof(void *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = lst->content;
		lst = lst->next;
		i++;
	}
	ret[size] = NULL;
	return (ret);
}
