#pragma once

template <class T> class SingletonTemplate
{
private :
    SingletonTemplate() = default;
    ~SingletonTemplate() = default;
public :
    SingletonTemplate(SingletonTemplate&) = delete;
    SingletonTemplate(SingletonTemplate&&) = delete;
    SingletonTemplate& operator=(SingletonTemplate&) = delete;
    SingletonTemplate&& operator=(SingletonTemplate&&) = delete;

    static T & getInstance() {
        static T instance;
        return instance;
    }
};