/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:50:37 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 13:23:05 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Ld : load a value into a registre.
** p1 = dir | ind
** p2 = reg
** Modify the carry.
*/

void	op_ld(t_vm *vm, t_processus *proc, t_param *params)
{
	int		reg_index;
	int		v_to_ld;

	print_str("\tExecuting LD\n", ALL, vm);
	reg_index = params[1].value;
	v_to_ld = get_value_according_to_type(vm, proc, &params[0], RESTRICT);
	proc->reg[reg_index - 1] = v_to_ld;
	proc->carry = v_to_ld == 0 ? 1 : 0;
}
