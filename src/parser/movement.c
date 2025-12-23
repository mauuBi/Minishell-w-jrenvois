/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 01:44:36 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/16 14:26:25 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parser_current_token(t_parser *parser)
{
	return (parser->current);
}

t_token	*parser_next_token(t_parser *parser)
{
	if (!parser->current)
		return (NULL);
	return (parser->current->next);
}

void	parser_go(t_parser *parser)
{
	if (!parser->current)
		return ;
	parser->current = parser->current->next;
	parser->pos++;
}

int	parser_is_end(t_parser *parser)
{
	return (parser->current == NULL);
}
