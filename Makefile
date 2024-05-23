NAME = philosophers

CC = cc
CFLAGS = -Wextra -Werror -Wall -g -pthread
RM = rm -f

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
YELLOW=\033[0;33m
RESET=\033[0m

SRC =	main.c \
		actions.c \
		destroy.c \
		init.c \
		print.c \
		philo_routine.c \
		room_routine.c \
		utils.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -I. $(SRC) -o $(NAME)
	@echo "$(GREEN)	PHILOSOPHERS COMPILED!$(RESET)"

clean:

fclean: clean
	$(RM) $(NAME)

re: fclean all