# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 16:39:48 by tjorge-l          #+#    #+#              #
#    Updated: 2025/09/22 11:02:55 by tjorge-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN

CCXX = c++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror
RM = rm -rf

DEBUG_FLAGS = -g
VFLAGS = -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

SRCS = main.cpp

OBJS = $(SRCS:%.cpp=%.o)


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CCXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CCXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	valgrind $(VFLAGS) ./$(NAME)

debug: CXXFLAGS = -g -Wall -Wextra -Werror
debug: $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

rdebug: debug
	valgrind $(VFLAGS) ./$(NAME)

.PHONY: all clean fclean re
