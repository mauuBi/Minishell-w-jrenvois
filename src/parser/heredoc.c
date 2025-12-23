/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:36:35 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/28 01:00:49 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_heredoc_line(t_minish *sh, char *content,
	char *line, char ***args)
{
	char	*new_content;

	new_content = join_nl(content, line);
	free(line);
	if (!new_content)
	{
		free(content);
		free_2char(*args);
		cleanup_minish(sh);
		exit(1);
	}
	free(content);
	return (new_content);
}

char	*read_heredoc_lines(t_minish *sh, char *delimiter,
	char *content, t_dptr dp)
{
	char			*line;
	struct termios	old_termios;

	signal(SIGINT, child_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	disable_control_echo(&old_termios);
	content = init_heredoc_content(content);
	write(1, "> ", 2);
	while (1)
	{
		line = read_line_manual(sh, dp, content);
		if (!line)
			return (handle_heredoc_eof(content, delimiter));
		if (need_stop_heredoc(line, delimiter))
		{
			free(line);
			break ;
		}
		content = process_heredoc_line(sh, content, line, dp.args);
		write(1, "> ", 2);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	return (content);
}

char	*read_from_pipe(int pipefd, char *buffer, int *total_read,
	int *buffer_size)
{
	int	bytes_read;

	bytes_read = read(pipefd, buffer + *total_read,
			*buffer_size - *total_read - 1);
	while (bytes_read > 0)
	{
		*total_read += bytes_read;
		if (*total_read >= *buffer_size - 1)
		{
			buffer = expand_buffer(buffer, buffer_size, *total_read);
			if (!buffer)
				return (NULL);
		}
		bytes_read = read(pipefd, buffer + *total_read,
				*buffer_size - *total_read - 1);
	}
	return (buffer);
}

char	*read_from_child(int pipefd)
{
	char	*buffer;
	int		buffer_size;
	int		total_read;

	buffer_size = 4096;
	buffer = malloc(buffer_size);
	if (!buffer)
		return (NULL);
	total_read = 0;
	buffer = read_from_pipe(pipefd, buffer, &total_read, &buffer_size);
	if (!buffer)
		return (NULL);
	buffer[total_read] = '\0';
	if (total_read == 0)
		return (free(buffer), ft_strdup(""));
	return (buffer);
}

char	*fork_heredoc_reader(t_minish *sh, char *delimiter,
	char ***args, t_ast_node **redirects)
{
	int		pipefd[2];
	pid_t	pid;
	t_dptr	dp;

	dp.args = args;
	dp.redirects = redirects;
	if (pipe(pipefd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), NULL);
	if (pid == 0)
		handle_heredoc_child(sh, pipefd, delimiter, dp);
	return (handle_heredoc_parent(pipefd, pid));
}
