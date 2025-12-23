/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenvois <jrenvois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 08:28:58 by jrenvois          #+#    #+#             */
/*   Updated: 2025/09/28 01:01:08 by jrenvois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>

# define STATE_NORMAL 0
# define STATE_DQUOTE 1
# define STATE_SQUOTE 2

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_DQUOTE,
	TOKEN_SQUOTE,
	TOKEN_PIPE,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_IN,
	TOKEN_APPEND,
	TOKEN_SEMICOLON,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_EOF,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
}	t_token_list;

typedef struct s_quote_stack
{
	char	quotes[20];
	int		top;
}	t_quote_stack;

typedef enum e_lexer_error
{
	LEXER_ERROR_NONE = 0,
	LEXER_ERROR_UNCLOSED_QUOTE,
	LEXER_ERROR_INVALID_OPERATOR,
	LEXER_ERROR_BUFFER_OVERFLOW,
	LEXER_ERROR_MEMORY_ALLOCATION,
	LEXER_ERROR_INVALID_CHARACTER,
}	t_lexer_error;

typedef struct s_lexer
{
	char			*input;
	int				i;
	int				length;
	t_token_list	*tokens;
	char			buffer[1024];
	int				bi;
	int				state;
	t_quote_stack	qstack;
	int				err_code;
	char			*err_msg;
	int				err_pos;
}	t_lexer;

typedef struct s_validator
{
	t_token_list	*tokens;
	int				pos;
	char			*err_msg;
	int				err_code;
}	t_validator;

// Lexer
t_token		*create_token(t_token_type type, char *value);
void		free_token(t_token *token);

void		free_token_list(t_token_list *list);
t_token		*add_token(t_token_list	*list, t_token_type type, char *value);
void		remove_token(t_token_list *list, t_token *token);
int			count_tokens(t_token_list *list);

int			lexer_dispatch(t_lexer *lexer);
int			init_lexer(t_lexer *lexer, char *input);

void		handle_word(t_lexer *lexer);
int			handle_operator(t_lexer *lexer);
void		handle_backslash(t_lexer *lexer);
void		handle_quote(t_lexer *lexer, t_token_type type, int pos);
void		handle_newline(t_lexer *lexer);

void		lexer_set_error(t_lexer *lexer, int code, char *msg, int pos);
int			lexer_has_error(t_lexer *lexer);
void		lexer_cleanup(t_lexer *lexer);

int			validator_validate(t_lexer *lexer);
void		v_error(t_validator *validator, char *token, int code);
void		print_verror(t_validator *validator);
int			is_token_operator(t_token *token);
int			is_token_cmd(t_token *token);
int			is_token_redirection(t_token *token);

// Utils
typedef struct s_atol
{
	int	res;
	int	err_code;
}	t_atol;

int			ft_isspace(char c);
int			is_operator(char c);
char		*expand_buffer(char *buffer, int *buffer_size, int total_read);
void		free_2char(char **tab);
int			realloc_tab(char ***tab, int add_size);
int			tab_size(char ***tab);
int			remove_tab_element(char ***tab, int index);
int			set_env_var(char *key, char *value, char ***env);
int			validate_env_var(char *var);
int			unset_env_var(char *key, char ***env);
int			env_var_index(char *key, char ***env);
char		**copy_tab(char **tab);
t_atol		ft_atol(char *nptr);
void		handle_sigint(int sig);
void		handle_sigint2(int sig);
void		child_sigint_handler(int sig);
void		disable_control_echo(struct termios *old_termios);

extern int	g_sig_num;

// PARSER
typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_OPERATOR,
	NODE_LIST,
	NODE_REDIRECT
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	char				**args;
	struct s_ast_node	*redirects;
	int					operator_type;
	int					redirect_type;
	char				*redirect_file;
	int					fd_from;
}	t_ast_node;

typedef struct s_parser
{
	t_token_list	*tokens;
	t_token			*current;
	int				pos;
	int				err_code;
	char			*err_msg;
}	t_parser;

t_ast_node	*create_ast_node(t_node_type type);
t_ast_node	*create_cmd_node(char **args, t_ast_node *redirects);
t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right);
t_ast_node	*create_op_node(t_ast_node *left, t_ast_node *right, int op_type);
t_ast_node	*create_list_node(t_ast_node *left, t_ast_node *right);
t_ast_node	*create_redirect_node(char *file, int fd_from, int type);
void		free_ast(t_ast_node *ast);
void		free_ast_redirects(t_ast_node *ast);

void		append_redirects(t_ast_node **redirects, t_ast_node *redirect);

void		parser_go(t_parser *parser);
void		parser_cleanup(t_parser	*parser);

// EXPAND
typedef struct s_expand
{
	char	*str;
	char	**env;
	int		exit_code;
	int		pos;
	char	*result;
}	t_expand;

void		process_escape(t_expand *exp);
void		process_single_quotes(t_expand *exp);
void		process_double_quotes(t_expand *exp);
void		process_normal_char(t_expand *exp);
void		add_to_result(t_expand *exp, char *segment);
char		*get_env_value(char *key, char **env);
void		expand_variable(t_expand *exp);
char		*expand_argument(char *arg, char **env, int exit_code);
char		**expand_arguments(char **args, char **env, int exit_code);

// PATH & EXEC UTILS
typedef struct s_cmd_res
{
	char	*path;
	int		error_code;
	char	*error_msg;
}	t_cmd_res;

char		**get_path(char **envp);
t_cmd_res	find_cmd_in_path(char *cmd, char **path);
int			is_builtin(char *cmd);

// MINISHELL
typedef struct s_minish
{
	char		*input;
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast_node	*ast;
	char		**env;
	int			exit_code;
	int			stdin_save;
	int			stdout_save;
}	t_minish;

int			lexer_run(t_minish *sh);
int			parser_run(t_minish *sh);
int			execute_ast(t_ast_node *node, t_minish *sh);
int			exec_run(t_minish *sh);
void		cleanup_minish(t_minish *sh);

// EXEC UTILS
int			standard_redirect(t_ast_node *redirect, t_minish *sh);
void		restore_fds(t_minish *sh);
int			setup_builtin_redirects(t_ast_node *redirects, t_minish *sh);
int			setup_external_redirects(t_ast_node *redirects, t_minish *sh);

// EXEC FUNCTIONS
int			execute_builtin(char **args, t_minish *sh);
int			execute_external(char **args, t_ast_node *redirects, t_minish *sh);
int			execute_pipe(t_ast_node *node, t_minish *sh);

// Debug
void		print_tokens(t_lexer *lexer);
void		print_ast(t_ast_node *node, int indent);

typedef struct s_dptr
{
	t_ast_node	**redirects;
	char		***args;
}	t_dptr;

// AST
t_ast_node	*parse_single_redirect(t_minish *sh, char ***args,
				t_ast_node **redirects);
t_ast_node	*parse_command(t_minish *sh);
t_ast_node	*parse_pipe(t_minish *sh);
t_ast_node	*parse_operator(t_minish *sh);
t_ast_node	*parse_list(t_minish *sh);
t_ast_node	*parse_all(t_minish *sh);

// BUILTINS

typedef struct s_exit
{
	int	code;
	int	need_exit;
}	t_exit;

int			ft_echo(char **args);
int			ft_pwd(void);
int			ft_env(char ***env);
int			ft_export(char **args, char ***env);
int			ft_unset(char **args, char ***env);
int			ft_cd(char **args, char ***env);
t_exit		ft_exit(char **args);

// HEREDOC UTILS
char		*join_nl(char *content, char *line);
int			need_stop_heredoc(char *line, char *delimiter);
char		*read_line_manual(t_minish *sh, t_dptr dp, char *content);
char		*init_heredoc_content(char *content);

// HEREDOC
char		*process_heredoc_line(t_minish *sh, char *content,
				char *line, char ***args);
char		*read_heredoc_lines(t_minish *sh, char *delimiter,
				char *content, t_dptr dp);
char		*read_from_child(int pipefd);
char		*fork_heredoc_reader(t_minish *sh, char *delimiter,
				char ***args, t_ast_node **redirects);

// HEREDOC HANDLER
char		*handle_heredoc(t_minish *sh, char *delimiter,
				char ***args, t_ast_node **redirects);
char		*handle_heredoc_parent(int pipefd[2], pid_t pid);
char		*handle_heredoc_eof(char *content, char *delimiter);
void		handle_heredoc_child(t_minish *sh, int pipefd[2],
				char *delimiter, t_dptr dp);

#endif