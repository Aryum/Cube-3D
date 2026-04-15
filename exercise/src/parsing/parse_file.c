/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:50:35 by david             #+#    #+#             */
/*   Updated: 2026/04/15 18:08:44 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


bool file_to_list(t_main *main, char *map_name)
{ 
	int fd;
	t_list *tmp;
	t_list *list;
	t_gnl gnl;


	list = NULL;
	fd = open(map_name , O_RDONLY);
	while(1)
	{
		gnl = get_next_line(fd);
		if (gnl.failed)
			return(false);
		if (!gnl.line)
			break ;
		tmp = lst_new(gnl.line);
		if (!tmp)
			return(false);
		lst_add_back(&list, tmp);
	}
	main->resorcers.file = (char **)lst_to_arr(&list);
	return(main->resorcers.file != NULL);
}



bool parse(int ac, char **av)
{
    t_main main;
	
	memset(&main, 0, sizeof(t_main));
    if (ac == 2)
    {
        file_to_list(&main, av[1]);
		if (!map_chek(&main))
			return(false);
		return (true);
    }
	return (false);
}