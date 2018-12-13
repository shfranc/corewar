#include "vm.h"

void	op_and(t_vm *vm, t_processus *proc, t_param *params)
{
	int		rslt;
	int		p1;
	int		p2;

	print_str("\tExecuting AND\n", ALL, vm);
	p1 = get_value_according_to_type(vm, proc, &params[0]);
	p2 = get_value_according_to_type(vm, proc, &params[1]);
	rslt = p1 & p2;
	if (is_valid_reg_index(params[2].value) == TRUE)
		proc->reg[params[2].value - 1] = rslt;
	proc->carry = (rslt == 0) ? 1 : 0; // pas sûr pour le zero !
	ft_dprintf(vm->trace_fd, "p1 = 0x%x\n", p1); //DEBUG
	ft_dprintf(vm->trace_fd, "p2 = 0x%x\n", p2); //DEBUG
	ft_dprintf(vm->trace_fd, "p3 = 0x%x\n", params[2].value); //DEBUG
}
