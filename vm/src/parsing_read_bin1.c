#include "vm.h"

/*
** Read of prog_size +1 -> to check if the prog is not too big.
*/
t_exit	read_prog(char *filename, int fd, t_player *player)
{
	char	*buff;
	int		read_ret;

	if (!(buff = ft_memalloc(sizeof(char) * (player->header.prog_size + 1))))
		return (EXIT_FAILURE);
	read_ret = read(fd, buff, player->header.prog_size + 1);
	if (read_ret == -1)
	{
		ft_strdel(&buff);
		return (read_error(filename));
	}
	if ((unsigned int)read_ret != player->header.prog_size)
	{
		ft_strdel(&buff);
		ft_dprintf(2, PROG_SIZE_ERR);
		return (EXIT_FAILURE);
	}
	if (!(player->prog = ft_strdup(buff)))
	{
		ft_strdel(&buff);
		return (EXIT_FAILURE);
	}
	ft_strdel(&buff);
	return (EXIT_SUCCESS);
}


