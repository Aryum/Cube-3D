#include "data.h"


void	setup_key(t_keys type, int code, int (*key_func)( void ))
{
	input()->key_code[type] = code;
	input()->key_func[type] = key_func;
}

void	setup_inputs()
{
	setup_key(key_w, 119, NULL);
	setup_key(key_a, 97, NULL);
	setup_key(key_s, 115, NULL);
	setup_key(key_d, 100, NULL);
	setup_key(key_esc, 65307, exit_clean);
}

void	ini_data()
{
	setup_inputs();


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

	render()->window_x = map()->size_x * GRIDSIZE;
	render()->window_y = map()->size_y * GRIDSIZE;

}