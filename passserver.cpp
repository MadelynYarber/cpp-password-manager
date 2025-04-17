#include "passserver.h"
#include "hashtable.h"

PassServer::PassServer(size_t size) : pServer(size){}

PassServer::~PassServer()
{
    pServer.clear();
}

bool PassServer::load(const char* filename)
{
    return(pServer.load(filename));
}

bool PassServer::addUser(std::pair<string, string> & kv)
{
    if (pServer.contains(kv.first) == true)
    {
        return false;
    }
    return(pServer.insert(make_pair(kv.first,encrypt(kv.second))));
}

bool PassServer::addUser(std::pair<string, string> && kv)
{
    if (pServer.contains(kv.first) == true)
    {
        return false;
    }
    return(pServer.insert(std::move(make_pair(kv.first,encrypt(kv.second)))));

}

bool PassServer::removeUser(const string& k)
{
    if (pServer.contains(k) == false)
    {
        return false;
    }
    else
    {
        return(pServer.remove(k));
    }
}

bool PassServer::changePassword(const pair<string, string> & p, const string& newpassword)
{
    if(pServer.match(make_pair(p.first, encrypt(p.second))) == true && encrypt(p.second) != encrypt(newpassword))
    {
        pServer.insert(make_pair(p.first, encrypt(newpassword)));
        return true;
    }
    return false;
}

bool PassServer::find(const string& user)
{
    return(pServer.contains(user));
}

void PassServer::dump()
{
    pServer.dump();
}

size_t PassServer::size() const
{
    return(pServer.getSize());
}

bool PassServer::write_to_file(const char* filename) const
{
    return(pServer.write_to_file(filename));
}

string PassServer::encrypt(const string& str)
{
    char salt[] = "$1$########";
    char *password = new char [100];
    strcpy(password, str.c_str());
    string newPass = crypt(password, salt);
    return newPass.substr(12);
}

int PassServer::get_prime_below(int n)
{
    return pServer.get_prime_below(n);
}