#include "data.h"


void	setup_keys()
{
	data()->key_code[key_w] = 119;
	data()->key_code[key_a] = 97;
	data()->key_code[key_s] = 115;
	data()->key_code[key_d] = 100;
	data()->key_code[key_esc] = 65307;
	data()->key_func[key_w] = NULL;
	data()->key_func[key_a] = NULL;
	data()->key_func[key_s] = NULL;
	data()->key_func[key_d] = NULL;
	data()->key_func[key_esc] = clean_data;
}

void	ini_data()
{
	setup_keys();
	char *map = "\
111111111111\n \
100000000001\n \
100000000001\n \
100000111111\n \
100000000001\n \
100000100001\n \
111111111111";
	data()->map = lib_split(map, '\n');
}