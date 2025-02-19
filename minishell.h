/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:30:16 by txavier           #+#    #+#             */
/*   Updated: 2025/02/13 18:12:31 by txavier          ###   ########.fr       */
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

/*pedef struct s_order
{
	char	**normal;
	char	**redir;
	int		normal_count;
	int		redir_count;
}	t_order;*/

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
}	t_shell;

void		handle_sigs(void);
void		handle_ctrl_c(int sig);
void		handle_cat_ctrl_c(int sig);
int			read_check(char *line);
int			is_valid_env(const char *key);
int			input_checker(char *input, t_shell *shell);
int			is_builtin(char *cmd);
int			handle_redirections(char **tokens, int *def_r, int *def_w, int *flag);
size_t		ft_strcspn(const char *s, const char *reject);
void		execute_all(char **cmd, t_shell **shell);
void		split_pipes(char *input, char **commands);
void		init_execution(t_exec *exec);
void		exec_builtin(char **tokens, t_shell **shell);
void		update_exit_var(t_evar **env, char *value);
void		free_matrix(char **matrix);
int			ft_isnumber(char *str);
void		exec_with_pipes(char **tokens, t_evar *env);
void		execute_extern_command(char **tokens, t_shell *shell);
char		**generate_matrix(t_evar *env_list);
void		free_env_list(t_evar *list);
void		main_loop(t_shell *shell);
void		wait_for_processes(t_exec *exec, t_shell **shell);
void		add_or_updt_envs(char *key, char *value, t_evar **env_list);
void		ft_cd(char **args, t_shell *shell);
void		heredoc_term(char **tokens, int i);
void		free_tokens(char **tokens);
void		execute_pipeline(char **tokens, t_shell **shell,
				t_exec *exec, int has_next);
void		fill_env_list(char **env, t_evar **list);
void		ft_unset(char **args, t_shell *shell);
void		exit_program(t_shell *shell);
void		init_program(t_shell **shell, char **env);
void		builtin_exit(char **args, t_shell *shell);
void		ft_env(t_shell **shell, char **tokens);
void		ft_pwd(t_shell *shell);
void		ft_free(char **str);
int			ft_strcmp(char *s1, char *s2);
int			handle_builtin(char **tokens, t_shell **shell, t_exec *exec);
int			handle_heredoc(char **tokens, int i);
int			handle_input_redirection(char **tokens, int i);
int			handle_double_output_redirection(char **tokens, int i);
int			handle_simple_output_redirection(char **tokens, int i);
void		execute_redirect(char **tokens, int *flag);
void		ft_export(char **args, t_shell *shell);
void		ft_echo(char **input, t_shell *shell);
int			reorder_tokens(char **tokens, int flag);
char		*my_strtok(char *str, const char *delim);
char		*get_value(char *key, t_shell *shell);
char		*expand_vars(char *input, t_shell *shell);
char		*ft_strjoin_free(char *s1, char *s2, int free_s1);
void		tokenize_inputs(char *input, char **args, int *flag);

#endif
