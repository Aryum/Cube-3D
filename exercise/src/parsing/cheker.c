/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:49:10 by david             #+#    #+#             */
/*   Updated: 2026/03/26 16:39:51 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool charecter_chek(t_main *main)
{
    int i;
	int j;

    i = 0;
	j = 0;
    while(main->resorcers.file[i])
    {
		j = 0;
		while(main->resorcers.file[i][j])
		{
			if (!lib_ischar(main->resorcers.file[i][j], "NSEW10", 0) 
				&& main->resorcers.file[i][j] != ' ' && main->resorcers.file[i][j] != '	')
				return(false);
			j++;
		}
        i++;
    }
    return(true);
}



void trim_map(t_main *main)
{
	size_t i;

	i = 0;
	while(main->resorcers.file[i])
	{
		
	}
}
