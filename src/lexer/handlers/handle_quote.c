/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:07:25 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/19 14:26:01 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_quote_type(t_token_type type)
{
	if (type == TOKEN_DQUOTE)
		return ('"');
	else if (type == TOKEN_SQUOTE)
		return ('\'');
	else
		return (0);
}

static int	need_stop(char c, t_token_type type, int pos, int pos2)
{
	if (pos == pos2)
		return (0);
	if (type == TOKEN_DQUOTE)
		return (c == '"');
	else if (type == TOKEN_SQUOTE)
		return (c == '\'');
	return (0);
}

static int	set_err(t_lexer *lexer)
{
	if (!lexer->input[lexer->i])
	{
		lexer_set_error(lexer, LEXER_ERROR_UNCLOSED_QUOTE,
			"unclosed quote", lexer->i);
		return (1);
	}
	if (lexer->bi >= 1023)
	{
		lexer_set_error(lexer, LEXER_ERROR_BUFFER_OVERFLOW,
			"token too long", lexer->i);
		return (1);
	}
	return (0);
}

void	handle_quote(t_lexer *lexer, t_token_type type, int pos)
{
	while (!need_stop(lexer->input[lexer->i], type, pos, lexer->i))
	{
		if (set_err(lexer))
			return ;
		if (lexer->input[lexer->i] == '\\')
			handle_backslash(lexer);
		else
		{
			lexer->buffer[lexer->bi] = lexer->input[lexer->i];
			lexer->bi++;
			lexer->i++;
		}
	}
	lexer->i++;
	lexer->buffer[lexer->bi] = get_quote_type(type);
	lexer->bi++;
	if (lexer->input[lexer->i] == ' ' || lexer->input[lexer->i] == '\0'
		|| is_operator(lexer->input[lexer->i]))
	{
		add_token(lexer->tokens, type, lexer->buffer);
		lexer->bi = 0;
		ft_bzero(lexer->buffer, 1024);
	}
}
