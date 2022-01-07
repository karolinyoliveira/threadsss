#ifndef DEF_MUTEXES
#include <cstdio>
#include <string>
#include <unordered_map>
#include <atomic>
#include <mutex>
#include <condition_variable>
using namespace std;

class Mtx_data
{
public:
    atomic<bool> value{};
    condition_variable cv;

    Mtx_data()
    {
        this->value = true;
        this->lck = unique_lock<mutex>(this->mtx);
    }

    void operator=(bool v)
    {
        this->value = v;
    }

    void lock()
    {
        this->value = false;
    }

    void unlock()
    {
        this->value = true;
    }

    bool locked()
    {
        return !this->value;
    }

    void sleep()
    {
        this->cv.wait(this->lck);
    }

    void wakeup()
    {
        this->cv.notify_one();
    }

private:
    mutex mtx;
    unique_lock<mutex> lck;
};

  bool create_mutex(std::string name);
  bool remove_mutex(std::string name);
  bool lock(std::string name);
  bool unlock(std::string name);
#endif