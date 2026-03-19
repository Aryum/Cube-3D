#include "input.h"

static void	setup_key(t_keys type, int code, bool hold, int (*f)( void ))
{
	data()->input[type].hold_call = hold;
	data()->input[type].code = code;
	data()->input[type].func = f;
	data()->input[type].status = false;

}

void	setup_inputs()
{
	setup_key(key_w, 119, true, NULL);
	setup_key(key_a, 97, true, NULL);
	setup_key(key_s, 115, true, NULL);
	setup_key(key_d, 100, true, NULL);
	return;
	//setup_key(key_left, 65363, true, rot_left);
	//setup_key(key_right, 65361, true, rot_right);

	setup_key(key_esc, 65307, false, exit_clean);
}