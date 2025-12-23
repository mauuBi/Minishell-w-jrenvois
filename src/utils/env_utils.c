/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:38:17 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/24 22:03:21 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_index(char *key, char ***env)
{
	int	i;

	if (!env)
		return (-1);
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, ft_strlen(key))
			&& (*env)[i][ft_strlen(key)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	add_env_var(char *new_var, char ***env)
{
	int	i;

	if (!env)
		return (free(new_var), -1);
	if (realloc_tab(env, 1) == -1)
		return (free(new_var), -1);
	i = 0;
	while ((*env)[i])
		i++;
	(*env)[i] = new_var;
	(*env)[i + 1] = NULL;
	return (0);
}

int	set_env_var(char *key, char *value, char ***env)
{
	int		index;
	char	*tmp;
	char	*new_var;

	if (!key || !env)
		return (-1);
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (-1);
	if (value)
		new_var = ft_strjoin(tmp, value);
	else
		new_var = ft_strjoin(tmp, "");
	free(tmp);
	if (!new_var)
		return (-1);
	index = env_var_index(key, env);
	if (index == -1)
		return (add_env_var(new_var, env));
	free((*env)[index]);
	(*env)[index] = new_var;
	return (0);
}

int	unset_env_var(char *key, char ***env)
{
	int		index;

	if (!env || !*env)
		return (-1);
	index = env_var_index(key, env);
	if (index == -1)
		return (0);
	return (remove_tab_element(env, index));
}

int	validate_env_var(char *var)
{
	int	i;

	if (!var || !var[0])
		return (0);
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
