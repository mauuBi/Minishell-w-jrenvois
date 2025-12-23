/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:56:52 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/25 18:56:53 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_argument(char *arg, char **env, int exit_code)
{
	t_expand	exp;

	if (!arg)
		return (NULL);
	exp = (t_expand){arg, env, exit_code, 0, ft_strdup("")};
	while (exp.str[exp.pos])
	{
		if (exp.str[exp.pos] == '\'')
			process_single_quotes(&exp);
		else if (exp.str[exp.pos] == '"')
			process_double_quotes(&exp);
		else if (exp.str[exp.pos] == '\\' && exp.str[exp.pos + 1])
			process_escape(&exp);
		else if (exp.str[exp.pos] == '$')
			expand_variable(&exp);
		else
			process_normal_char(&exp);
	}
	return (exp.result);
}

char	**expand_arguments(char **args, char **env, int exit_code)
{
	char	**result;
	int		count;
	int		i;

	if (!args)
		return (NULL);
	count = 0;
	while (args[count])
		count++;
	result = ft_calloc(count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = expand_argument(args[i], env, exit_code);
		if (!result[i])
		{
			free_2char(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
