SRCS = parsing.c main.c ft_malloc.c ft_lst.c philo_utils.c ft_libft.c ft_init.c \
		simulation.c
CFLAGS = -Wall -Wextra -Werror
O_SRCS = $(addprefix object_files/,$(SRCS:.c=.o))

NAME = philo_bonus 
all: $(NAME)
$(NAME): $(O_SRCS)
	cc $(CFLAGS) $(O_SRCS) -o $(NAME)
object_files/%.o:%.c philo.h
	mkdir -p object_files
	cc $(CFLAGS) -c $< -o $@
clean:
	rm -rf object_files
fclean:clean
	rm -rf $(NAME)
re:fclean all