/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 03:14:33 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 11:42:22 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_cleanup(t_parser	*parser)
{
	if (!parser)
		return ;
	if (parser->err_msg)
		free(parser->err_msg);
	*parser = (t_parser){0};
}

int	init_parser(t_minish *sh)
{
	sh->parser->tokens = sh->lexer->tokens;
	if (!sh->parser->tokens)
		return (0);
	sh->parser->current = sh->lexer->tokens->head;
	return (1);
}

t_ast_node	*parse_all(t_minish *sh)
{
	return (parse_list(sh));
}

int	parser_run(t_minish *sh)
{
	t_ast_node	*ast;

	sh->ast = NULL;
	init_parser(sh);
	ast = parse_all(sh);
	if (!ast)
	{
		ft_putstr_fd("minishell: failed to create ast\n", 32);
		return (1);
	}
	sh->ast = ast;
	return (0);
}
