/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:29:40 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 16:22:48 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_cmd_node(char **args, t_ast_node *redirects)
{
	t_ast_node	*cmd_node;

	cmd_node = create_ast_node(NODE_CMD);
	if (!cmd_node)
		return (NULL);
	cmd_node->args = args;
	cmd_node->redirects = redirects;
	return (cmd_node);
}

t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*pipe_node;

	pipe_node = create_ast_node(NODE_PIPE);
	if (!pipe_node)
		return (NULL);
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

t_ast_node	*create_op_node(t_ast_node *left, t_ast_node *right, int op_type)
{
	t_ast_node	*op_node;

	op_node = create_ast_node(NODE_OPERATOR);
	if (!op_node)
		return (NULL);
	op_node->left = left;
	op_node->right = right;
	op_node->operator_type = op_type;
	return (op_node);
}

t_ast_node	*create_list_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*list_node;

	list_node = create_ast_node(NODE_LIST);
	if (!list_node)
		return (NULL);
	list_node->left = left;
	list_node->right = right;
	return (list_node);
}

t_ast_node	*create_redirect_node(char *file, int fd_from, int type)
{
	t_ast_node	*redirect_node;

	redirect_node = create_ast_node(NODE_REDIRECT);
	if (!redirect_node)
		return (NULL);
	redirect_node->fd_from = fd_from;
	redirect_node->redirect_type = type;
	redirect_node->redirect_file = ft_strdup(file);
	if (!redirect_node->redirect_file)
	{
		free(redirect_node);
		return (NULL);
	}
	return (redirect_node);
}
