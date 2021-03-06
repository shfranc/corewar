/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:43:37 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:43:39 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			get_registre(unsigned char *output, char *r)
{
	*output = ft_atoi(r + 1);
	return ;
}

t_ex_ret		encode_parameters(t_src_file *file, int i, int pos)
{
	unsigned int		j;

	j = 0;
	while (j < file->ast[i]->opcode->param_nb)
	{
		if ((file->ast[i]->arg_type[j] & T_REG) == T_REG)
		{
			get_registre(file->output + pos, file->ast[i]->arguments[j]);
			pos += NUM_REG_SIZE;
		}
		else if ((file->ast[i]->arg_type[j] & T_IND) == T_IND)
		{
			if (get_indirect(file, i, j, pos) == FAILURE)
				return (FAILURE);
			pos += IND_SIZE;
		}
		else if ((file->ast[i]->arg_type[j] & T_DIR) == T_DIR)
		{
			if (get_direct(file, i, j, pos) == FAILURE)
				return (FAILURE);
			pos += get_dir_size(file->ast[i]->opcode->index);
		}
		j++;
	}
	return (SUCCESS);
}

t_ex_ret		encode_instructions(t_src_file *file)
{
	int i;
	int start;

	i = 0;
	while (file->ast[i])
	{
		if (file->ast[i]->opcode)
		{
			start = file->ast[i]->offset;
			file->output[start] = file->ast[i]->opcode->opcode;
			if (file->ast[i]->opcode->ocp)
			{
				file->output[start + 1] = create_ocp(file->ast[i]);
				start++;
			}
			if (encode_parameters(file, i, start + 1) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

t_ex_ret		encode(t_src_file *file)
{
	if (create_symbol_table(file) == FAILURE)
		return (FAILURE);
	if (encode_instructions(file) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
