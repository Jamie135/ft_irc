NAME = ircserv
CLIENT = client
CPP = c++
CFLAGS = -Wall -Wextra -Werror -g3
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
		Command/PART.cpp

CLIOBJS = $(patsubst Client/%.cpp, $(OBJDIR)/%.o, $(SRCSCLI))

all: $(OBJDIR) $(NAME) $(CLIENT)

$(NAME): $(SRVOBJS)
	$(CPP) $(CFLAGS) $(CPPFLAGS) $(SRVOBJS) -o $(NAME)

$(CLIENT):	$(CLIOBJS)
	$(CPP) $(CFLAGS) $(CPPFLAGS) $(CLIOBJS) -o $(CLIENT)

$(OBJDIR):
	mkdir -p .obj

$(OBJDIR)/%.o : Server/%.cpp
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/%.o : Client/%.cpp
	$(CPP) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -f $(NAME)
	rm -f $(CLIENT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
