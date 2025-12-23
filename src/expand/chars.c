/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:55:38 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/25 18:55:53 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_escape(t_expand *exp)
{
	exp->pos++;
	add_to_result(exp, ft_substr(exp->str, exp->pos, 1));
	exp->pos++;
}

void	process_normal_char(t_expand *exp)
{
	add_to_result(exp, ft_substr(exp->str, exp->pos, 1));
	exp->pos++;
}
