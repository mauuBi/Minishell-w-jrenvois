/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:47:11 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 23:40:50 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_exit	exit_ret(char **args)
{
	t_atol	exitcode;
	t_exit	resp;

	exitcode = ft_atol(args[1]);
	if (exitcode.err_code)
	{
		printf("minishell: exit: %s: numeric argument required\n",
			args[1]);
		return (resp.need_exit = 1, resp.code = 2, resp);
	}
	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (resp.code = 2, resp);
	}
	return (resp.need_exit = 1, resp.code = exitcode.res, resp);
}

t_exit	ft_exit(char **args)
{
	t_exit	resp;

	resp = (t_exit){0};
	if (!args || !args[0])
		return (resp.code = 1, resp);
	ft_putstr_fd("exit\n", 1);
	if (args[1])
		return (exit_ret(args));
	return (resp.need_exit = 2, resp);
}
