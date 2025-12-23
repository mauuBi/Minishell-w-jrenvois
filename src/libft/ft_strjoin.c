/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:58:00 by jrenvois          #+#    #+#             */
/*   Updated: 2025/04/28 18:49:26 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	char	*res;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!res)
		return (0);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	i--;
	while (s2[++i - s1_len])
		res[i] = s2[i - s1_len];
	res[i] = '\0';
	return (res);
}
