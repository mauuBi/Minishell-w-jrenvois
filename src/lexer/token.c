/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 08:56:50 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/06 09:06:27 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*res;

	if (!value)
		return (NULL);
	res = ft_calloc(1, sizeof(t_token));
	if (!res)
		return (NULL);
	res->type = type;
	res->value = ft_strdup(value);
	if (!res->value)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}
