#include "vm.h"

t_vm *g_vm = NULL;

void	print_player(t_player *p)
{
	ft_printf("Player num %d (%#0x)\n", p->num, ~p->num);
	ft_printf("header :\n");
	ft_printf("-> magic = %#0x\n", p->header.magic);
	ft_printf("-> name = %s\n", p->header.prog_name);
	ft_printf("-> size = %d\n", p->header.prog_size);
	ft_printf("-> comment = %s\n", p->header.comment);
}

void	print_vm(t_vm *vm)
{
	int		i;

	ft_printf("VM :\n");
	ft_printf("Player number = %d\n", vm->players_number);
	ft_printf("flag = %b\n", vm->flag);
	ft_printf("Dump cycles = %d\n", vm->dump_cycle);
	ft_printf("----------------------\n");
	ft_printf("PLAYERS :\n");
	i = 0;
	while (i < vm->players_number)
	{
		print_player(&vm->player[i]);
		i++;
		ft_printf("---\n");
	}
	ft_printf("----------------------\n");
}

t_exit	init_check(void)
{
	if (PROG_NAME_LENGTH % 4 != 0 || PROG_NAME_LENGTH <= 0
		|| COMMENT_LENGTH % 4 != 0 || COMMENT_LENGTH <= 0)
	{
		ft_dprintf(2, DEFINE_ERR);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main (int argc, char **argv)
{
	t_vm	vm;

	g_vm = &vm;
	ft_bzero(&vm, sizeof(vm));
	if (init_check() == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (argc <= 1)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	if (parsing(argc, argv, &vm) == EXIT_FAILURE)
	{
		clean_all();
		exit(EXIT_FAILURE);
	}
	/*print_vm(&vm);*/
	clean_all();
	return (EXIT_SUCCESS);
}
