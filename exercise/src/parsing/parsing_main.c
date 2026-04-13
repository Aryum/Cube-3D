/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 14:50:35 by david             #+#    #+#             */
/*   Updated: 2026/04/02 19:35:08 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


char	*helper(char *filename)
{
	int		fd;
	char	*line;
	char	*temp;
	size_t	bytesread;
	char	buffer[BUFFER_SIZE + 1];

	fd = open(filename, O_RDONLY);
	bytesread = 1;
	if (fd < 0)
		return (write(2, "ERROR:\nPlease submit a map!\n", 29), NULL);
	line = lib_strdup("");
	while (bytesread > 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread > 0)
		{
			buffer[bytesread] = '\0';
			temp = line;
			line = lib_strjoin(line, buffer);
			free(temp);
		}
	}
	return (line);
}


void map_creator(t_main *main, char *file)
{ 
    main->resorcers.file = lib_split(helper(file), '\n');

}

bool parse(int ac, char **av)
{
    t_main main;
	
	memset(&main, 0, sizeof(t_main));
    if (ac == 2)
    {
        map_creator(&main ,av[1]);
		if (!map_chek(&main))
			return(false);
		return (true);
    }
	return (false);
}