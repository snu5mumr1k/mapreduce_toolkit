#pragma once

template <typename T>
T *Singleton() {
    static T t;

    return &t;
}
