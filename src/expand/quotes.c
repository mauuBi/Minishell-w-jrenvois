/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:54:42 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/25 18:54:58 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_single_quotes(t_expand *exp)
{
	int	start;

	exp->pos++;
	start = exp->pos;
	while (exp->str[exp->pos] && exp->str[exp->pos] != '\'')
		exp->pos++;
	add_to_result(exp, ft_substr(exp->str, start, exp->pos - start));
	if (exp->str[exp->pos] == '\'')
		exp->pos++;
}

void	process_double_quotes(t_expand *exp)
{
	exp->pos++;
	while (exp->str[exp->pos] && exp->str[exp->pos] != '"')
	{
		if (exp->str[exp->pos] == '\\' && exp->str[exp->pos + 1]
			&& (exp->str[exp->pos + 1] == '"' || exp->str[exp->pos + 1] == '$'
				|| exp->str[exp->pos + 1] == '\\'))
		{
			exp->pos++;
			add_to_result(exp, ft_substr(exp->str, exp->pos, 1));
			exp->pos++;
		}
		else if (exp->str[exp->pos] == '$')
			expand_variable(exp);
		else
		{
			add_to_result(exp, ft_substr(exp->str, exp->pos, 1));
			exp->pos++;
		}
	}
	if (exp->str[exp->pos] == '"')
		exp->pos++;
}
