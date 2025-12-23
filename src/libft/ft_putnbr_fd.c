/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:54:02 by jrenvois          #+#    #+#             */
/*   Updated: 2025/04/28 18:40:55 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_rec(int n, int fd)
{
	char	to_print;

	if (n == 0)
		return ;
	ft_putnbr_rec(n / 10, fd);
	to_print = (n % 10) + '0';
	write(fd, &to_print, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	ft_putnbr_rec(n, fd);
}
