/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:35:00 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 20:57:15 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(t_minish *sh)
{
	if (sh->stdin_save != -1)
	{
		dup2(sh->stdin_save, STDIN_FILENO);
		close(sh->stdin_save);
		sh->stdin_save = -1;
	}
	if (sh->stdout_save != -1)
	{
		dup2(sh->stdout_save, STDOUT_FILENO);
		close(sh->stdout_save);
		sh->stdout_save = -1;
	}
}

int	setup_builtin_redirects(t_ast_node *redirects, t_minish *sh)
{
	t_ast_node	*current;
	int			stdin_save;
	int			stdout_save;

	if (!redirects)
		return (0);
	stdin_save = dup(STDIN_FILENO);
	stdout_save = dup(STDOUT_FILENO);
	if (stdin_save == -1 || stdout_save == -1)
		return (1);
	sh->stdin_save = stdin_save;
	sh->stdout_save = stdout_save;
	current = redirects;
	while (current)
	{
		if (standard_redirect(current, sh))
		{
			restore_fds(sh);
			return (1);
		}
		current = current->right;
	}
	return (0);
}

int	setup_external_redirects(t_ast_node *redirects, t_minish *sh)
{
	t_ast_node	*current;

	if (!redirects)
		return (0);
	current = redirects;
	while (current)
	{
		if (standard_redirect(current, sh))
			exit(1);
		current = current->right;
	}
	return (0);
}
