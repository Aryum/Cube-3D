#ifndef HLP_H
# define HLP_H

#include "gnl.h"

int		h_appendbuffer(t_gnl *gnl, char *buffer);
void	h_resetbuffer(char *buffer, int failed);
void	h_updateline(t_gnl *gnl, char *updated, bool failed);

#endif