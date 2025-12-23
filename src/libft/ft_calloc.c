/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:01:15 by jrenvois          #+#    #+#             */
/*   Updated: 2025/04/28 20:26:16 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	mul;
	void	*res;

	if (size != 0 && nmemb > ((size_t)-1) / size)
		return (0);
	mul = nmemb * size;
	res = malloc(mul);
	if (!res)
		return (0);
	i = 0;
	while (i < mul)
	{
		((unsigned char *) res)[i] = 0;
		i++;
	}
	return (res);
}
