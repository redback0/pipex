CC = cc

ifeq ($(DEBUG), 1)
	CFLAGS = -Wall -Wextra -Werror -g
else
	CFLAGS = -Wall -Wextra -Werror
endif

NAME = pipex

SRC = pipex.c \
	  pipex_utils.c \

OBJ = $(SRC:.c=.o)

#LIBFT VARIABLES
LIBFT = libft

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

$(NAME): $(OBJ) $(LIBFT).a
	@printf "$(PREFIX) CREATING $(C_CYAN)$(NAME)$(NC)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT).a

$(LIBFT).a: $(LIBFT).h
	@printf "$(PREFIX) MAKING $(C_CYAN)$(LIBFT)$(NC) ARCHIVE\n"
	@$(MAKE) -C $(LIBFT)
	@mv $(LIBFT)/$(LIBFT).a .

$(LIBFT).h:
	@printf "$(PREFIX) $(C_GRAY)GETTING LIBFT HEADER$(NC)\n"
	@cp $(LIBFT)/$(LIBFT).h .

%.o: %.c $(LIBFT).h
	@printf "$(PREFIX) $(C_GRAY)COMPILING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@

clean:
	@printf "$(PREFIX) $(C_RED)REMOVING OBJECT FILES$(NC)\n"
	@rm -f $(OBJ) $(LIBFT).a $(LIBFT).h
	@$(MAKE) fclean -C $(LIBFT)

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
