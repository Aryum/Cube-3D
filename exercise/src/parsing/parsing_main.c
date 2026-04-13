/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:50:35 by david             #+#    #+#             */
/*   Updated: 2026/04/13 14:19:31 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


bool get_line(t_list **list, int fd)
{
	char *line;
	t_list *tmp;

	*line = get_next_line(fd);
	tmp = lst_new(line);
	if (!tmp)
		return(false);
	lst_add_back(list, tmp);
	return(true);
}

bool map_creator(t_main *main)
{ 
	int fd;
	char *line;
	t_list *tmp;
	t_list *list;

	list = NULL;
	fd = open("map.txt", O_RDONLY);
	while(1)
	{
		if (!get_line(&list, fd))
			return(false);
		
	}
	lst_to_arr(&list);
}


bool parse(int ac, char **av)
{
    t_main main;
	
	memset(&main, 0, sizeof(t_main));
    if (ac == 2)
    {
        map_creator(&main);
		if (!map_chek(&main))
			return(false);
		return (true);
    }
	return (false);
}