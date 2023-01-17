NAME=container

CXX=c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98
RM=rm -rf

# SRCS=$(wildcard *.cpp)
SRCS= main.cpp

OBJS=$(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re