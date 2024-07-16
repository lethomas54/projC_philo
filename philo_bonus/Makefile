NAME		:=	philo_bonus

COMP		:= 	cc
CFLAGS		:= 	-Wall -Wextra -Werror

SRC			:=	main_bonus.c ft_get_time_bonus.c ft_set_info_bonus.c \
				ft_open_sem_tab_bonus.c ft_create_children_bonus.c ft_wait_for_children_bonus.c \
				ft_close_sem_tab_bonus.c ft_philo_bonus.c ft_philo_sleeping_thinking_bonus.c \
				ft_philo_eating_bonus.c ft_philo_utils_bonus.c ft_death_bonus.c \
				ft_atoi_bonus.c ft_bzero_bonus.c ft_calloc_bonus.c ft_putendl_fd_bonus.c ft_putstr_fd_bonus.c \
				ft_putnbr_fd_bonus.c ft_memset_bonus.c ft_putchar_fd_bonus.c ft_free_bonus.c

SRCS		:= $(addprefix ./srcs/, $(SRC))
OBJ 		:= $(SRCS:.c=.o)
INC			:= philosopher_bonus.h
INCS		:= $(addprefix ./includes/, $(INC))

all: $(NAME)

$(NAME): $(OBJ) Makefile
	@$(COMP) $(CFLAGS) $(OBJ) -o $@ -lpthread
	@echo "\033[0;34m$(NAME) compilation: \033[0;32mOK\033[0;0m"

%.o: %.c $(INCS)
	@$(COMP) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\033[0;31m$(NAME) clean: \033[0;32mOK\033[0;0m"

fclean:
	@rm -f $(OBJ) $(NAME)
	@echo "\033[0;31m$(NAME) fclean: \033[0;32mOK\033[0;0m"

re: fclean all

.PHONY: all clean fclean re
