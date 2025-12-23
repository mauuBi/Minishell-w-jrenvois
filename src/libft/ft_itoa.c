/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:00:34 by jrenvois          #+#    #+#             */
/*   Updated: 2025/04/28 20:57:38 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long	nbr;
	int		nb_len;
	char	*res;

	nbr = (long) n;
	nb_len = (nbr <= 0);
	while (n != 0)
	{
		n /= 10;
		nb_len++;
	}
	res = malloc((nb_len + 1) * sizeof(char));
	if (!res)
		return (0);
	if (nbr < 0)
		res[0] = '-';
	res[nb_len] = '\0';
	n = (int) nbr;
	while (nb_len > (n < 0))
	{
		res[nb_len - 1] = ((nbr % 10) * (1 - 2 * (n < 0))) + '0';
		nb_len--;
		nbr /= 10;
	}
	return (res);
}
