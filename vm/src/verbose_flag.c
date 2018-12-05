#include "vm.h"

void	print_str(char *s, t_verbose type, t_vm *vm)
{
	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type > FEW))
		return ;
	ft_dprintf(vm->trace_fd, "%s", s);
}

void	print_str_int(char *s, int n, t_verbose type, t_vm *vm)
{
	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type > FEW))
		return ;
	ft_dprintf(vm->trace_fd, "%s (%d)\n", s, n);
}

void	print_upd_intvar(int v1, int v2, t_verbose type, t_vm *vm)
{
	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type > FEW))
		return ;
	ft_dprintf(vm->trace_fd, "%d -> %d\n", v1, v2);
}

void	print_compare_intvar(int v1, int v2, t_verbose type, t_vm *vm)
{
	if ((vm->verbose == NONE && type != NONE)
		|| (vm->verbose == FEW && type > FEW))
		return ;
	ft_dprintf(vm->trace_fd, "%d // %d\n", v1, v2);
}
