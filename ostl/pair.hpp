#pragma once
// a pair type.

#include "utility.hpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// valina queue
template <typename T1, typename T2> struct Pair {
    using first_type = T1;
    using second_type = T2;

    T1 first;
    T2 second;

    Pair()
        : first()
        , second() {}

    Pair(T1 const &a, T2 const &b) // copy into pair
        : first(a)
        , second(b) {}

    template <typename U1, typename U2>
    Pair(U1 &&a, U2 const &&b) // foward into pair.
        : first(ostl::forward<U1>(a))
        , second(ostl::forward<U2>(b)) {}

    Pair(Pair &&other) // move
        : first(ostl::move(other.first))
        , second(ostl::move(other.second)) {}

    Pair(Pair const &other) // copy
        : first(other.first)
        , second(other.second) {}

    // templated version for copy constructor.
    template <typename U1, typename U2>
    Pair(Pair<U1, U2> const &other) // copy
        : first(other.first)
        , second(other.second) {}

    // templated version for move constructor.
    template <typename U1, typename U2>
    Pair(Pair<U1, U2> &&other) // copy
        : first(ostl::move(other.first))
        , second(ostl::move(other.second)) {}

    // multiple args for second.
    template <typename U, typename Arg, typename... Args>
    Pair(U &&x, Arg &&arg, Args &&...args)
        : first(ostl::forward<U>(x))
        , second(ostl::forward<Arg>(arg), ostl::forward<Args>(args)...) {}

    Pair &operator=(Pair &&other) {
        first = ostl::move(other.first);
        second = ostl::move(other.second);
        return *this;
    }

    template <typename U1, typename U2> Pair &operator=(Pair<U1, U2> &&other) {
        first = ostl::move(other.first);
        second = ostl::move(other.second);
        return *this;
    }

    void swap(Pair &&other) {
        ostl::swap(first, other.first);
        ostl::swap(second, other.second);
    }

    // memberwise equality
};

template <typename T1, typename T2>
inline bool operator==(Pair<T1, T2> const &x, Pair<T1, T2> const &y) {
    return x.first == y.first && x.second == y.second;
}

template <typename T1, typename T2>
inline bool operator!=(Pair<T1, T2> const &x, Pair<T1, T2> const &y) {
    return !(x == y);
}

template <typename T1, typename T2>
inline bool operator<(Pair<T1, T2> &x, Pair<T2, T2> &y) {
    return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}

template <typename T1, typename T2>
inline bool operator>(Pair<T1, T2> &x, Pair<T2, T2> &y) {
    return y < x;
}

template <typename T1, typename T2>
inline bool operator<=(Pair<T1, T2> &x, Pair<T2, T2> &y) {
    return !(y < x);
}

template <typename T1, typename T2>
inline bool operator>=(Pair<T1, T2> &x, Pair<T2, T2> &y) {
    return !(x < y);
}

template <typename T1, typename T2>
inline void swap(Pair<T1, T2> &x, Pair<T1, T2> &y) {
    x.swap(y);
}

template <typename T1, typename T2>
inline void swap(Pair<T1, T2> &&x, Pair<T1, T2> &y) {
    x.swap(y);
}

template <typename T1, typename T2>
inline void swap(Pair<T1, T2> &x, Pair<T1, T2> &&y) {
    x.swap(y);
}

// pair smart constructor.
template <typename T1, typename T2> inline Pair<T1, T2> make_pair(T1 x, T2 y) {
    return Pair<T1, T2>(x, y);
}
#endif
