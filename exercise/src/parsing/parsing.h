/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:00:40 by david             #+#    #+#             */
/*   Updated: 2026/04/15 20:10:07 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSING_H
# define PARSING_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include "../cub.h"

typedef struct s_resorcers
{
    void *wall;
    void *door;
    void *floor;
    void *sky;
    char **file;
    char **map;
	char **dir;
	size_t y;
	size_t x;
	size_t lower_x;
	size_t end_map;
} t_resorcers;


typedef struct s_flag
{
	bool double_map;
	bool NO;
	bool SO;
	bool WE;
	bool EA;
	
} t_flag;

typedef struct s_main
{
    t_resorcers resorcers;
	t_flag flags;
    
} t_main;

bool parse(int ac, char **av);
bool map_chek(t_main *main);
bool find_map(t_main *main);

#endif