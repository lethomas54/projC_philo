NAME		:= philo

COMP		:= 	cc
CFLAGS		:= 	-Wall -Wextra -Werror

SRC			:=	main.c ft_get_time.c \
				ft_init_philo.c ft_create_philo.c ft_end_philo.c \
				ft_philo.c ft_philo_sleeping_thinking.c ft_philo_eating.c \
				ft_philo_utils.c

SRCS		:= $(addprefix ./srcs/, $(SRC))
OBJ 		:= $(SRCS:.c=.o)
INC			:= philosopher.h
INCS		:= $(addprefix ./includes/, $(INC))

LIBNAME = ../libft/libft.a
LIBPATH = ../libft/

all: $(NAME)

bonus: $(NAME_bonus)

$(NAME): $(LIBNAME) $(OBJ) Makefile
	@$(COMP) $(CFLAGS) $(OBJ) -o $@ -L $(LIBPATH) -lft -lpthread
	@echo "\033[0;34m$(NAME) compilation: \033[0;32mOK\033[0;0m"

$(LIBNAME):
	@make -C $(LIBPATH) all

%.o: %.c $(INCS)
	@$(COMP) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBPATH) clean
	@rm -f $(OBJ)
	@echo "\033[0;31m$(NAME) clean: \033[0;32mOK\033[0;0m"

fclean:
	@make -C $(LIBPATH) fclean
	@rm -f $(OBJ) $(NAME)
	@echo "\033[0;31m$(NAME) fclean: \033[0;32mOK\033[0;0m"

re: fclean all

.PHONY: all clean fclean re
