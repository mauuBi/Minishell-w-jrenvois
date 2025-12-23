/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:39:10 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/14 20:00:17 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_commands(t_validator *validator)
{
	if (!validator->tokens)
		return (0);
	if (!validator->tokens->head || !validator->tokens->tail)
		return (0);
	return (1);
}

int	validate_operators(t_validator *validator)
{
	t_token	*current;

	current = validator->tokens->head;
	while (current)
	{
		if (is_token_operator(current))
		{
			if (!current->prev || !current->next)
				return (v_error(validator, current->value, 2), 0);
			if (!is_token_cmd(current->prev))
				return (v_error(validator, current->value, 2), 0);
			if (current->type != TOKEN_PIPE)
			{
				if (!is_token_cmd(current->next))
					return (v_error(validator, current->value, 2), 0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	validate_redirects(t_validator *validator)
{
	t_token	*current;

	current = validator->tokens->head;
	while (current)
	{
		if (is_token_redirection(current))
		{
			if (!current->next || !is_token_cmd(current->next))
				return (v_error(validator, current->value, 2), 0);
		}
		current = current->next;
	}
	return (1);
}

int	validate_separators(t_validator *validator)
{
	t_token	*current;

	current = validator->tokens->head;
	while (current)
	{
		if (current->type == TOKEN_SEMICOLON)
		{
			if (current == validator->tokens->head)
				return (v_error(validator, current->value, 2), 0);
			if (!current->prev || is_token_operator(current->prev)
				|| current->prev->type == TOKEN_SEMICOLON)
				return (v_error(validator, current->value, 2), 0);
		}
		current = current->next;
	}
	return (1);
}

int	validator_validate(t_lexer *lexer)
{
	t_validator	validator;
	int			err_code;

	err_code = 0;
	if (lexer->err_code)
		return (lexer->err_code);
	validator = (t_validator){0};
	validator.err_msg = ft_strdup("");
	validator.tokens = lexer->tokens;
	if (!validate_commands(&validator))
		err_code = -1;
	if (!err_code && !validate_operators(&validator))
		err_code = 2;
	if (!err_code && !validate_redirects(&validator))
		err_code = 2;
	if (!err_code && !validate_separators(&validator))
		err_code = 2;
	lexer->err_code = err_code;
	lexer->err_msg = ft_strdup(validator.err_msg);
	free(validator.err_msg);
	return (err_code);
}
