#pragma once
// a simple type trait

#include <stddef.h>

namespace ostl {

template <typename...> using void_t = void;

template <typename T> struct type_identity { using type = T; };

template <typename T, T v> struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }

    constexpr value_type operator()() const noexcept { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <bool Pred, typename If, typename Else> struct conditional;

template <typename If, typename Else> struct conditional<true, If, Else> {
    using type = If;
};

template <typename If, typename Else> struct conditional<false, If, Else> {
    using type = Else;
};

} // namespace ostl

namespace ostl {

// the source of all evil.
template <bool B, typename T = void> struct enable_if {};
template <typename T> struct enable_if<true, T> { using type = T; };

} // namespace ostl

namespace ostl {
template <typename T> struct remove_reference { using type = T; };
template <typename T> struct remove_reference<T &> { using type = T; };
template <typename T> struct remove_reference<T &&> { using type = T; };

template <typename T> auto try_add_lvalue_reference(int) -> type_identity<T &>;
template <typename T> auto try_add_lvalue_reference(...) -> type_identity<T>;

template <typename T> auto try_add_rvalue_reference(int) -> type_identity<T &&>;
template <typename T> auto try_add_rvalue_reference(...) -> type_identity<T>;

template <typename T>
struct add_lvalue_reference : decltype(try_add_lvalue_reference<T>(0)) {};

template <typename T>
struct add_rvalue_reference : decltype(try_add_rvalue_reference<T>(0)) {};

template <typename T>
auto try_add_pointer(int)
    -> type_identity<typename remove_reference<T>::type *>;
template <typename T> auto try_add_pointer(...) -> type_identity<T>;
template <typename T> struct add_pointer : decltype(try_add_pointer<T>(0)) {};

} // namespace ostl

namespace ostl {} // namespace ostl

namespace ostl {
template <typename T> struct remove_cv { using type = T; };
template <typename T> struct remove_cv<const T> { using type = T; };
template <typename T> struct remove_cv<volatile T> { using type = T; };
template <typename T> struct remove_cv<const volatile T> { using type = T; };

template <typename T> struct remove_const { using type = T; };
template <typename T> struct remove_const<const T> { using type = T; };
template <typename T> struct remove_volatile { using type = T; };
template <typename T> struct remove_volatile<volatile T> { using type = T; };

template <typename T> struct remove_cvref {
    using type = typename remove_cv<typename remove_reference<T>::type>::type;
};

template <typename T> struct add_cv { using type = const volatile T; };
template <typename T> struct add_const { using type = const volatile T; };
template <typename T> struct add_volatile { using type = const volatile T; };

} // namespace ostl

namespace ostl {

template <typename T> struct remove_pointer { using type = T; };
template <typename T> struct remove_pointer<T *> { using type = T; };
template <typename T> struct remove_pointer<T *const> { using type = T; };
template <typename T> struct remove_pointer<T *volatile> { using type = T; };
template <typename T> struct remove_pointer<T *const volatile> {
    using type = T;
};

} // namespace ostl

