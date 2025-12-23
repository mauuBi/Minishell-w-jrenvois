/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:42:16 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 16:41:50 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_pipe_child(t_ast_node *node, int *pipefd,
	t_minish *sh, int is_left)
{
	int	resp_code;

	resp_code = 0;
	if (is_left)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		resp_code = execute_ast(node, sh);
		free_ast(sh->ast);
		cleanup_minish(sh);
		exit(resp_code);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		resp_code = execute_ast(node, sh);
		free_ast(sh->ast);
		cleanup_minish(sh);
		exit(resp_code);
	}
}

static int	wait_for_pipe_children(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	return (1);
}

int	execute_pipe(t_ast_node *node, t_minish *sh)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!node || node->type != NODE_PIPE)
		return (1);
	if (pipe(pipefd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (1);
	if (pid1 == 0)
		execute_pipe_child(node->left, pipefd, sh, 1);
	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0)
		execute_pipe_child(node->right, pipefd, sh, 0);
	close(pipefd[0]);
	close(pipefd[1]);
	return (wait_for_pipe_children(pid1, pid2));
}
