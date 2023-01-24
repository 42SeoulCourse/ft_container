#ifndef UTILS_HPP
# define UTILS_HPP

#include "iterator.hpp"

namespace ft {
  // distance ==================================================================
    template <class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type distance(
        InputIterator first, InputIterator last) {
      typename ft::iterator_traits<InputIterator>::difference_type num = 0;
      while (first != last) {
        ++first;
        ++num;
      }
      return num;
    }

} // namespace ft

#endif