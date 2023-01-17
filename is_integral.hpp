#ifndef IS_INTEGRAL_HPP_
# define IS_INTEGRAL_HPP_

// template <bool, typename T>
// struct enable_if {};

// template <typename T>
// struct enable_if<true, T> {
//   typedef T type;
// };

// enable_if<typename is_integral<T>::value, T>

template <bool is_integral, typename T>
struct true_type {
  const static bool value = true;
  typedef T type;
};

template <bool is_integral, typename T>
struct false_type {
  const static bool value = false;
  typedef T type;
};

template <typename T>
struct is_integral : public false_type<false, void> {};

template <>
struct is_integral<bool> : public true_type<true, bool> {};

template <>
struct is_integral<char> : public true_type<true, char> {};

template <>
struct is_integral<signed char> : public true_type<true, char> {};

template <>
struct is_integral<unsigned char> : public true_type<true, unsigned char> {};

template <>
struct is_integral<wchar_t> : public true_type<true, wchar_t> {};

template <>
struct is_integral<short> : public true_type<true, short> {};

template <>
struct is_integral<unsigned short> : public true_type<true, unsigned short> {};

template <>
struct is_integral<int> : public true_type<true, int> {};

template <>
struct is_integral<unsigned int> : public true_type<true, unsigned int> {};

template <>
struct is_integral<long> : public true_type<true, long> {};

template <>
struct is_integral<unsigned long> : public true_type<true, unsigned long> {};

template <>
struct is_integral<long long> : public true_type<true, long long> {};

template <>
struct is_integral<unsigned long long>
    : public true_type<true, unsigned long long> {};

#endif  // _IS_INTEGRAL_HPP_
