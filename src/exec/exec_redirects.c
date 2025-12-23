/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:45:00 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 20:53:19 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirect(char *expanded_file)
{
	int	fd;

	fd = open(expanded_file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(expanded_file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output_redirect(char *expanded_file)
{
	int	fd;

	fd = open(expanded_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(expanded_file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_append_redirect(char *expanded_file)
{
	int	fd;

	fd = open(expanded_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(expanded_file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	handle_heredoc_redirect(char *expanded_file)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	write(pipefd[1], expanded_file, ft_strlen(expanded_file));
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}

int	standard_redirect(t_ast_node *redirect, t_minish *sh)
{
	char	*expanded_file;
	int		result;

	if (!redirect || redirect->type != NODE_REDIRECT)
		return (0);
	expanded_file = expand_argument(redirect->redirect_file, sh->env,
			sh->exit_code);
	if (!expanded_file)
		return (1);
	if (redirect->redirect_type == 0)
		result = handle_input_redirect(expanded_file);
	else if (redirect->redirect_type == 1)
		result = handle_output_redirect(expanded_file);
	else if (redirect->redirect_type == 2)
		result = handle_append_redirect(expanded_file);
	else if (redirect->redirect_type == 3)
		result = handle_heredoc_redirect(expanded_file);
	else
		result = 0;
	free(expanded_file);
	return (result);
}
