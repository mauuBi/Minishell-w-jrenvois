/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:22:38 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 23:18:57 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_n_option(char **args)
{
	int	start_arg;

	start_arg = 1;
	while (args[start_arg] && is_valid_n_option(args[start_arg]))
		(start_arg)++;
	return (start_arg - 1);
}

int	ft_echo(char **args)
{
	int	start_arg;
	int	i;

	if (!args)
		return (-1);
	start_arg = check_n_option(args);
	i = start_arg + 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!start_arg)
		ft_putstr_fd("\n", 1);
	return (0);
}
