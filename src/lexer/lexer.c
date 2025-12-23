/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:49:30 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/22 15:37:01 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_lexer(t_lexer *lexer, char *input)
{
	if (!input)
	{
		lexer_set_error(lexer, LEXER_ERROR_MEMORY_ALLOCATION, "null input", 0);
		return (0);
	}
	lexer->input = ft_strdup(input);
	if (!lexer->input)
	{
		lexer_set_error(lexer, LEXER_ERROR_MEMORY_ALLOCATION,
			"memory allocation failed", 0);
		return (0);
	}
	lexer->tokens = ft_calloc(1, sizeof(t_token_list));
	if (!lexer->tokens)
	{
		free(lexer->input);
		lexer_set_error(lexer, LEXER_ERROR_MEMORY_ALLOCATION,
			"memory allocation failed", 0);
		return (0);
	}
	lexer->qstack.top = -1;
	return (1);
}

int	state_normal(t_lexer *lexer)
{
	if (ft_isspace(lexer->input[lexer->i]))
		lexer->i++;
	else if (lexer->input[lexer->i] == '\'')
		handle_quote(lexer, TOKEN_SQUOTE, lexer->i);
	else if (lexer->input[lexer->i] == '"')
		handle_quote(lexer, TOKEN_DQUOTE, lexer->i);
	else if (is_operator(lexer->input[lexer->i]))
	{
		if (!handle_operator(lexer))
			return (0);
	}
	else
		handle_word(lexer);
	return (1);
}

int	lexer_dispatch(t_lexer *lexer)
{
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '\n')
	{
		if (lexer->state == STATE_NORMAL)
		{
			if (!state_normal(lexer))
				return (0);
		}
		if (lexer_has_error(lexer))
			return (0);
	}
	handle_newline(lexer);
	return (1);
}

int	lexer_run(t_minish *sh)
{
	int		validator_ret;

	init_lexer(sh->lexer, sh->input);
	lexer_dispatch(sh->lexer);
	validator_ret = validator_validate(sh->lexer);
	if (validator_ret == -1)
	{
		lexer_cleanup(sh->lexer);
		return (-1);
	}
	add_history(sh->input);
	if (sh->lexer->err_code)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(sh->lexer->err_msg, 2);
		write(2, "\n", 1);
		lexer_cleanup(sh->lexer);
		return (2);
	}
	return (0);
}
