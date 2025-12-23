/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:08:15 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/07 15:39:13 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_has_error(t_lexer *lexer)
{
	return (lexer && lexer->err_code != LEXER_ERROR_NONE);
}

void	lexer_set_error(t_lexer *lexer, int code, char *msg, int pos)
{
	if (!lexer || !msg)
		return ;
	if (lexer->err_msg)
		free(lexer->err_msg);
	lexer->err_code = code;
	lexer->err_msg = ft_strdup(msg);
	lexer->err_pos = pos;
	if (!lexer->err_msg)
	{
		lexer->err_code = LEXER_ERROR_MEMORY_ALLOCATION;
		lexer->err_msg = ft_strdup("Memory allocation failed for err msg");
		lexer->err_pos = pos;
	}
}

void	lexer_cleanup(t_lexer *lexer)
{
	if (!lexer)
		return ;
	if (lexer->input)
		free(lexer->input);
	if (lexer->tokens)
		free_token_list(lexer->tokens);
	if (lexer->err_msg)
		free(lexer->err_msg);
	*lexer = (t_lexer){0};
}
