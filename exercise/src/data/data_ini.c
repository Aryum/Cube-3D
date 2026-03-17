#include "data.h"


void	setup_keys()
{
	input()->key_code[key_w] = 119;
	input()->key_code[key_a] = 97;
	input()->key_code[key_s] = 115;
	input()->key_code[key_d] = 100;
	input()->key_code[key_esc] = 65307;
	input()->key_func[key_w] = NULL;
	input()->key_func[key_a] = NULL;
	input()->key_func[key_s] = NULL;
	input()->key_func[key_d] = NULL;
	input()->key_func[key_esc] = clean_data;
}

void	ini_data()
{
	setup_keys();


	char *layout = "\
111111111111\n\
100000000001\n\
100000000001\n\
100000111111\n\
100000000001\n\
100000100001\n\
111111111111";

	printf("%s\n", layout);
	map()->layout = lib_split(layout, '\n');
	map()->size_x = lib_strlen(map()->layout[0]);
	while (map()->layout[map()->size_y] != NULL)
		map()->size_y++;
}