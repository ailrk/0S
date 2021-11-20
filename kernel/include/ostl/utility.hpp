#pragma once

#include "type_traits.hpp"

namespace ostl {
template <typename T>
constexpr typename remove_reference<T>::type &&move(T &&t) noexcept {
    return static_cast<typename remove_reference<T>::type &&>(t);
}

template <typename T>
constexpr T &&forward(typename remove_reference<T>::type &t) noexcept {
    return static_cast<T &&>(t);
}

template <typename T>
constexpr T &&forward(typename remove_reference<T>::type &&t) noexcept {
    static_assert(!is_lvalue_reference<T>::value,
                  "Cannot forward an rvalue as lvalue.");
    return static_cast<T &&>(t);
}

template <typename T> typename add_rvalue_reference<T>::type declval() noexcept;

template <typename T> inline void swap(T &a, T &b) {
    T tmp = move(a);
    a = move(b);
    b = move(tmp);
}

} // namespace ostl
