/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:00:00 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/24 13:13:46 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *name, t_expand *exp)
{
	char	*value;

	if (!name)
		return (ft_strdup(""));
	if (ft_strlen(name) == 1)
	{
		if (name[0] == '?')
			return (ft_itoa(exp->exit_code));
		if (name[0] == '$')
			return (ft_strdup("$"));
	}
	value = get_env_value(name, exp->env);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*extract_var_name(t_expand *exp)
{
	int	start;

	start = exp->pos;
	if (exp->str[exp->pos] == '?' || exp->str[exp->pos] == '$')
	{
		exp->pos++;
		return (ft_substr(exp->str, start, 1));
	}
	if (ft_isalpha(exp->str[exp->pos]) || exp->str[exp->pos] == '_')
	{
		while (exp->str[exp->pos]
			&& (ft_isalnum(exp->str[exp->pos])
				|| exp->str[exp->pos] == '_'))
			exp->pos++;
		return (ft_substr(exp->str, start, exp->pos - start));
	}
	return (NULL);
}

void	add_to_result(t_expand *exp, char *segment)
{
	char	*tmp;

	if (!segment)
		return ;
	tmp = exp->result;
	exp->result = ft_strjoin(tmp, segment);
	free(tmp);
	free(segment);
}

void	expand_variable(t_expand *exp)
{
	char	*name;
	char	*value;

	exp->pos++;
	if (!exp->str[exp->pos])
	{
		add_to_result(exp, ft_strdup("$"));
		return ;
	}
	name = extract_var_name(exp);
	value = get_var_value(name, exp);
	add_to_result(exp, value);
	free(name);
}
