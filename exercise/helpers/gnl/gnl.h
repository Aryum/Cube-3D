/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ricsanto <ricsanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:58:57 by ricsanto          #+#    #+#             */
/*   Updated: 2026/04/13 14:35:24 by ricsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_gnl
{
	char	*line;
	bool	failed;
}	t_gnl;

t_gnl	get_next_line(int fd);


#endif
