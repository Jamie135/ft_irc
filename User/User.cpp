#include "User.hpp"

User::User(int fdNew, std::string const &nicknameNew)
{
    this->fdUser = fdNew;
    this->nickname = nicknameNew;
}

User::~User()
{}

int User::getFdUser()
{
    return (this->fdUser);
}

std::string const &User::getNickName() const
{
    return (this->nickname);
}

std::string const &User::getName() const
{
    return (this->name);
}

void	User::setName(std::string const &nameNew)
{
	this->name = nameNew;
}
