/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:50:27 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 12:04:22 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_op(t_parser *parser)
{
	return (parser->current && (parser->current->type == TOKEN_OR
			|| parser->current->type == TOKEN_AND));
}

static int	get_op_type(t_parser *parser)
{
	if (!parser->current)
		return (-1);
	if (parser->current->type == TOKEN_OR)
		return (2);
	else if (parser->current->type == TOKEN_AND)
		return (1);
	return (-1);
}

t_ast_node	*parse_operator(t_minish *sh)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*operator;
	int			op_type;

	left = parse_pipe(sh);
	if (!left)
		return (NULL);
	while (is_op(sh->parser))
	{
		op_type = get_op_type(sh->parser);
		parser_go(sh->parser);
		right = parse_pipe(sh);
		if (!right)
			return (free_ast(left), NULL);
		operator = create_op_node(left, right, op_type);
		if (!operator)
			return (free_ast(left), free_ast(right), NULL);
		left = operator;
	}
	return (left);
}
