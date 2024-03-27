NAME = ircserv
CPP = c++
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -std=c++98

SRCS =	main.cpp \
		Server/Server.cpp \
		Server/ServerInit.cpp \
		Server/ServerParsing.cpp \
		User/User.cpp \
		Channel/Channel.cpp \
		Command/PASS.cpp \
		Command/NICK.cpp \
		Command/USER.cpp \
		Command/QUIT.cpp \
		Command/PING.cpp \
		Command/JOIN.cpp \
		Command/PART.cpp \
		Command/TOPIC.cpp

OBJDIR = .obj
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(VFLAGS) -o $(NAME) $^
	mkdir -p $(OBJDIR) && mv $(SRCS:.cpp=.o) $(OBJDIR)

%.o : %.cpp
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
