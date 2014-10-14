#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <cassert>

template<typename T>
class Singleton
{
public:
    static T& get()
    {
        return *_instance;
    }

protected:
    Singleton(void) { 
        assert(_instance == nullptr); 
        _instance = (T*)this; 
        ;
    }
    virtual	~Singleton(void) { _instance = nullptr; }

private:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
    static T* _instance;
};

template<typename T> T* Singleton<T>::_instance = nullptr;

#endif