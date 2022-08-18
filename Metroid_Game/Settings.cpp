#include "pch.h"
#include "Settings.h"

template<typename T>
T& Settings<T>::GetInstance()
{
    static T instance{};
    return instance;
}