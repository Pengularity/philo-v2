NAME = philosophers

INCLUDE = ./includes/

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE)

SRCS = src/parsing.c \
			src/libft.c \
			src/utils.c \
			src/main.c \
			src/routine.c \
			src/simulation.c \
			

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread -g

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re