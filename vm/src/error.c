#include "vm.h"

t_exit	wrong_flag_err(char *s)
{
	ft_dprintf(2, "Error: %s: %s", s, WRONG_FLAG_ERR);
	return (EXIT_FAILURE);
}

t_exit	player_num_err(void)
{
	ft_dprintf(2, PLAYER_NUM_ERR);
	return (EXIT_FAILURE);
}

t_exit	dump_cycle_err(void)
{
	ft_dprintf(2, DUMP_CYCLE_ERR);
	return (EXIT_FAILURE);
}

t_exit	max_player_err(void)
{
	ft_dprintf(2, MAX_PLAYER_ERR);
	return (EXIT_FAILURE);
}
