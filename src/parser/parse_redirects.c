/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 02:34:56 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 16:42:51 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirect_type(t_token *redirect)
{
	if (redirect->type == TOKEN_REDIRECT_IN)
		return (0);
	else if (redirect->type == TOKEN_REDIRECT_OUT)
		return (1);
	else if (redirect->type == TOKEN_APPEND)
		return (2);
	else if (redirect->type == TOKEN_HEREDOC)
		return (3);
	return (-1);
}

int	get_fd_from(int redirect_type)
{
	if (redirect_type == 0)
		return (0);
	else if (redirect_type == 1)
		return (1);
	else if (redirect_type == 2)
		return (1);
	else if (redirect_type == 3)
		return (0);
	return (0);
}

void	append_redirects(t_ast_node **redirects, t_ast_node *redirect)
{
	t_ast_node	*current;

	if (!redirects || !redirect)
		return ;
	if (!*redirects)
	{
		*redirects = redirect;
		return ;
	}
	current = *redirects;
	while (current->right)
		current = current->right;
	current->right = redirect;
}

static char	*get_redirect_content(t_minish *sh, int type,
	char ***args, t_ast_node **redirects)
{
	char	*content_or_file;

	if (type == 3)
	{
		content_or_file = handle_heredoc(sh, sh->parser->current->value,
				args, redirects);
		if (!content_or_file)
			return (NULL);
	}
	else
		content_or_file = ft_strdup(sh->parser->current->value);
	return (content_or_file);
}

t_ast_node	*parse_single_redirect(t_minish *sh, char ***args,
	t_ast_node **redirects)
{
	t_ast_node	*redirect;
	int			type;
	int			fd_from;
	char		*content_or_file;

	if (!is_token_redirection(sh->parser->current))
		return (NULL);
	type = get_redirect_type(sh->parser->current);
	if (type == -1)
		return (NULL);
	fd_from = get_fd_from(type);
	parser_go(sh->parser);
	if (!sh->parser->current)
		return (NULL);
	content_or_file = get_redirect_content(sh, type, args, redirects);
	if (!content_or_file)
		return (NULL);
	redirect = create_redirect_node(content_or_file, fd_from, type);
	free(content_or_file);
	if (!redirect)
		return (NULL);
	return (parser_go(sh->parser), redirect);
}
