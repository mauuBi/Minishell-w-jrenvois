/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:29:51 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/18 18:47:06 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	need_stop(char c)
{
	return (!c || ft_isspace(c) || c == '\'' || c == '"' || is_operator(c)
		|| c == '\n');
}

void	handle_word(t_lexer *lexer)
{
	while (!need_stop(lexer->input[lexer->i]))
	{
		if (lexer->bi >= 1023)
		{
			lexer_set_error(lexer, LEXER_ERROR_BUFFER_OVERFLOW,
				"token too long", lexer->i);
			return ;
		}
		if (lexer->input[lexer->i] == '\\')
			handle_backslash(lexer);
		else
		{
			lexer->buffer[lexer->bi] = lexer->input[lexer->i];
			lexer->bi++;
			lexer->i++;
		}
	}
	if (lexer->input[lexer->i] == ' ' || lexer->input[lexer->i] == '\0'
		|| is_operator(lexer->input[lexer->i]))
	{
		add_token(lexer->tokens, TOKEN_WORD, lexer->buffer);
		lexer->bi = 0;
		ft_bzero(lexer->buffer, 1024);
	}
}
