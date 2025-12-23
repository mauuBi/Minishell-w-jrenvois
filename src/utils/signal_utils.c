/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:07:24 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/28 00:41:58 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	g_sig_num = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_redisplay();
}

void	handle_sigint2(int sig)
{
	(void) sig;
}

void	child_sigint_handler(int sig)
{
	if (sig == 3)
	{
		return ;
	}
	write(1, "\n", 1);
	close(0);
}

void	disable_control_echo(struct termios *old_termios)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, old_termios);
	new_termios = *old_termios;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}
