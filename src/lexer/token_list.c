/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:06:39 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/06 09:35:22 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token_list *list)
{
	t_token	*current;
	t_token	*tmp;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		tmp = current->next;
		free_token(current);
		current = tmp;
	}
	free(list);
}

t_token	*add_token(t_token_list	*list, t_token_type type, char *value)
{
	t_token	*res;

	if (!list)
		return (NULL);
	res = create_token(type, value);
	if (!res)
		return (NULL);
	res->next = NULL;
	res->prev = list->tail;
	if (list->tail)
		list->tail->next = res;
	else
		list->head = res;
	list->tail = res;
	return (res);
}

void	remove_token(t_token_list *list, t_token *token)
{
	if (!list || !token)
		return ;
	if (token->prev)
		token->prev->next = token->next;
	else
		list->head = token->next;
	if (token->next)
		token->next->prev = token->prev;
	else
		list->tail = token->prev;
	free_token(token);
}

int	count_tokens(t_token_list *list)
{
	t_token	*current;
	int		i;

	if (!list || !list->head)
		return (0);
	i = 0;
	current = list->head;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
