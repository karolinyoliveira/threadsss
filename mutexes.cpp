#include "mutexes.h"

unordered_map<string, Mtx_data> mutexes;

bool create_mutex(string name)
{
    if (mutexes.find(name) != mutexes.end())
        return false;
    else
    {
        mutexes[name] = true;
        return true;
    }
}

bool remove_mutex(string name)
{
    if (mutexes.find(name) == mutexes.end())
        return false;
    else
    {
        mutexes.erase(name);
        return true;
    }
}

bool lock(string name)
{
    if (mutexes.empty())
        return false;
    if (!mutexes.count(name))
        return false;
    while (mutexes[name].locked())
        mutexes[name].sleep();
    mutexes[name].lock();
    return true;
}

bool unlock(string name)
{
    if (mutexes.empty())
        return false;
    if (!mutexes.count(name))
        return false;
    mutexes[name].unlock();
    mutexes[name].wakeup();
    return true;
}
