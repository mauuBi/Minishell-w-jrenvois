/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 00:36:41 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/28 01:03:57 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_hd(t_minish *sh, t_dptr dp, char *content)
{
	free(content);
	free_2char(*dp.args);
	free_ast(*dp.redirects);
	cleanup_minish(sh);
	exit(130);
}

char	*join_nl(char *content, char *line)
{
	char	*tmp;
	char	*str_nl;
	char	*result;

	if (!content || !line)
		return (NULL);
	str_nl = ft_strjoin(line, "\n");
	if (!str_nl)
		return (NULL);
	tmp = content;
	result = ft_strjoin(tmp, str_nl);
	free(str_nl);
	return (result);
}

int	need_stop_heredoc(char *line, char *delimiter)
{
	if (!line || !delimiter)
		return (0);
	return (!ft_strncmp(line, delimiter, INT_MAX));
}

char	*read_line_manual(t_minish *sh, t_dptr dp, char *content)
{
	char	buffer[1024];
	char	*line;
	int		i;
	int		ret;
	char	c;

	i = 0;
	while (i < 1023)
	{
		ret = read(0, &c, 1);
		if (ret < 0)
			clean_hd(sh, dp, content);
		if (ret == 0)
			return (NULL);
		if (c == '\n')
			break ;
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	line = ft_strdup(buffer);
	return (line);
}

char	*init_heredoc_content(char *content)
{
	if (!content)
	{
		content = ft_strdup("");
		if (!content)
			exit(1);
	}
	return (content);
}
