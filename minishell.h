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
	char		*token;
	int			quote_flag;
	struct s_tokens		*next;
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
	int				last_exit;
	t_tokens		*tok;
}	t_shell;

// signails_functions
void		handle_sigs(void);
void		handle_ctrl_c(int sig);
void		handle_cat_ctrl_c(int sig);
void		init_execution(t_exec *exec);

int			read_check(char *line);
int			input_checker(char *input, t_shell *shell);
size_t		ft_strcspn(const char *s, const char *reject);
void		execute_all(char **cmd, t_shell **shell);

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
void		heredoc_term(char **tokens, int i);
char		*my_strtok(char *str, const char *delim);

//redirects && pipes
int			handle_redirections(t_shell *shell, int *def_read, int *def_write);
int			is_redirect(char *token);
void		split_pipes(char *input, char **commands);

// tokens
int			ft_isnumber(char *str);
void		add_or_updt_envs(char *key, char *value, t_evar **env_list);
void		print_tokens(t_tokens *head);
void		tokenize(char *input, t_tokens **head);

// matrix && lists
void		ft_free(char **str);
void		free_matrix(char **matrix);
void		free_tokens(char **tokens);
void		free_tokens_list(t_tokens *list);
void		free_env_list(t_evar *list);
void		fill_env_list(char **env, t_evar **list);
char		**generate_matrix(t_evar *env_list);
char		**generate_tokens_matrix(t_tokens *tokens_list);
int			ft_strcmp(char *s1, char *s2);

//extern_cmd && pipes
void		execute_extern_command(t_shell *shell);
void		execute_pipeline(t_shell **shell, t_exec *exec, int has_next);
void		exec_with_pipes(char **tokens, t_evar *env);
void		update_exit_var(t_evar **env, char *value);
void		wait_for_processes(t_exec *exec, t_shell **shell);

// program_execution
void		init_program(t_shell **shell, char **env);
void		main_loop(t_shell *shell);

char		*get_value(char *key, t_shell *shell);
char		*expand_vars(char *input, t_shell *shell);
char		*ft_strjoin_free(char *s1, char *s2, int free_s1);

#endif
