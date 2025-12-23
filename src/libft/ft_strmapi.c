/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:36:27 by jrenvois          #+#    #+#             */
/*   Updated: 2025/04/28 18:41:28 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	s_len;
	char			*res;

	if (!s || !f)
		return (0);
	s_len = 0;
	while (s[s_len])
		s_len++;
	res = malloc((s_len + 1) * sizeof(char));
	if (!res)
		return (0);
	s_len = 0;
	while (s[s_len])
	{
		res[s_len] = f(s_len, s[s_len]);
		s_len++;
	}
	res[s_len] = '\0';
	return (res);
}
