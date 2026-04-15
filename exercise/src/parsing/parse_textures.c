/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:34:23 by david             #+#    #+#             */
/*   Updated: 2026/04/15 21:06:54 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


bool give_value(t_main *main, size_t i, size_t j, t_dir dire)
{
	while(main->resorcers.file[i][j])
	{
		if (main->resorcers.file[i][j] != '	' && main->resorcers.file[i][j] != ' ')
			main->resorcers.dir[dire] = (main->resorcers.file[i], j, lib_strlen(main->resorcers.file[i])); 
		j++;
	}
}


void dir_value(t_main *main, size_t i, size_t j)
{
	if (lib_strncmp(main->resorcers.file[i][j], "NO", 3) && main->flags.NO == false)
	{
		give_value(main, i, j, dir_north);
		main->flags.NO = true;
		return;
	}
	if (lib_strncmp(main->resorcers.file[i][j], "SO", 3) && main->flags.SO == false)
	{
		give_value(main, i, j, dir_south);
		main->flags.SO = true;
		return;
	}
	if (lib_strncmp(main->resorcers.file[i][j], "WE", 3) && main->flags.WE == false)
	{
		give_value(main, i, j, dir_west);
		main->flags.WE = true;
		return;
	}
	if (lib_strncmp(main->resorcers.file[i][j], "EA", 3) && main->flags.EA == false)
	{
		give_value(main, i, j, dir_east);
		main->flags.EA = true;
		return;
	}
}

bool find_textures(t_main *main)
{
	size_t i;
	size_t j;
	bool flag;

	i = 0;
	while (main->resorcers.file[i])
	{
		j = 0;
		while(main->resorcers.file[i][j])
		{
			dir_value(main, i, j);
			j++;
		}
	}
	return(false);   
}

bool apply_textures(t_main *main)
{
	
}