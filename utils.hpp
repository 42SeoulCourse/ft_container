#ifndef UTILS_HPP
#define UTILS_HPP

#include "iterator.hpp"

namespace ft {
// distance ==================================================================
template <typename InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(
    InputIterator first, InputIterator last) {
  typename ft::iterator_traits<InputIterator>::difference_type num = 0;
  while (first != last) {
    ++first;
    ++num;
  }
  return num;
}

template <typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1) {
    if (first2 == last2 || *first2 < *first1) return false;
    if (*first1 < *first2) return true;
    ++first1;
    ++first2;
  }
  return (first2 != last2);
}

}  // namespace ft

#endif