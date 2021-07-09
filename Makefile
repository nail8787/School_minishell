NAME			=	minishell

FLAGS			=	-Wall -Wextra -Werror

SRCS 			=	main.c			get_next_line.c		env_utils.c		mem_utils.c 		\
					words_utils.c	split_command.c		parse_check.c	special_symbols.c	\
					command_init.c  parse_redirect.c	error.c			syntax_check.c		\
					dolla.c \
					binary.c		cd_relative.c		cd_utils.c		cd.c				\
					env.c			export_no_args.c	export.c		unset.c				\
					choose_cmd.c	pwd.c				echo.c			error_checks.c  	\
					check_for_pipe_and_rd.c				signals.c		cd_chdir.c			\
					change_question.c					exit.c			error_extra.c		\
					pipe.c			find_in_path.c		cd_relative_utils.c

OBJS			=	$(SRCS:.c=.o)

LIBFT_NAME		= 	libft.a
LIBFT_FOLDER	=	./libft/
LIBFT			=	$(LIBFT_FOLDER)$(LIBFT_NAME)

all: $(NAME)

%.o: %.c
	gcc -g $(FLAGS) -I $(LIBFT_FOLDER) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_FOLDER)

$(NAME): $(OBJS) $(LIBFT) minishell.h
	gcc -g $(FLAGS) -lft -L $(LIBFT_FOLDER) $(OBJS) -o $(NAME)

clean:
	make clean -C $(LIBFT_FOLDER)
	rm -f $(OBJS)


fclean: clean
	make fclean -C $(LIBFT_FOLDER)
	rm -f $(NAME)

re: fclean all
