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
    this->isOp = false;
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
        this->isOp = obj.isOp;
    }
    return *this;
}

bool User::operator==(User const &rhs)
{
    if (this->nickname == rhs.nickname)
        return (true);
    return (false);
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

std::string User::getHostname()
{
    std::string hostname;

    hostname = this->getNickname() + "!" + this->getUser();
    return (hostname);
}

bool    User::getRegistered()
{
    return (registered);
}

bool    User::getConnected()
{
    return (this->connected);
}

// vérifie si le user a été invité à rejoindre le canal
bool    User::getInvited(std::string &channel)
{
    for (size_t i = 0; i < this->invitation.size(); i++)
    {
        if (this->invitation[i] == channel)
            return (true);
    }
    return (false);
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

// retirer l'invitation quand le user invité rejoint le canal
void    User::removeInvite(std::string &channel)
{
    for (size_t i = 0; i < this->invitation.size(); i++)
    {
        if (this->invitation[i] == channel)
        {
            this->invitation.erase(this->invitation.begin() + i);
            return ;
        }
    }
}
