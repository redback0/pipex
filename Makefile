CC = cc

ifeq ($(DEBUG), 1)
	CFLAGS = -Wall -Wextra -Werror -g
	export DEBUG
else
	CFLAGS = -Wall -Wextra -Werror
endif

NAME = pipex

SRC = pipex.c \
	  pipex_utils.c \

OBJ = $(SRC:.c=.o)

#LIBFT VARIABLES
LIBFT = libft/libft.a
LIBFT_DIR = libft

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
C_CYAN = \033[0;36m
NC = \033[0m

PREFIX = $(C_ORANGE)<$(NAME)>$(NC)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@printf "$(PREFIX) CREATING $(C_CYAN)$(NAME)$(NC)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(LIBFT):
	@printf "$(PREFIX) MAKING $(C_CYAN)$(LIBFT)$(NC) ARCHIVE\n"
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@printf "$(PREFIX) $(C_GRAY)COMPILING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) $(DEFINES) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@printf "$(PREFIX) $(C_RED)REMOVING OBJECT FILES$(NC)\n"
	@rm -f $(OBJ)
	@$(MAKE) fclean -C $(LIBFT_DIR)

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
