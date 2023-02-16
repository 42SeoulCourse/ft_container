#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

template <typename T, typename Container = ft::vector<T> >
class stack {
 public:
  typedef Container                           container_type;
  typedef typename container_type::value_type value_type;
  typedef typename container_type::size_type  size_type;

 protected:
  container_type c;

 public:
  explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}

  ~stack() {}

  bool              empty() const { return c.empty(); }
  size_type         size() const { return c.size(); }
  value_type       &top() { return c.back(); }
  const value_type &top() const { return c.back(); }
  void              push(const value_type &val) { c.push_back(val); }
  void              pop() { c.pop_back(); }

  template <typename TT, typename TContainer>
  friend bool operator==(const stack<TT, TContainer> &lhs,
                         const stack<TT, TContainer> &rhs);

  template <typename TT, typename TContainer>
  friend bool operator!=(const stack<TT, TContainer> &lhs,
                         const stack<TT, TContainer> &rhs);

  template <typename TT, typename TContainer>
  friend bool operator<(const stack<TT, TContainer> &lhs,
                        const stack<TT, TContainer> &rhs);

  template <typename TT, typename TContainer>
  friend bool operator<=(const stack<TT, TContainer> &lhs,
                         const stack<TT, TContainer> &rhs);

  template <typename TT, typename TContainer>
  friend bool operator>(const stack<TT, TContainer> &lhs,
                        const stack<TT, TContainer> &rhs);

  template <typename TT, typename TContainer>
  friend bool operator>=(const stack<TT, TContainer> &lhs,
                         const stack<TT, TContainer> &rhs);
};

template <typename T, typename Container>
bool operator==(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return lhs.c == rhs.c;
}

template <typename T, typename Container>
bool operator!=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return lhs.c != rhs.c;
}

template <typename T, typename Container>
bool operator<(const stack<T, Container> &lhs,
               const stack<T, Container> &rhs) {
  return lhs.c < rhs.c;
}

template <typename T, typename Container>
bool operator<=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return lhs.c <= rhs.c;
}

template <typename T, typename Container>
bool operator>(const stack<T, Container> &lhs,
               const stack<T, Container> &rhs) {
  return lhs.c > rhs.c;
}

template <typename T, typename Container>
bool operator>=(const stack<T, Container> &lhs,
                const stack<T, Container> &rhs) {
  return lhs.c >= rhs.c;
}

}  // namespace ft

#endif