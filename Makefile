
#	███╗   ███╗ █████╗ ██╗  ██╗███████╗███████╗██╗██╗     ███████╗
#	████╗ ████║██╔══██╗██║ ██╔╝██╔════╝██╔════╝██║██║     ██╔════╝
#	██╔████╔██║███████║█████╔╝ █████╗  █████╗  ██║██║     █████╗
#	██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  ██╔══╝  ██║██║     ██╔══╝
#	██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗██║     ██║███████╗███████╗
#	╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝

NAME = pipex

CC		 = cc
CFLAGS   = -Wall -Werror -Wextra
AR		 = ar rcs
RM		 = rm -rf
FSANITIZE = -fsanitize=address -g
LINKFLAGS = 
LSAN			=	LeakSanitizer
LSANLIB			=	/LeakSanitizer/liblsan.a

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
			$(CC) $(CFLAGS) $(OBJS) $(LINK_FLAGS) $(LIBFT) -o $(NAME)

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

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
#	LINK_FLAGS += -ltinfo
	LSANLFLAGS := -rdynamic -LLeakSanitizer -llsan -ldl -lstdc++
endif
ifeq ($(UNAME_S),Darwin)
	LSANLFLAGS := -LLeakSanitizer -llsan -lc++
endif


lsan: CFLAGS += -ILeakSanitizer -Wno-gnu-include-next
lsan: LINK_FLAGS += $(LSANLFLAGS)
lsan: fclean $(LSANLIB)
lsan: all
$(LSAN):
	git clone https://github.com/mhahnFr/LeakSanitizer.git
$(LSANLIB): $(LSAN)
	@$(MAKE) -C LeakSanitizer

.PHONY: all clean fclean re
