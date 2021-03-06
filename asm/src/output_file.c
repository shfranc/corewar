/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:46:43 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:46:45 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_ex_ret	write_output_file(t_src_file *file)
{
	int		fd;
	char	*tmp;
	char	*output;

	if (!(tmp = ft_strsub(file->filename, 0,
		ft_strrchr(file->filename, '.') - file->filename)))
	{
		return (ft_ret_err(ERR_MALLOC));
	}
	if (!(output = ft_strjoin(tmp, OUTPUT_EXT)))
		return (ft_ret_err(ERR_MALLOC));
	if ((fd = open(output, O_CREAT | O_TRUNC | O_WRONLY,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		return (ft_ret_err(ERR_OPEN));
	}
	write(fd, (const char*)&(file->header), sizeof(file->header));
	ft_printf("%s %s\n", WRITING_PROG, output);
	write(fd, file->output, ft_swap_int(file->header.prog_size));
	free(tmp);
	free(output);
	close(fd);
	return (SUCCESS);
}
