/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:02:50 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 20:15:45 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*create_ast_node(t_node_type type)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}

void	free_ast(t_ast_node *ast)
{
	if (!ast)
		return ;
	if (ast->type == NODE_REDIRECT)
		free(ast->redirect_file);
	if (ast->type == NODE_CMD)
		free_2char(ast->args);
	free_ast(ast->redirects);
	free_ast(ast->right);
	free_ast(ast->left);
	free(ast);
}
