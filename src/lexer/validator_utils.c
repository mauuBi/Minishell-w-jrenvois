/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:28:21 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/18 18:22:32 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_operator(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_PIPE || token->type == TOKEN_AND
		|| token->type == TOKEN_OR);
}

int	is_token_cmd(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_DQUOTE || token->type == TOKEN_WORD
		|| token->type == TOKEN_SQUOTE);
}

int	is_token_redirection(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_APPEND || token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT || token->type == TOKEN_HEREDOC);
}

void	v_error(t_validator *validator, char *token, int code)
{
	char	*tmp;

	if (!validator)
		return ;
	tmp = validator->err_msg;
	validator->err_msg = ft_strjoin(validator->err_msg,
			"syntax error near unexpected token ");
	free(tmp);
	if (!validator->err_msg)
		return ;
	tmp = validator->err_msg;
	validator->err_msg = ft_strjoin(validator->err_msg, token);
	free(tmp);
	validator->err_code = code;
}

void	print_verror(t_validator *validator)
{
	if (!validator || !validator->err_msg)
		return ;
	ft_putstr_fd(validator->err_msg, 2);
}
