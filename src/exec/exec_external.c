/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:42:27 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/30 13:12:14 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_err(char *cmd_name, t_cmd_res *cmd_res,
	t_minish *sh, t_ast_node *redirects)
{
	setup_builtin_redirects(redirects, sh);
	restore_fds(sh);
	if (cmd_res->path)
		free(cmd_res->path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd_res->error_msg, 2);
	ft_putstr_fd("\n", 2);
	return (cmd_res->error_code);
}

static int	run_external_child(char **args, t_ast_node *redirects,
	t_minish *sh, t_cmd_res *cmd_res)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_external_redirects(redirects, sh);
	if (execve(cmd_res->path, args, sh->env) == -1)
	{
		perror("execve");
		exit(1);
	}
	return (0);
}

int	execute_external(char **args, t_ast_node *redirects, t_minish *sh)
{
	char		**path;
	t_cmd_res	cmd_res;
	pid_t		pid;
	int			status;

	path = get_path(sh->env);
	cmd_res = find_cmd_in_path(args[0], path);
	free_2char(path);
	if (cmd_res.error_code)
		return (cmd_err(args[0], &cmd_res, sh, redirects));
	pid = fork();
	if (pid == -1)
		return (free(cmd_res.path), 1);
	if (pid == 0)
		run_external_child(args, redirects, sh, &cmd_res);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		return (free(cmd_res.path), 128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (free(cmd_res.path), WEXITSTATUS(status));
	return (free(cmd_res.path), 1);
}
