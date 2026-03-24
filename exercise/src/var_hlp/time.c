#include "var_hlp.h"

long get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		exit_clean(NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}