NAME		= philo

SRC = src/main.c \
	src/parsing.c \
	src/cleaning.c \
	src/initialize.c \
	src/philosopher.c \
	src/game_over.c \
	src/monitoring.c \
	src/utils/utils.c \
	src/utils/libft_functions.c

INCLUDES = ./includes

# FLAGS		= -Wall -Werror -Wextra -I includes -pthread -fsanitize=thread -g
FLAGS		=  -Wall -Werror -Wextra -I includes -pthread -g

OBJS		= $(SRC:%.c=%.o)

$(NAME): $(OBJS)
	@cc $(OBJS) $(FLAGS) -I $(INCLUDES) -o $(NAME) -s
	@echo "$(GREEN)[PHILO]:\t PROJECT COMPILED$(RESET)"

all:$(NAME)

%.o: %.c
	@cc -c $< -o $@ $(FLAGS) -I $(INCLUDES)

clean:
	@rm -fr $(OBJS)
	@echo "$(RED)[PHILO]:\t CLEAN$(RESET)"

fclean: clean
	@rm -f *.a
	@rm -f *.out
	@rm -f *.gch
	@rm -f $(NAME)
	@echo "$(RED)[PHILO]:\t FCLEAN$(RESET)"

re: fclean all

test: all
	@echo "$(GREEN)[PHILO]:\t The philosopher should not eat and should die.$(RESET)"
	@read ans
		./$(NAME) 1 800 200 200
	@echo "\n$(GREEN)[PHILO]:\t No philosopher should die.$(RESET)"
	@read ans
		./$(NAME) 5 800 200 200
	@echo "\n$(GREEN)[PHILO]:\t No philosopher should die. $(RESET)"
	@read ans
		./$(NAME) 5 800 200 200 7
	@echo "\n$(GREEN)[PHILO]:\t No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.$(RESET)"
	@read ans
		./$(NAME) 4 410 200 200
	@echo "\n$(GREEN)[PHILO]:\t One philosopher should die.$(RESET)"
	@read ans
		./$(NAME) 4 310 200 100
	@echo "\n$(GREEN)[PHILO]:\t No philosopher should die.$(RESET)"

hel: all
	valgrind --tool=helgrind --tool=drd -s ./$(NAME) 100 800 200 200 10

val: all
	 valgrind --leak-check=full --track-origins=yes -s --show-leak-kinds=all ./$(NAME) 2 800 200 200 10


#COLORS

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m
