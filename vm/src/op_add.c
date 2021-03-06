/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 20:13:16 by curquiza          #+#    #+#             */
/*   Updated: 2019/01/09 20:13:20 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Add : p1 + p2 and put the result in registre p3
** p1 = reg
** p2 = reg
** p3 = reg
** Modify the carry
*/

void	op_add(t_vm *vm, t_processus *proc, t_param *params)
{
	int		p1;
	int		p2;
	int		p3;

	print_str("\tExecuting ADD\n", ALL, vm);
	p1 = get_value_according_to_type(vm, proc, &params[0], RESTRICT);
	p2 = get_value_according_to_type(vm, proc, &params[1], RESTRICT);
	p3 = params[2].value;
	proc->reg[p3 - 1] = p1 + p2;
	proc->carry = ((p1 + p2) == 0) ? 1 : 0;
}
