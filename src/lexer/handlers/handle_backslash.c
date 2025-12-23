/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:48:34 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/07 15:25:57 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_backslash(t_lexer *lexer)
{
	lexer->i++;
	if (lexer->input[lexer->i] != '\0')
	{
		lexer->buffer[lexer->bi] = lexer->input[lexer->i];
		lexer->bi++;
		lexer->i++;
	}
}
