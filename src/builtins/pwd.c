/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:34:14 by jrenvois          #+#    #+#             */
/*   Updated: 2025/07/22 16:51:19 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: error handler
int	ft_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		return (-1);
	}
	ft_putstr_fd(current_dir, 1);
	ft_putstr_fd("\n", 1);
	free(current_dir);
	return (0);
}
