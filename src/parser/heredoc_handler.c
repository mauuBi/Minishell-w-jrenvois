/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:00:00 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/28 01:00:01 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_heredoc_eof(char *content, char *delimiter)
{
	printf("minishell: warning: here-document delimited by end-of-file "
		"(wanted `%s')\n", delimiter);
	return (content);
}

void	handle_heredoc_child(t_minish *sh, int pipefd[2],
	char *delimiter, t_dptr	dp)
{
	char	*content;

	close(pipefd[0]);
	content = read_heredoc_lines(sh, delimiter, NULL, dp);
	if (!content)
	{
		write(pipefd[1], "", 0);
		close(pipefd[1]);
		free_2char(*dp.args);
		cleanup_minish(sh);
		exit(2);
	}
	write(pipefd[1], content, ft_strlen(content));
	free(content);
	close(pipefd[1]);
	free_2char(*dp.args);
	free_ast(*dp.redirects);
	cleanup_minish(sh);
	exit(0);
}

char	*handle_heredoc_parent(int pipefd[2], pid_t pid)
{
	int		status;
	char	*result;

	close(pipefd[1]);
	signal(SIGINT, handle_sigint2);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (WIFSIGNALED(status)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
		return (close(pipefd[0]), NULL);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
		return (close(pipefd[0]), ft_strdup(""));
	result = read_from_child(pipefd[0]);
	close(pipefd[0]);
	return (result);
}

char	*handle_heredoc(t_minish *sh, char *delimiter,
	char ***args, t_ast_node **redirects)
{
	if (!delimiter || !delimiter[0])
	{
		printf("minishell: syntax error: invalid heredoc delimiter\n");
		return (NULL);
	}
	return (fork_heredoc_reader(sh, delimiter, args, redirects));
}
