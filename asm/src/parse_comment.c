/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:48:08 by sfranc            #+#    #+#             */
/*   Updated: 2019/02/14 10:48:20 by sfranc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_ex_ret		comment_check_before(char *line, int nb_line)
{
	char	*start;
	char	*start_line;

	if ((start = ft_strchr(line, '"')) == NULL)
		return (parse_error(nb_line, NO_COMMENT));
	start_line = line + ft_strlen(COMMENT_CMD_STRING);
	while (start_line != start)
	{
		if (is_whitespace(*start_line))
			start_line++;
		else
			return (parse_error_token(nb_line, start_line, INVALID_TOKEN));
	}
	return (SUCCESS);
}

static t_ex_ret		comment_check_after(char *line, int nb_line)
{
	char	*start;
	char	*end;
	char	*start_line;

	start = ft_strchr(line, '"') + 1;
	if (count_char(start, '"') != 1)
		return (parse_error_token(nb_line, start, ERR_QUOTE));
	end = ft_strrchr(line, '"');
	start_line = end + 1;
	while (*start_line)
	{
		if (is_whitespace(*start_line))
			start_line++;
		else
			return (parse_error_token(nb_line, start_line, INVALID_TOKEN));
	}
	return (SUCCESS);
}

static int			get_comment(t_src_file *file, char **line)
{
	char	*start;
	char	*end;
	int		size;

	if (comment_check_before(*line, file->nb_line) == FAILURE)
		return (FAILURE);
	if (read_again(file, line) == FAILURE)
		return (FAILURE);
	if (comment_check_after(*line, file->nb_line) == FAILURE)
		return (FAILURE);
	start = ft_strchr(*line, '"') + 1;
	end = ft_strrchr(*line, '"');
	size = end - start > COMMENT_LENGTH + 1 ? -1 : end - start;
	if (size == -1)
		return (parse_error(file->nb_line, BIG_COMMENT));
	ft_memcpy(file->header.comment, start, size);
	if (*(file->header.comment) == '\0')
		return (parse_error(file->nb_line, NO_COMMENT));
	return (SUCCESS);
}

static t_ex_ret		return_parse_comment(t_src_file *file, int ret)
{
	if (ret == -1)
		return (ft_ret_err(ERR_GNL));
	if (ret == 0 || *(file->header.comment) == '\0')
		return (parse_error(file->nb_line, NO_COMMENT));
	return (SUCCESS);
}

t_ex_ret			parse_comment(t_src_file *file)
{
	char	*line;
	int		ret;

	while ((ret = get_trim_line(file->fd, &line)) == 1)
	{
		file->nb_line++;
		if (*line == '#' || *line == '\0')
		{
			ft_strdel(&line);
			continue ;
		}
		else if ((ft_strncmp(line, COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING))) == 0)
		{
			ret = get_comment(file, &line);
			ft_strdel(&line);
			return (ret);
		}
		else
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (return_parse_comment(file, ret));
}
