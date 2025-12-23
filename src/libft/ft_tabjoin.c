/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:18:44 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/24 21:31:20 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_full_size(int size, char **strs, char *sep)
{
	int	full_sz;
	int	i;

	i = 0;
	full_sz = size * ft_strlen(sep);
	while (i < size)
	{
		full_sz += ft_strlen(strs[i]);
		i++;
	}
	return (full_sz);
}

int	add_new(char *result, char *new, int index)
{
	int	i;

	i = 0;
	while (new[i])
	{
		result[index] = new[i];
		i++;
		index++;
	}
	return (index);
}

char	*ft_tabjoin(int size, char **strs, char *sep)
{
	int		i;
	int		k;
	char	*result;

	i = 0;
	k = 0;
	if (size == 0)
	{
		result = malloc(1 * sizeof(char));
		result[0] = '\0';
		return (result);
	}
	result = malloc((get_full_size(size, strs, sep) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < size)
	{
		k = add_new(result, strs[i], k);
		if (i != size - 1)
			k = add_new(result, sep, k);
		i++;
	}
	result[k] = '\0';
	return (result);
}
