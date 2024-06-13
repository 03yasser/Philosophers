SRCS = parsing.c main.c ft_malloc.c ft_lst.c philo_utils.c mutex_func.c ft_libft.c ft_init.c \
		simulation.c ft_clean.c
CFLAGS =  -Wall -Wextra -Werror -fsanitize=thread
O_SRCS = $(addprefix object_files/,$(SRCS:.c=.o))

NAME = philo
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