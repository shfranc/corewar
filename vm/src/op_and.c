/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:50:29 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/10 10:50:30 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** And : p1 & p2 and put the result in registre p3
** p1 = reg | dir | ind
** p2 = reg | dir | ind
** p3 = reg
** Modify the carry
*/

void	op_and(t_vm *vm, t_processus *proc, t_param *params)
{
	int		p1;
	int		p2;

	print_str("\tExecuting AND\n", ALL, vm);
	p1 = get_value_according_to_type(vm, proc, &params[0], RESTRICT);
	p2 = get_value_according_to_type(vm, proc, &params[1], RESTRICT);
	proc->reg[params[2].value - 1] = p1 & p2;
	proc->carry = ((p1 & p2) == 0) ? 1 : 0;
}
