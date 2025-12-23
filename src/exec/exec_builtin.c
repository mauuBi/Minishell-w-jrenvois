/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:46:48 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 23:40:35 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_exit(t_minish *sh, t_exit res, char **args)
{
	free_2char(args);
	if (sh->ast)
		free_ast(sh->ast);
	if (sh->input)
		free(sh->input);
	cleanup_minish(sh);
	if (res.need_exit == 2)
		exit(sh->exit_code);
	exit(res.code);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", INT_MAX))
		return (1);
	if (!ft_strncmp(cmd, "cd", INT_MAX))
		return (1);
	if (!ft_strncmp(cmd, "pwd", INT_MAX))
		return (1);
	if (!ft_strncmp(cmd, "export", INT_MAX))
		return (1);
	if (!ft_strncmp(cmd, "unset", INT_MAX))
		return (1);
	if (!ft_strncmp(cmd, "env", INT_MAX))
		return (1);
	if (!ft_strncmp(cmd, "exit", INT_MAX))
		return (1);
	return (0);
}

int	execute_builtin(char **args, t_minish *sh)
{
	t_exit	exit_res;

	if (!args || !args[0])
		return (1);
	if (!ft_strncmp(args[0], "echo", INT_MAX))
		return (ft_echo(args));
	if (!ft_strncmp(args[0], "cd", INT_MAX))
		return (ft_cd(args, &sh->env));
	if (!ft_strncmp(args[0], "pwd", INT_MAX))
		return (ft_pwd());
	if (!ft_strncmp(args[0], "export", INT_MAX))
		return (ft_export(args, &sh->env));
	if (!ft_strncmp(args[0], "unset", INT_MAX))
		return (ft_unset(args, &sh->env));
	if (!ft_strncmp(args[0], "env", INT_MAX))
		return (ft_env(&sh->env));
	if (!ft_strncmp(args[0], "exit", INT_MAX))
	{
		exit_res = ft_exit(args);
		if (exit_res.need_exit)
			free_exit(sh, exit_res, args);
		return (exit_res.code);
	}
	return (1);
}
