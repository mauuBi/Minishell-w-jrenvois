/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:32:59 by jrenvois          #+#    #+#             */
/*   Updated: 2025/04/28 18:49:39 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_letters(char const *s1, char const *set)
{
	int	i;
	int	flag;
	int	to_remove;

	i = 0;
	while (is_in_set(s1[i], set))
		i++;
	to_remove = i;
	flag = 0;
	while (s1[i])
	{
		if (!is_in_set(s1[i], set))
			flag = 0;
		else
			flag++;
		i++;
	}
	return (ft_strlen(s1) - (to_remove + flag));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		nb_letters;
	char	*res;

	nb_letters = count_letters(s1, set);
	res = malloc((nb_letters + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (is_in_set(s1[i], set))
		i++;
	j = 0;
	while (j < nb_letters)
	{
		res[j] = s1[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
