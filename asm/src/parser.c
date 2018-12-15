#include "asm.h"
#include <stdio.h>

/*
** parse: organize parsing of the name, comment, and instructions.
*/

t_ex_ret		parse(t_src_file *file)
{
	if ((parse_name(file)) == FAILURE)
		return (FAILURE);
	if ((parse_comment(file)) == FAILURE)
		return (FAILURE);
	if ((parser(file)) == FAILURE)
		return (FAILURE);

	if (!(g_flags & FLAG_A))
	{
		if ((write_output_file(file)) == FAILURE)
			return (FAILURE);
	}
	else
		write_output_stdout(file);

	close(file->fd);
	return (SUCCESS);
}

t_ex_ret		parse_line(t_token_list *tokens, int nb_line)
{
	(void)nb_line;
	(void)tokens;

	return (SUCCESS);
}

/*
** parser: read the end of the file, line by line and parse them.
*/

t_ex_ret		init_parser(t_src_file *file, char ***array_input)
{
	t_ex_ret		ret;
	t_list 			*list_input;

	list_input = NULL;
	ret = FAILURE;
	if ((read_file(file, &list_input)) == SUCCESS)
		ret = list_to_array(list_input, array_input, ft_lstlen(list_input));
	ft_lstdel(&list_input, &del);
	return (ret);
}

t_ex_ret		parser(t_src_file *file)
{
	t_ex_ret		ret;
	char			**array_input;
	t_token_list 	*tokens;
	char			**tmp;

	array_input = NULL;
	tokens = NULL;
	init_parser(file, &array_input);
	tmp = array_input;
	while (*tmp)
	{
		file->nb_line++;
		if ((lexer(&tokens, *tmp, file->nb_line)) == FAILURE)
		{
			ft_tabdel(&array_input);
			free_tokens(&tokens);
			return (FAILURE);
		}
		print_tokens(tokens);
		ret = parse_line(tokens, file->nb_line); // return ??
		free_tokens(&tokens);
		tmp++;
	}
	ft_tabdel(&array_input);
	return (ret);
}

// t_ex_ret		parser(t_src_file *file)
// {
// 	char			*line;
// 	t_token_list 	*tokens;
// 	t_ex_ret		ret;

// 	tokens = NULL;
// 	while ((get_next_line(file->fd, &line)) > 0)
// 	{
// 		file->nb_line++;
// 		if ((lexer(&tokens, line, file->nb_line)) == FAILURE)
// 			return (FAILURE);
// 		ft_printf("%d ", file->nb_line);
// 		print_tokens(tokens);
// 		ret = parse_line(tokens, file->nb_line);
// 		free_tokens(&tokens);
// 		ft_strdel(&line);
// 	}
// 	return (ret);
// }
