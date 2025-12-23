/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:02:03 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 12:04:36 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_list(t_parser *parser)
{
	return (parser->current && parser->current->type == TOKEN_SEMICOLON);
}

t_ast_node	*parse_list(t_minish *sh)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*list;

	left = parse_operator(sh);
	if (!left)
		return (NULL);
	while (is_list(sh->parser))
	{
		parser_go(sh->parser);
		right = parse_operator(sh);
		if (!right)
			return (free_ast(left), NULL);
		list = create_list_node(left, right);
		if (!list)
			return (free_ast(left), free_ast(right), NULL);
		left = list;
	}
	return (left);
}
