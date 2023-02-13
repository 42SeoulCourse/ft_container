#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

template <typename T1, typename T2>
struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  pair() : first(), second() {}
  pair(const T1 &t1, const T2 &t2) : first(t1), second(t2) {}

  template <typename U1, typename U2>
  pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

  pair &operator==(pair const &p) {
    first = p.first;
    second = p.second;
    return *this;
  }
};

template <typename T, typename U>
bool operator==(const pair<T, U> &x, const pair<T, U> &y) {
  return x.first == y.first && x.second == y.second;
}

template <typename T, typename U>
bool operator!=(const pair<T, U> &x, const pair<T, U> &y) {
  return !(x == y);
}

template <typename T, typename U>
bool operator<(const pair<T, U> &x, const pair<T, U> &y) {
  return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}

template <typename T, typename U>
bool operator>(const pair<T, U> &x, const pair<T, U> &y) {
  return y < x;
}

template <typename T, typename U>
bool operator>=(const pair<T, U> &x, const pair<T, U> &y) {
  return !(x < y);
}

template <typename T, typename U>
bool operator<=(const pair<T, U> &x, const pair<T, U> &y) {
  return !(y < x);
}

template <typename T, typename U>
pair<T, U> make_pair(T x, U y) {
  return pair<T, U>(x, y);
}

}  // namespace ft

#endif