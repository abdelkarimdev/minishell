
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = minishell.c \
	environment.c \
	Utils/utils.c \
	Utils/ft_print_error.c \
	Utils/collector.c \
	Utils/utils2.c \
	Utils/collect_fds.c \
	Signals/setup_signals.c \
	Signals/signals_utils.c \
	Parsing/tokenizer.c \
	Parsing/parsing.c \
	Parsing/handle_heredoc.c \
	Expansion/expand_word.c \
	Expansion/expand_commands.c \
	Expansion/expand_in_heredoc.c \
	Expansion/expansion_utils.c \
	Executor/executor.c \
	Executor/builtins/execute_builtin.c \
	Executor/builtins/ft_cd.c \
	Executor/builtins/ft_echo.c \
	Executor/builtins/ft_env.c \
	Executor/builtins/ft_exit.c \
	Executor/builtins/ft_export.c \
	Executor/builtins/ft_export_helper.c \
	Executor/builtins/ft_export_print.c \
	Executor/builtins/ft_pwd.c \
	Executor/builtins/ft_unset.c \
	Executor/execute_pipeline/execute_pipeline.c \
	Executor/execute_pipeline/helper_function_pipe.c \
	Executor/simple_command/execute_external.c \
	Executor/simple_command/search.c \
	Executor/redirections.c \
	Executor/utils.c \
	Libft_utils/ft_bzero.c \
	Libft_utils/ft_isalpha.c \
	Libft_utils/ft_putstr_fd.c \
	Libft_utils/ft_strcmp.c \
	Libft_utils/ft_strjoin.c \
	Libft_utils/ft_substr.c \
	Libft_utils/ft_calloc.c \
	Libft_utils/ft_isdigit.c \
	Libft_utils/ft_split.c \
	Libft_utils/ft_strdup.c \
	Libft_utils/ft_strlen.c \
	Libft_utils/ft_isalnum.c \
	Libft_utils/ft_itoa.c \
	Libft_utils/ft_strchr.c \
	Libft_utils/ft_strncmp.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
