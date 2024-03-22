#include "User.hpp"

User::User()
{
    this->fdUser = -1;
    this->nickname = "";
    this->user = "";
    this->ip = "";
    this->buffer = "";
    this->registered = false;
    this->connected = false;
}

User::User(int fd, std::string nickname, std::string user): fdUser(fd), nickname(nickname), user(user)
{}

User::User(User const &obj)
{
    *this = obj;
}

User &User::operator=(User const &obj)
{
    if (this != &obj)
    {
        this->fdUser = obj.fdUser;
        this->nickname = obj.nickname;
        this->user = obj.user;
        this->ip = obj.ip;
        this->buffer = obj.buffer;
        this->registered = obj.registered;
        this->connected = obj.connected;
    }
    return *this;
}

User::~User()
{}

int User::getFduser()
{
    return (this->fdUser);
}

std::string User::getNickname()
{
    return (this->nickname);
}

std::string User::getUser()
{
    return (this->user);
}

std::string User::getIp()
{
    return (ip);
}

std::string User::getBuffer()
{
    return (buffer);
}

bool    User::getRegistered()
{
    return (registered);
}

bool    User::getConnected()
{
    return (this->connected);
}

void    User::setFduser(int fd)
{
    this->fdUser = fd;
}

void    User::setNickname(std::string &nickname)
{
    this->nickname = nickname;
}

void    User::setUser(std::string &user)
{
    this->user = user;
}

void    User::setIp(std::string ip)
{
    this->ip = ip;
}

void    User::setBuffer(std::string recv)
{
    buffer += recv;
}

void    User::setRegistered(bool val)
{
    registered = val;
}

void    User::setConnected(bool val)
{
    this->connected = val;
}

void    User::removeBuffer()
{
    buffer.clear();
}
