/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:53:18 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/25 16:44:28 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	real_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\f'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v');
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '&' || c == ';');
}

t_atol	ft_atol(char *nptr)
{
	int		sign;
	int		i;
	t_atol	res;

	i = 0;
	res = (t_atol){0};
	sign = 1;
	while (real_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	if (!nptr[i])
		return (res.err_code = 1, res);
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (res.err_code = 1, res);
		res.res = 10 * res.res + (nptr[i] - '0');
		i++;
	}
	return (res.res = res.res * sign, res);
}

char	*expand_buffer(char *buffer, int *buffer_size, int total_read)
{
	char	*new_buffer;
	int		new_size;
	int		i;

	new_size = (*buffer_size) * 2;
	new_buffer = malloc(new_size);
	if (!new_buffer)
		return (NULL);
	i = 0;
	while (i < total_read)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	free(buffer);
	*buffer_size = new_size;
	return (new_buffer);
}
