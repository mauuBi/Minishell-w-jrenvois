/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:17:08 by jrenvois          #+#    #+#             */
/*   Updated: 2025/04/28 20:07:22 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char ) s1[i] || (unsigned char ) s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char ) s1[i] - (unsigned char ) s2[i]);
		i++;
	}
	return (0);
}