namespace ostl {
template <typename T, typename U> struct is_same : false_type {};
template <typename T> struct is_same<T, T> : true_type {};

template <typename T> struct is_lvalue_reference : false_type {};
template <typename T> struct is_lvalue_reference<T &> : true_type {};

template <typename T> struct is_rvalue_reference : false_type {};
template <typename T> struct is_rvalue_reference<T &&> : true_type {};

template <typename T>
struct is_void : is_same<typename remove_cv<T>::type, void> {};

template <typename T>
struct is_null_pointer
    : is_same<typename remove_cv<T>::type, decltype(nullptr)> {};

template <typename T>
struct is_integral
    : integral_constant<
          bool,
          is_same<typename remove_cv<T>::type, int>::value ||
              is_same<typename remove_cv<short>::type, short>::value ||
              is_same<typename remove_cv<bool>::type, bool>::value ||
              is_same<typename remove_cv<char>::type, char>::value ||
              is_same<typename remove_cv<char16_t>::type, char16_t>::value ||
              is_same<typename remove_cv<char32_t>::type, char32_t>::value ||
              is_same<typename remove_cv<wchar_t>::type, wchar_t>::value ||
              is_same<typename remove_cv<long>::type, long>::value ||
              is_same<typename remove_cv<long long>::type, long long>::value> {
};

template <typename T>
struct is_floating_point
    : integral_constant<
          bool, is_same<typename remove_cv<T>::type, float>::value ||
                    is_same<typename remove_cv<T>::type, double>::value ||
                    is_same<typename remove_cv<T>::type, long double>::value> {
};

template <typename T>
struct is_arithmetic
    : integral_constant<bool, is_integral<T>::value ||
                                  is_floating_point<T>::value> {};

template <typename T> struct is_pointer_ : false_type {};
template <typename T> struct is_pointer_<T *> : true_type {};
template <typename T>
struct is_pointer : is_pointer_<typename remove_cv<T>::type> {};

template <typename T> struct is_array : false_type {};
template <typename T> struct is_array<T[]> : true_type {};
template <typename T, size_t N> struct is_array<T[N]> : true_type {};

template <typename T> struct is_member_pointer_ : false_type {};
template <typename T, typename U>
struct is_member_pointer_<T U::*> : true_type {};

template <typename T>
struct is_member_pointer : is_member_pointer_<typename remove_cv<T>::type> {};

// fundamental types like arithmetics, void, nullptr
template <typename T>
struct is_fundamental
    : integral_constant<bool, is_arithmetic<T>::value || is_void<T>::value ||
                                  is_same<decltype(nullptr),
                                          typename remove_cv<T>::type>::value> {
};

template <typename T>
struct is_compound : integral_constant<bool, !is_fundamental<T>::value> {};

template <typename T, typename = void> struct is_class : false_type {};
template <typename T> struct is_class<T, void_t<int T::*>> : true_type {};

template <typename T> struct is_reference : false_type {};
template <typename T> struct is_reference<T &> : true_type {};
template <typename T> struct is_reference<T &&> : true_type {};

template <typename T> struct is_const : false_type {};
template <typename T> struct is_const<const T> : true_type {};

} // namespace ostl

namespace ostl {
template <typename T> struct is_function : false_type {};

// regular function
template <typename Ret, class... Args>
struct is_function<Ret(Args...)> : true_type {};

// varaidc functions like printf
template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...)> : true_type {};

// bunch of cv qualifiers...
template <typename Ret, class... Args>
struct is_function<Ret(Args...) const> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args...) volatile> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args...) const volatile> : true_type {};

template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) const> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) volatile> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) const volatile> : true_type {};

// then bunch of ref qualfiers...
template <typename Ret, class... Args>
struct is_function<Ret(Args...) &> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args...) const &> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args...) volatile &> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args...) const volatile &> : true_type {};

template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) &> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) const &> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) volatile &> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) const volatile &> : true_type {};

template <typename Ret, class... Args>
struct is_function<Ret(Args...) &&> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args...) const &&> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args...) volatile &&> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args...) const volatile &&> : true_type {};

template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) &&> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) const &&> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) volatile &&> : true_type {};
template <typename Ret, class... Args>
struct is_function<Ret(Args..., ...) const volatile &&> : true_type {};
} // namespace ostl

namespace ostl {

template <typename T> struct remove_extent { using type = T; };
template <typename T> struct remove_extent<T[]> { using type = T; };
template <typename T, size_t N> struct remove_extent<T[N]> { using type = T; };

template <typename T> struct decay {
  private:
    using U = typename remove_reference<T>::type;

  public:
    using type = typename conditional<
        is_array<U>::value, typename remove_extent<U>::type *,
        typename conditional<is_function<U>::value,
                             typename add_pointer<U>::type,
                             typename remove_cv<U>::type>::type>::type;
};

} // namespace ostl

#endif
