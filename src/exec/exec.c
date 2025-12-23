/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:45:28 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 20:55:42 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_redirects_only(t_ast_node *redirects, t_minish *sh)
{
	if (setup_builtin_redirects(redirects, sh) != 0)
	{
		return (1);
	}
	restore_fds(sh);
	return (0);
}

static int	execute_single_command(t_ast_node *node, t_minish *sh)
{
	char	**expanded_args;
	int		exit_code;

	if (!node || node->type != NODE_CMD)
		return (1);
	if (!node->args && node->redirects)
		return (exec_redirects_only(node->redirects, sh));
	expanded_args = expand_arguments(node->args, sh->env, sh->exit_code);
	if (!expanded_args)
		return (1);
	if (is_builtin(expanded_args[0]))
	{
		if (setup_builtin_redirects(node->redirects, sh) != 0)
		{
			free_2char(expanded_args);
			return (1);
		}
		exit_code = execute_builtin(expanded_args, sh);
		restore_fds(sh);
	}
	else
		exit_code = execute_external(expanded_args, node->redirects, sh);
	free_2char(expanded_args);
	return (exit_code);
}

static int	execute_operator(t_ast_node *node, t_minish *sh)
{
	int	left_result;

	if (!node || node->type != NODE_OPERATOR)
		return (1);
	left_result = execute_ast(node->left, sh);
	if (node->operator_type == 1)
	{
		if (left_result == 0)
			return (execute_ast(node->right, sh));
		return (left_result);
	}
	else if (node->operator_type == 2)
	{
		if (left_result)
			return (execute_ast(node->right, sh));
		return (left_result);
	}
	return (left_result);
}

int	execute_ast(t_ast_node *node, t_minish *sh)
{
	if (!node)
		return (1);
	if (node->type == NODE_CMD)
		return (execute_single_command(node, sh));
	else if (node->type == NODE_OPERATOR)
		return (execute_operator(node, sh));
	else if (node->type == NODE_PIPE)
		return (execute_pipe(node, sh));
	else if (node->type == NODE_LIST)
	{
		execute_ast(node->left, sh);
		return (execute_ast(node->right, sh));
	}
	return (1);
}

int	exec_run(t_minish *sh)
{
	if (!sh || !sh->ast)
		return (1);
	signal(SIGINT, handle_sigint2);
	sh->exit_code = execute_ast(sh->ast, sh);
	signal(SIGINT, handle_sigint);
	return (sh->exit_code);
}
