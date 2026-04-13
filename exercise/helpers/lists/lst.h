/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:03:30 by ricsanto          #+#    #+#             */
/*   Updated: 2026/04/13 11:54:54 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*last;
}	t_list;

t_list	*lst_new(void *content);

t_list	*lst_map(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*lst_last(t_list *lst);

void	lst_iter(t_list *lst, void (*f)(void *));

void	lst_delone(t_list **start, t_list *node, void (*del)(void*));

void	lst_add_back(t_list **lst, t_list *new);

void	lst_add_front(t_list **lst, t_list *new);

void	lst_clear_all(t_list **lst, void (*del)(void*));

void	lst_clear_nodes(t_list **lst);

int		lst_size(t_list *lst);

t_list	*lst_get_node(t_list *lst, void *content, int (*func)(void *, void *));

void	**lst_to_arr(t_list **lst);

void	lst_mod_node(t_list **s, t_list *old, t_list *new, void (*d)(void *));

#endif