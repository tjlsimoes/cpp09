################################################################################
#                                    CONFIGS                                   #
################################################################################

NAME =	btc
FLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address -I.
CC = c++
RM = rm -rf

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS = main.cpp BitcoinExchange.cpp
OBJS_D = objs
OBJS = $(SRCS:.cpp=.o)

################################################################################
#                                  Makefile  objs                              #
################################################################################

WHITE	= \033[1;37m
BLACK	= \033[1;30m
RED		= \033[1;31m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
GREEN	= \033[1;32m
DEFAULT = \033[0m


%.o:%.cpp
	$(CC) $(FLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Compiling $(YELLOW)$(NAME)$(BLUE) . . . . . . .$(DEFAULT)"
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Successfully built --> $(YELLOW)$(NAME)$(DEFAULT)"

clean: 
	@$(RM) $(OBJS)
	@echo "$(YELLOW)OBJECTS $(RED)REMOVED$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)$(NAME) $(RED)REMOVED$(DEFAULT)"

re: fclean all

.PHONY: all clean re fclean