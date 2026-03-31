#include "input.h"

static void	setup_key(t_data *dt, t_keys type, int code, int (*f)( void ))
{
	dt->input[type].neg_key = -1;
	dt->input[type].code = code;
	dt->input[type].func = f;
	dt->input[type].status = false;

}

static void	set_neg(t_data *dt, t_keys a, t_keys b)
{
	dt->input[a].neg_key = b;
	dt->input[b].neg_key = a;
}

void	setup_inputs()
{
	t_data *dt;

	dt = data();
	setup_key(dt, key_w, 119, NULL);
	setup_key(dt, key_a, 97, NULL);
	setup_key(dt, key_s, 115, NULL);
	setup_key(dt, key_d, 100, NULL);
	setup_key(dt, key_left, 65363, NULL);
	setup_key(dt, key_right, 65361, NULL);
	setup_key(dt, key_up, 65362, NULL);
	setup_key(dt, key_down, 65364, NULL);
	setup_key(dt, key_right, 65361, NULL);
	setup_key(dt, key_esc, 65307, exit_clean);

	set_neg(dt, key_w, key_s);
	set_neg(dt, key_a, key_d);
	set_neg(dt, key_right, key_left);
	set_neg(dt, key_up, key_down);
}
