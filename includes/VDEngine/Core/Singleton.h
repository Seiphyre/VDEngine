#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

namespace VDEngine
{

template <typename T> class Singleton
{
  protected:
    static T * instance;

    Singleton()
    {
    }

  public:
    static T * getInstance()
    {
        if (instance == 0)
        {
            instance = new T();
        }

        return instance;
    }
};

template <typename T> T * Singleton<T>::instance = 0;

} // namespace VDEngine

#endif