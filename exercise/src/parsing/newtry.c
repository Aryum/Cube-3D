/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newtry.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:52:02 by david             #+#    #+#             */
/*   Updated: 2026/04/13 12:44:14 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


bool find_end_map_helper(t_main *main, size_t i, size_t j)
{
	while (main->resorcers.file[i][j])
	{
		if (main->resorcers.file[i][j + 1] == '\0')
				return(true);
		if (main->resorcers.file[i][j] != '1')
		{
			if (main->resorcers.file[i][j + 1] == '\0')
				return(true);
			if ((main->resorcers.file[i][j] != '	' && main->resorcers.file[i][j] != ' ' ))
				return(false);
		}
		j++;
	}
	return(false);
}




bool only_wspaces(t_main *main, size_t i)
{
	size_t j;

	while (main->resorcers.file[i + 1])
	{
		j = 0;
		while (main->resorcers.file[i + 1][j])
		{
			if (main->resorcers.file[i + 1][j] != '	' && main->resorcers.file[i + 1][j] != ' ')
				return(false);
			j++;
		}
		i++;
	}
	return(true);
}

void find_end_map(t_main *main, size_t i,  size_t j)
{

	while(main->resorcers.file[i])
	{
		j = 0;
		while (main->resorcers.file[i][j])
		{
			if (main->resorcers.file[i][j] == '1' && !only_wspaces(main, i))
				break;
			if (main->resorcers.file[i][j] == '1' && find_end_map_helper(main, i, j))
			{
				main->resorcers.end_map = i;
				return;
			}
			j++;
		}
		i++;
	}
}

bool find_map(t_main *main)
{
	size_t i;
	size_t j;
	bool map_flag;

	i = 0;
	map_flag = true;
	while(main->resorcers.file[i])
	{
		j = 0;
		map_flag = true;
		while(main->resorcers.file[i][j])
		{
			if ((main->resorcers.file[i][j] == '1' || main->resorcers.file[i][j] == '0') && map_flag == true)
			{
				main->resorcers.y = i;
				main->resorcers.x = j;
				find_end_map(main, i, j);
				return (true);
			}
			else if (main->resorcers.file[i][j] != ' ' && main->resorcers.file[i][j] != '	')
				map_flag = false;
			j++;
		}
		i++;
	}
	return(false);
}

void update_lower(t_main *main, size_t i, size_t j)
{
	if (main->resorcers.file[i][j] == '1')
	{
		if (j <= main->resorcers.lower_x)
			main->resorcers.lower_x = j;
	}
}

bool first_row(t_main *main)
{
	size_t i;
	size_t j;
	
	i = main->resorcers.y;
	j = main->resorcers.x; 
	while(main->resorcers.file[i][j])
	{
		if (main->resorcers.file[i][j] == '0')
			return(false);
		j++;
	}
	return (true);
}
bool border_check(t_main *main)
{
	size_t i;
	size_t j;

	i = main->resorcers.y;
	if(!first_row(main))
		return(false);
	while(i < main->resorcers.end_map)
    {
        j = 0;
		printf("%s\n", main->resorcers.file[i]);
        while(main->resorcers.file[i][j])
        {
			update_lower(main, i, j);
            if (main->resorcers.file[i][j] == '0')
            {
                if (main->resorcers.file[i - 1][j] == ' ' || main->resorcers.file[i - 1][j] == '	')
                    return(false);
				if (main->resorcers.file[i + 1][j] == ' ' || main->resorcers.file[i + 1][j] == '	')
                    return(false);
				if (main->resorcers.file[i + 1][0] == '\0')
					return(false);

            }
            j++;   
        }
        i++;
    }
	return(true);
}

void find_low(t_main *main)
{
	size_t i;
	size_t j;
	bool flag;
	
	i = main->resorcers.y;
	flag = true;
	while(i <= main->resorcers.end_map)
	{
		j = 0;
		while(main->resorcers.file[i][j])
		{
			if (main->resorcers.file[i][j] == '1')
				break;
			j++;
		}
		if (flag == true)
		{
			main->resorcers.lower_x = j;
			flag = false;
		}
		if (j < main->resorcers.lower_x)
			main->resorcers.lower_x = j;
		i++;
	}
}

size_t find_end_line(t_main *main, size_t i)
{
	size_t x;

	x = 0;
	while (main->resorcers.file[i][x])
	{
		if (main->resorcers.file[i][x] == '\n')
			return (x);
		x++;
	}
	return (x);
}
void trim_map(t_main *main)
{
	size_t i;
	size_t j;
	
	i = main->resorcers.y;
	j = 0;
	main->resorcers.map = lib_calloc((main->resorcers.end_map - main->resorcers.y) + 2, sizeof(char *));
	//printf("end map %ld\n", main->resorcers.end_map);
	while(i <= main->resorcers.end_map)
	{
		main->resorcers.map[j] = lib_strdup_part(main->resorcers.file[i], main->resorcers.lower_x, find_end_line(main, i));
		j++;
		i++;
	}
	main->resorcers.map[j] = NULL;
}

void a(t_main *main)
{
	size_t i;

	i = 0;
	while(main->resorcers.map[i])
	{
		printf("%s\n", main->resorcers.map[i]);
		i++;
	}
	
}
void	floodfill(t_main *main, size_t y, size_t x)
{	
	printf("Y: %ld", y);	
	printf("X: %ld\n", x);	
	if (main->resorcers.flood_flag == true)
		return;
	
	if (main->resorcers.map[y] == NULL)
	{
		main->resorcers.flood_flag = true;
		return;
	}
	if (x >= lib_strlen(main->resorcers.map[y]))
		return;
	if (main->resorcers.map[y][x] == ' ' || main->resorcers.map[y][x] == '	')
		return;
	main->resorcers.map[y][x] = 'F';
	floodfill(main, y + 1, x);
	if (y != 0)
		floodfill(main, y - 1, x);
	floodfill(main, y, x + 1);
	if (x != 0)
		floodfill(main, y, x - 1);
}
size_t find_one(t_main *main)
{
	size_t j;
	
	j = 0;	
	while (main->resorcers.map[0][j])
	{
		printf("%c", main->resorcers.map[0][j]);
		if (main->resorcers.map[0][j] == '1')
			return(j);
		j++;
	}
	return(j);
}
bool delimitor_check(t_main * main)
{
	if (!border_check(main))
		return (printf("Border check\n"), false);
	find_low(main);
	trim_map(main);
	//floodfill(main, 0, find_one(main));
	//a(main);
    return (true);
}

bool map_chek(t_main *main)
{
	if(!find_map(main))
		return(false);
	if (!delimitor_check(main))
   		return (false);
   return (true);
}
