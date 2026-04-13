#ifndef HLP_H
# define HLP_H

#include "gnl.h"

int		h_appendbuffer(char **last, char *buffer);
void	h_resetbuffer(char *buffer, int failed);

char	*h_updateret(char **last, char *updated);
#endif