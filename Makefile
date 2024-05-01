CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex

SRC = pipex.c \

OBJ = $(SRC:.c=.o)

#LIBFT VARIABLES

#LOGGING DEFINES
LOGLEVEL ?= 4
LOGERROR ?= 4
export LOGLEVEL
export LOGERROR

DEFINES = -DLOGLEVEL=$(LOGLEVEL) -DLOGERROR=$(LOGERROR)

#PREFIX/COLOUR VARIABLES
C_GRAY = \033[1;30m
C_ORANGE = \033[0;33m
C_RED = \033[0;31m
NC = \033[0m

PREFIX = $(C_ORANGE)<$(NAME)>

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(PREFIX) $(NC)CREATING $(NAME)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	@printf "$(PREFIX) $(C_GRAY)COMPILING $@$(NC)\n"
	@$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@

clean:
	@printf "$(PREFIX) $(C_RED)REMOVING OBJECT FILES$(NC)\n"
	@rm -f $(OBJ)

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
