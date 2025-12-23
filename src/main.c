/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:38:57 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/24 14:34:03 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_num = 0;

void	update_exit_code(t_minish *sh)
{
	if (g_sig_num == SIGINT)
		sh->exit_code = 130;
	g_sig_num = 0;
}

int	init_minish(t_minish *sh, char **envp)
{
	if (!sh)
		return (0);
	sh->env = copy_tab(envp);
	if (!sh->env)
		return (0);
	sh->lexer = ft_calloc(1, sizeof(t_lexer));
	if (!sh->lexer)
		return (0);
	sh->parser = ft_calloc(1, sizeof(t_parser));
	if (!sh->parser)
		return (0);
	sh->stdin_save = -1;
	sh->stdout_save = -1;
	return (1);
}

void	cleanup_minish(t_minish *sh)
{
	if (!sh)
		return ;
	lexer_cleanup(sh->lexer);
	parser_cleanup(sh->parser);
	if (sh->env)
		free_2char(sh->env);
	if (sh->lexer)
		free(sh->lexer);
	if (sh->parser)
		free(sh->parser);
}

void	read_loop(t_minish *sh)
{
	int	parser_err;
	int	lexer_err;

	while (1)
	{
		sh->input = readline("minishell> ");
		if (!sh->input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		update_exit_code(sh);
		lexer_err = lexer_run(sh);
		if (!lexer_err)
		{
			parser_err = parser_run(sh);
			if (!parser_err)
				exec_run(sh);
			if (sh->ast)
				free_ast(sh->ast);
			parser_cleanup(sh->parser);
			lexer_cleanup(sh->lexer);
		}
		free(sh->input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minish	sh;

	(void) ac;
	(void) av;
	sh = (t_minish){0};
	if (!init_minish(&sh, envp))
		return (cleanup_minish(&sh), -1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	read_loop(&sh);
	cleanup_minish(&sh);
	rl_clear_history();
	return (0);
}
