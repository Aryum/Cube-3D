#include "input.h"

int	key_press(int key)
{
	int	i;

	i = 0;
	while (i < KEYCOUNT)
	{
		if (input()->key_code[i] == key)
		{
			if(input()->key_func[i] != NULL)
			{
				printf("Key %d\n", input()->key_code[i]);
				input()->key_func[i]();
			}
			break;
		}
		i++;
	}
	if (i == KEYCOUNT)
		printf("Key not mapped\n");
	return 0;
}