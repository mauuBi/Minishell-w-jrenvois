/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 01:55:46 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/23 20:13:14 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg_array(char ***args, int *count, char *arg)
{
	char	**new;
	int		i;

	if (!args || !count || !arg)
		return ;
	new = ft_calloc(*count + 2, sizeof(char *));
	if (!new)
		return ;
	i = 0;
	while (i < *count)
	{
		new[i] = ft_strdup((*args)[i]);
		if (!new[i])
			return (free_2char(new));
		i++;
	}
	new[i] = ft_strdup(arg);
	new[i + 1] = NULL;
	if (!new[i])
		return (free_2char(new));
	(*count)++;
	free_2char(*args);
	*args = new;
}

void	init_args(char ***a, t_ast_node **old, int *c, t_ast_node **new)
{
	*a = NULL;
	*old = NULL;
	*new = NULL;
	*c = 0;
}

static int	is_valid(t_parser *parser)
{
	return (is_token_redirection(parser->current)
		|| is_token_cmd(parser->current));
}

static t_ast_node	*return_result(char **args, t_ast_node *redirects, int c)
{
	if (c == 0 && !redirects)
		return (NULL);
	return (create_cmd_node(args, redirects));
}

t_ast_node	*parse_command(t_minish *sh)
{
	char		**args;
	t_ast_node	*redirects;
	int			args_count;
	t_ast_node	*new_redirect;

	init_args(&args, &redirects, &args_count, &new_redirect);
	if (!is_valid(sh->parser))
		return (NULL);
	while (sh->parser->current && is_valid(sh->parser))
	{
		if (is_token_cmd(sh->parser->current))
		{
			add_arg_array(&args, &args_count, sh->parser->current->value);
			parser_go(sh->parser);
		}
		else if (is_token_redirection(sh->parser->current))
		{
			new_redirect = parse_single_redirect(sh, &args, &redirects);
			if (new_redirect)
				append_redirects(&redirects, new_redirect);
			else
				return (free_2char(args), free_ast(redirects), NULL);
		}
	}
	return (return_result(args, redirects, args_count));
}
