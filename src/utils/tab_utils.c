/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:08:45 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/31 14:30:33 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_size(char ***tab)
{
	int	i;

	if (!tab || !*tab)
		return (0);
	i = 0;
	while ((*tab)[i])
		i++;
	return (i);
}

int	realloc_tab(char ***tab, int add_size)
{
	int		i;
	int		old_size;
	char	**tmp;

	if (!tab || add_size < 0)
		return (-1);
	old_size = tab_size(tab);
	tmp = ft_calloc(old_size + add_size + 1, sizeof(char *));
	if (!tmp)
		return (-1);
	i = 0;
	if (*tab)
	{
		while ((*tab)[i])
		{
			tmp[i] = (*tab)[i];
			i++;
		}
		free(*tab);
	}
	*tab = tmp;
	return (0);
}

static void	copy_tab_without_index(char **src, char **dst, int skip_index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (i != skip_index)
		{
			dst[j] = src[i];
			j++;
		}
		else
		{
			free(src[i]);
		}
		i++;
	}
}

int	remove_tab_element(char ***tab, int index)
{
	int		old_size;
	char	**tmp;

	if (!tab || !*tab || index < 0)
		return (-1);
	old_size = tab_size(tab);
	if (index >= old_size)
		return (-1);
	tmp = ft_calloc(old_size, sizeof(char *));
	if (!tmp)
		return (-1);
	copy_tab_without_index(*tab, tmp, index);
	free(*tab);
	*tab = tmp;
	return (0);
}

char	**copy_tab(char **tab)
{
	char	**new_tab;
	int		i;
	int		size;

	if (!tab)
		return (NULL);
	size = 0;
	while (tab[size])
		size++;
	new_tab = ft_calloc(size + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_tab[i] = ft_strdup(tab[i]);
		if (!new_tab[i])
		{
			free_2char(new_tab);
			return (NULL);
		}
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
