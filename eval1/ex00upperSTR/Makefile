# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 13:24:46 by vhaefeli          #+#    #+#              #
#    Updated: 2023/06/23 11:44:28 by vhaefeli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		= btc
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -pedantic -std=c++98
CPPFLAGS	= -Iinclude
SRC_DIR		= /
OBJS_DIR	= obj
SRCS		= main.cpp \
				BitcoinExchange.cpp \

OBJS = 		$(patsubst %.cpp, $(OBJS_DIR)/%.o, $(SRCS))

all: $(TARGET)


debug: CXXFLAGS += -g3
debug: LDFLAGS += -fsanitize=address
debug: $(TARGET)

valgrind: CXXFLAGS += -g3
valgrind: fclean $(OBJS) $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -rf $(OBJS_DIR)
fclean: clean
	rm -f $(TARGET)

re: fclean all

run: all
	@-./$(TARGET)

runleaks: all
	@-leaks -atExit -- ./$(TARGET)

$(OBJS_DIR)/%.o: $(SRC_DIR_DIR)%.cpp | $(OBJS_DIR)
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) -o $@ $^

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJS_DIR):
	@mkdir -p $(dir $(OBJS))

.PHONY: all clean fclean re test 98 bear
