/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:30:16 by txavier           #+#    #+#             */
/*   Updated: 2025/02/21 16:20:27 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <errno.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

extern int	g_sig;

typedef struct s_tokens
{
	int				quote_flag;
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_exec
{
	int		fd[2];
	int		prev_fd;
	int		def_r;
	int		def_w;
	int		status;
	pid_t	pid;
}	t_exec;

typedef struct s_evar
{
	char			*name;
	char			*value;
	struct s_evar	*next;
}	t_evar;

typedef struct s_shell
{
	t_evar		*env_list;
	char		*program_name;
	int			last_exit;
	t_tokens	*tok;
}	t_shell;

void		execute_all(char **cmd, t_shell **shell);
int			check_syntax_errors(char *input, t_shell *shell);
int			read_check(char	*line);
int			read_check(char	*line);

// builtins
int			handle_simple_builtin(t_shell **shell, t_exec *exec);
int			is_builtin(char *cmd);
int			is_valid_env(const char *key);
void		builtin_exit(t_shell *shell);
void		exec_builtin(t_shell **shell);
void		exit_program(t_shell *shell);
void		ft_cd(t_shell *shell);
void		ft_echo(t_shell *shell);
void		ft_env(t_shell **shell);
void		ft_export(t_shell *shell);
void		ft_pwd(t_shell *shell);
void		ft_unset(t_shell *shell);
char		*my_strtok(char *str, const char *delim);

//redirects && pipes
int			handle_heredoc(t_tokens *current);
int			handle_simple_output_redirection(t_tokens *current);
int			handle_double_output_redirection(t_tokens *current);
int			handle_input_redirection(t_tokens *current);
int			handle_redirections(t_shell *shell, int *def_read, int *def_write);
int			is_redirect(char token);
int			process_redirection(t_tokens *current);
int			reset_heredoc_line(int pipefd[2], char **line,
				int len_line, char **delim);
void		save_def_fds(int *def_read, int	*def_write);
void		split_pipes(char *input, char ***commands);
void		term_redirs(t_tokens *current, t_tokens *next, int fd);
void		heredoc_term(char **line, int pipefd[2],
				char **token1, char **token2);

// init && signals
void		handle_sigs(void);
void		handle_ctrl_c(int sig);
void		handle_cat_ctrl_c(int sig);
void		init_execution(t_exec *exec);

// input && tokens
t_tokens	*new_token(char *token, int quote_flag);
int			ft_isnumber(char *str);
int			skip_spaces(char *input, int i);
int			check_pipe_errors(char *input, int i, t_shell *shell);
int			check_redirection_errors(char *input, int i, t_shell *shell);
int			check_pipe_redir_sequence(char *input, int i, t_shell *shell);
int			read_check(char *line);
int			input_checker(char *input, t_shell *shell);
int			handle_word(char *input, int i, t_tokens **head, int *quote_flag);
int			handle_normal_part(char *input, int i, char **token);
int			check_invalid_syntax(char *input, t_shell *shell);
int			check_invalid_operators(char *input);
int			handle_quoted_part(char *input, int i, char **token,
				int *quote_flag);
size_t		ft_strcspn(const char *s, const char *reject);
//int			check_redirection_errors(char **matrix, int i);
void		add_or_updt_envs(char *key, char *value, t_evar **env_list);
void		print_tokens(t_tokens *head);
void		tokenize(char *input, t_tokens **head);
void		add_token(t_tokens **list, char *token, int quote_flag);
char		*ft_strncpy(char *dest, char *src, int i);
char		*ft_strcpy(char *s1, char *s2);
char		*ft_strcat(char *s1, char *s2);
char		*extract_token(char *start, int length);
char		*concat_tokens(char *tokens1, char *tokens2);

// matrix && lists
void		ft_free(char **str);
void		free_matrix(char **matrix);
void		print_error(char c, int n_l);
int			validate_operators(char **matrix);
char		**create_matrix(char *input, int len);
void		free_tokens(char **tokens);
void		free_tokens_list(t_tokens *list);
void		free_env_list(t_evar *list);
void		fill_env_list(char **env, t_evar **list);
char		**generate_matrix(t_evar *env_list);
char		**generate_tokens_matrix(t_tokens *tokens_list);
int			ft_strcmp(char *s1, char *s2);
void		update_shell_exit(t_shell *shell, int exit_code, char *message);

//extern_cmd && pipes
int			count_commands(char *input);
int			check_unclosed_quotes(char *input, t_shell *shell);
void		execute_extern_command(t_shell *shell);
void		execute_pipeline(t_shell **shell, t_exec *exec, int has_next);
void		exec_with_pipes(char **tokens, t_evar *env);
void		update_exit_var(t_evar **env, char *value);
void		wait_for_processes(t_exec *exec, t_shell **shell);
void		update_quote_state(char *temp,
				int *inside_quotes, char *quote_char);
void		split_into_commands(char *input, char **result);
void		handle_pipe_quotes(char **input, int *inside_quotes,
				char *quote_char);
char		*ft_strcpy(char *s1, char *s2);

// program_execution
int			check_unclosed_quotes(char *input, t_shell *shell);
int			is_absolute_or_relative_path(char *cmd);
void		init_program(t_shell **shell, char **env);
void		main_loop(t_shell *shell);
void		cmd_exec_error(int i, char *str);
char		*handle_home_directory(char *cmd, t_shell *shell);
char		*handle_absolute_or_relative_path(char *cmd);
char		*ft_getenv(char *str, t_shell *shell);
char		*find_exec(char **dirs, char *cmd);
char		*search_in_path(char *cmd, t_shell *shell);
char		*get_value(char *key, t_shell *shell);
char		*search_cmd(char *cmd, t_shell *shell);
char		*expand_vars(char *input, t_shell *shell);
char		*ft_strjoin_free(char *s1, char *s2, int free_s1);

#endif
