NAME = ircserv
CPP = c++
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -std=c++98

SRCS =	

INCLS = 

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(VFLAGS) -o $(NAME) $^

%.o : %.cpp $(INCLS)
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
