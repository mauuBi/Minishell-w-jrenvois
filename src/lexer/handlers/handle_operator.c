/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:16:13 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/14 18:25:41 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_op_type(char *op)
{
	if (!op || !op[0])
		return (TOKEN_WORD);
	if (op[0] == '|' && op[1] == '\0')
		return (TOKEN_PIPE);
	if (op[0] == '>' && op[1] == '\0')
		return (TOKEN_REDIRECT_OUT);
	if (op[0] == '<' && op[1] == '\0')
		return (TOKEN_REDIRECT_IN);
	if (op[0] == ';' && op[1] == '\0')
		return (TOKEN_SEMICOLON);
	if (op[0] == '>' && op[1] == '>' && op[2] == '\0')
		return (TOKEN_APPEND);
	if (op[0] == '<' && op[1] == '<' && op[2] == '\0')
		return (TOKEN_HEREDOC);
	if (op[0] == '|' && op[1] == '|' && op[2] == '\0')
		return (TOKEN_OR);
	if (op[0] == '&' && op[1] == '&' && op[2] == '\0')
		return (TOKEN_AND);
	return (TOKEN_WORD);
}

int	handle_operator(t_lexer *lexer)
{
	char			op[3];
	int				op_len;
	t_token_type	op_type;

	op_len = 0;
	while (lexer->input[lexer->i] != '\0' && is_operator(lexer->input[lexer->i])
		&& op_len < 2)
	{
		op[op_len] = lexer->input[lexer->i];
		op_len++;
		lexer->i++;
	}
	op[op_len] = '\0';
	op_type = get_op_type(op);
	if (op_type == TOKEN_WORD)
	{
		lexer_set_error(lexer, LEXER_ERROR_INVALID_OPERATOR,
			"invalid operator used", lexer->i - op_len);
		return (0);
	}
	add_token(lexer->tokens, op_type, op);
	return (1);
}
