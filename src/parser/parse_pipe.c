/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:45:05 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 11:43:47 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pipe(t_parser *parser)
{
	return (parser->current && parser->current->type == TOKEN_PIPE);
}

t_ast_node	*parse_pipe(t_minish *sh)
{
	t_ast_node	*left;
	t_ast_node	*right;
	t_ast_node	*pipe;

	left = parse_command(sh);
	if (!left)
		return (NULL);
	while (is_pipe(sh->parser))
	{
		parser_go(sh->parser);
		right = parse_command(sh);
		if (!right)
			return (free_ast(left), NULL);
		pipe = create_pipe_node(left, right);
		if (!pipe)
			return (free_ast(left), free_ast(right), NULL);
		left = pipe;
	}
	return (left);
}
