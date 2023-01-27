
#	███╗   ███╗ █████╗ ██╗  ██╗███████╗███████╗██╗██╗     ███████╗
#	████╗ ████║██╔══██╗██║ ██╔╝██╔════╝██╔════╝██║██║     ██╔════╝
#	██╔████╔██║███████║█████╔╝ █████╗  █████╗  ██║██║     █████╗
#	██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  ██╔══╝  ██║██║     ██╔══╝
#	██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗██║     ██║███████╗███████╗
#	╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝

NAME = pipex

CC		 = cc
#CFLAGS   = -Wall -Werror -Wextra
AR		 = ar rcs
RM		 = rm -rf
FSANITIZE = -fsanitize=address -g

.SILENT:
			libft
			clean
			all
			$(NAME)

SRC =		pipex.c						\
			putils.c						\


OBJS =		$(SRC:.c=.o)

LIBFT =	./libft/libft.a

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(OBJS) $(LIBFT) -o $(NAME)
# $(CFLAGS)

$(LIBFT):
			@if [ ! -d "libft" ]; then git clone https://github.com/Pgorner/libft.git; fi
			@cd libft && make && make clean


all :		$(NAME)

clean :
			$(RM) $(OBJS)

fclean :	clean
			@$(RM) $(NAME)
			@$(RM) ./libft

re :		fclean all

libft: $(LIBFT)

.PHONY: all clean fclean re
