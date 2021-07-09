NAME 		 = 	libft.a
INCLUDE 	 = 	libft.h

CC			 = 	gcc
CFLAGS		 =	-Wall -Wextra -Werror -c
SOURCE  	 =	ft_atoi.c		ft_isalpha.c	ft_isdigit.c 	ft_isascii.c \
				ft_isprint.c	ft_isalnum.c 	ft_toupper.c 	ft_tolower.c \
				ft_strncmp.c 	ft_memcmp.c 	ft_strlen.c 	ft_strlcpy.c \
				ft_strlcat.c 	ft_strchr.c		ft_strrchr.c 	ft_putendl_fd.c \
				ft_strdup.c 	ft_bzero.c 		ft_memset.c 	ft_putchar_fd.c \
				ft_memccpy.c 	ft_memmove.c	ft_memchr.c 	ft_calloc.c \
				ft_itoa.c 		ft_strjoin.c 	ft_substr.c 	ft_putnbr_fd.c \
				ft_strmapi.c 	ft_split.c		ft_memcpy.c		ft_putstr_fd.c \
				ft_strtrim.c	ft_strnstr.c 	ft_strcmp.c 	\
				ft_lstnew.c		ft_lstsize.c	ft_lstlast.c	ft_lstadd_front.c \
				ft_lstclear.c	ft_lstiter.c	ft_lstmap.c		ft_lstadd_back.c \
				ft_lstdelone.c 
				
OBJ 	 	 = 	$(SOURCE:.c=.o)

.PHONY: all clean fclean re
				
all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
		@echo "-- Linking base static library..."
		@ar -rcs $(NAME) $(OBJ)
		make clean

%.o: %.c $(INCLUDE)
		@$(CC) $(CFLAGS) $< -o $@

clean:
		@echo "-- Removing object files..."
		@/bin/rm -f $(OBJ)
 
fclean: clean
		@echo "-- Removing static Library..."
		@/bin/rm -f $(NAME)

re: fclean all