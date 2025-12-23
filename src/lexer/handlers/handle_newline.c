/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:16:56 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/07 15:26:15 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_newline(t_lexer *lexer)
{
	if (lexer->input[lexer->i] == '\n')
	{
		add_token(lexer->tokens, TOKEN_SEMICOLON, ";");
		lexer->i++;
	}
}
