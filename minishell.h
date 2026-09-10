/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazounda <aazounda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 04:52:07 by aazounda          #+#    #+#             */
/*   Updated: 2025/08/16 13:33:17 by aazounda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COLLECT 0
# define CLEAR 1

# define SET 0
# define FREE 1
# define GET 2

# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIRECT_IN 2
# define TOKEN_REDIRECT_OUT 3
# define TOKEN_REDIRECT_APPEND 4
# define TOKEN_HEREDOC 5

# define COLLECT_TMPFILE 0
# define UNLINK_ALL 1

# define SET_SIGINT_HND 0
# define SET_SIGQUIT_HND 1
# define GET_SIGINT_HND 2
# define GET_SIGQUIT_HND 3

# define COLLECT_FD 0
# define CLOSE_ALL 1

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_buffer
{
	char				*buffer;
	size_t				pos;
	int					has_empty_str;

}						t_buffer;

typedef struct s_collect
{
	struct s_collect	*next;
	void				*value;
}						t_collect;

typedef struct s_list
{
	struct s_list		*next;
	char				*content;
	int					type;
}						t_list;

typedef struct s_command
{
	struct s_command	*next;
	t_list				*args;
	t_list				*redirects;
}						t_command;

/* signal handling */
void					setup_signals(int set_prev);
void					setup_ignore_signals(void);
void					setup_child_signals(int is_heredoc);
__sighandler_t			prev_handler(int option, __sighandler_t handler);
void					sighandler_interactive(int sig);
void					handle_sigexit_child(int sig);
void					heredoc_sighandler(int sig);

/* libft utils */
char					*ft_substr(char const *str, unsigned int start,
							size_t len);
char					*ft_strdup(const char *str);
void					*ft_calloc(size_t nmemb, size_t size);
char					*ft_itoa(int nbr);
char					**ft_split(char const *str, char c);
char					*ft_strjoin(char const *str1, char const *str2);
void					ft_putstr_fd(char *str, int fd);
size_t					ft_strlen(const char *str);
char					*ft_strchr(const char *str, char c);
int						ft_strncmp(const char *str1, const char *str2,
							size_t n);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						ft_isdigit(int c);
void					ft_bzero(void *s, size_t n);

/* environment */
char					**environment_copy(int option, char **envp);

/* utils */
int						is_whitespace(int c);
int						ft_strcmp(const char *str1, const char *str2);
void					tmpfiles_collector(int option, char *new_file);
void					collector(int option, void *new);
int						add_node(t_list **head, char *_content, int _type);
void					ft_print_error(const char *format, ...);
int						*ft_exit_code(void);
char					**copy_envp(char **envp, int flag);
void					*ft_malloc(size_t size);
void					ft_exit_clean(int exit_code);
int						add_command(t_command **commands, t_list *_args,
							t_list *_redirects);
/* parsing & expansion */
int						tokenizer(const char *input, t_list **tokens);
int						parsing(char *input, t_command **command);
t_list					*expand_word(char *str, int split_flag);
int						expand_cmds(t_command *cmds);
char					*expand_in_heredoc(char *str);
char					*get_var_name(char *content);
char					*get_var_value(char *var_name);
size_t					get_expand_len(char *content);
void					set_to_buffer(char *buffer, size_t *buff_pos,
							char *src);
int						handle_expansion(char *word, size_t *i,
							t_buffer *buffer);
int						handle_heredoc(char **content);
int						ft_strlen_key(char *s);
char					**ft_envp(char **newenv);
void					collect_fds(int option, int fd);

/* ################################################## */
/* .............EXECUTION...HEADER................... */

# define REDIRECT_IN 2
# define REDIRECT_OUT 3
# define REDIRECT_APPEND 4
# define REDIRECT_HEREDOC 5

# define ADD 0
# define CP 1

int						ft_lst_size(t_command *cmd);
int						ft_t_lst_size(t_list *cmd);
int						execute_builtin(t_list *cmd);
int						ft_echo(t_list *cmd);
int						ft_pwd(t_list *cmd);
int						ft_cd(t_list *cmd);
char					*ft_get_pwd_from_env(char **envp);
char					*ft_getenv(char *key);
void					print_str_with_quotes(char *str);
int						ft_export(t_list *args);
size_t					get_len(char *s1, char *s2);
void					ft_swap(char **s1, char **s2);
int						check_identifier(char *var);
void					print_env(char **envp);
int						ft_env(t_list *cmd);
int						ft_unset(t_list *cmd);
int						ft_exit(t_list *cmd);
int						check_arg(char *s);

/* execution */
int						executor(t_command *cmd);
int						check_is_builtin(t_list *cmd);
int						execute_external(t_list *cmd);
int						execute_external_without_fork(t_list *cmd);
char					*found_command(char *cmd);
int						is_valid_absolute_relative_path(char **cmd_path,
							char *cmd);
int						check_command_in_path(char **cmd_path, char *path,
							char *cmd);

int						execute_pipeline(t_command *cmds);
int						ft_exit_status(int status);
void					close_fds(int **fds, int size);
/* redirection */
int						handel_redirections(t_command *cmd);

#endif
