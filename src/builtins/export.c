/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:07:53 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/30 15:21:52 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_error(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	display_env(char ***env)
{
	int	i;

	i = 0;
	if (!env || !*env || !(*env)[0])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while ((*env)[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd((*env)[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

static int	export_no_value(char *arg, int res)
{
	char	*key;

	key = ft_strdup(arg);
	if (!key)
		return (-1);
	if (!validate_env_var(key))
		return (free(key), -1);
	free(key);
	return (res);
}

static int	export_value(char *arg, char ***env, int res)
{
	char	*equal_pos;
	char	*key;
	char	*value;

	equal_pos = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, equal_pos - arg);
	value = ft_strdup(equal_pos + 1);
	if (!key || !value)
		return (free(key), free(value), -1);
	if (!validate_env_var(key))
		return (free(key), free(value), -1);
	if (set_env_var(key, value, env) == -1)
		return (free(key), free(value), -1);
	free(key);
	free(value);
	return (res);
}

int	ft_export(char **args, char ***env)
{
	char	*equal_pos;
	int		i;
	int		res;

	i = 1;
	res = 0;
	if (!args || !args[1])
		return (display_env(env));
	while (args[i])
	{
		if (export_error(args[i]))
		{
			res = 1;
			i++;
			continue ;
		}
		equal_pos = ft_strchr(args[i], '=');
		if (!equal_pos)
			res = export_no_value(args[i], res);
		else
			res = export_value(args[i], env, res);
		i++;
	}
	return (res);
}
