#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"
#include "utils.hpp"

namespace ft {
template <typename T>
class random_access_iterator
    : public ft::iterator<random_access_iterator_tag, T> {
 public:
  //  Member types =============================================================
  typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category iterator_category;
  typedef typename ft::iterator<random_access_iterator_tag, T>::value_type        value_type;
  typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type   difference_type;
  typedef typename ft::iterator<random_access_iterator_tag, T>::pointer           pointer;
  typedef typename ft::iterator<random_access_iterator_tag, T>::reference         reference;

 private:
  pointer _ptr;

 public:
  // Constructors =============================================================
  random_access_iterator() : _ptr(0) {}
  random_access_iterator(const random_access_iterator& other)
      : _ptr(other._ptr) {}
  random_access_iterator(pointer ptr) : _ptr(ptr) {}
  random_access_iterator& operator=(const random_access_iterator& other) {
    if (this != &other) _ptr = other._ptr;
    return *this;
  }
  virtual ~random_access_iterator() {}

  // Operators overloads =======================================================
  pointer base() const { return this->_ptr; }

  random_access_iterator& operator+=(difference_type n) {
    _ptr += n;
    return *this;
  }

  random_access_iterator operator+(difference_type n) const {
    random_access_iterator tmp = (*this);
    tmp += n;
    return tmp;
  }

  random_access_iterator& operator-=(difference_type n) {
    _ptr -= n;
    return *this;
  }

  random_access_iterator operator-(difference_type n) const {
    random_access_iterator tmp = (*this);
    tmp -= n;
    return tmp;
  }

  template <typename U>
  random_access_iterator& operator=(const random_access_iterator<U>& other) {
    this->_ptr = other.base();
    return *this;
  }

  reference operator[](difference_type n) { return _ptr[n]; }

  const reference operator[](difference_type n) const { return *_ptr[n]; }

  random_access_iterator& operator++() {
    ++_ptr;
    return *this;
  }

  random_access_iterator operator++(int) {
    random_access_iterator tmp = (*this);
    ++_ptr;
    return tmp;
  }

  random_access_iterator& operator--() {
    --_ptr;
    return *this;
  }

  random_access_iterator operator--(int) {
    random_access_iterator tmp = (*this);
    --_ptr;
    return tmp;
  }

  reference       operator*() { return *_ptr; }
  const reference operator*() const { return *_ptr; }
  pointer         operator->() const { return _ptr; }
  // ++
  operator random_access_iterator<const T>() const {
    return (random_access_iterator<const T>(this->_ptr));
  }
};

// operators overloads =========================================================

template <typename T>
random_access_iterator<T> operator+(
    typename random_access_iterator<T>::difference_type n,
    const random_access_iterator<T>&                    iterator) {
  random_access_iterator<T> it = iterator;
  return (it + n);
}

template <typename Iterator>
typename ft::random_access_iterator<Iterator>::difference_type operator-(
    const random_access_iterator<Iterator>& lhs,
    const random_access_iterator<Iterator>& rhs) {
  return (lhs.base() - rhs.base());
}

template <typename Iterator1, typename Iterator2>
typename ft::random_access_iterator<Iterator1>::difference_type operator-(
    const random_access_iterator<Iterator1>& lhs,
    const random_access_iterator<Iterator2>& rhs) {
  return (lhs.base() - rhs.base());
}

template <typename Iterator>
bool operator==(
    const ft::random_access_iterator<Iterator>& lhs,
    const ft::random_access_iterator<Iterator>& rhs) {
  return (lhs.base() == rhs.base());
}

template <typename Iterator>
bool operator!=(
    const ft::random_access_iterator<Iterator>& lhs,
    const ft::random_access_iterator<Iterator>& rhs) {
  return (lhs.base() != rhs.base());
}

template <typename Iterator>
bool operator<(const ft::random_access_iterator<Iterator>& lhs,
               const ft::random_access_iterator<Iterator>& rhs) {
  return (lhs.base() < rhs.base());
}

template <typename Iterator>
bool operator>(const ft::random_access_iterator<Iterator>& lhs,
               const ft::random_access_iterator<Iterator>& rhs) {
  return (lhs.base() > rhs.base());
}

template <typename Iterator>
bool operator<=(const ft::random_access_iterator<Iterator>& lhs,
                const ft::random_access_iterator<Iterator>& rhs) {
  return (lhs.base() <= rhs.base());
}

template <typename Iterator>
bool operator>=(const ft::random_access_iterator<Iterator>& lhs,
                const ft::random_access_iterator<Iterator>& rhs) {
  return (lhs.base() >= rhs.base());
}
//

template <typename Iterator1, typename Iterator2>
bool operator==(
    const ft::random_access_iterator<Iterator1>& lhs,
    const ft::random_access_iterator<Iterator2>& rhs) {
  return (lhs.base() == rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator!=(
    const ft::random_access_iterator<Iterator1>& lhs,
    const ft::random_access_iterator<Iterator2>& rhs) {
  return (lhs.base() != rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator<(const ft::random_access_iterator<Iterator1>& lhs,
               const ft::random_access_iterator<Iterator2>& rhs) {
  return (lhs.base() < rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator>(const ft::random_access_iterator<Iterator1>& lhs,
               const ft::random_access_iterator<Iterator2>& rhs) {
  return (lhs.base() > rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator<=(const ft::random_access_iterator<Iterator1>& lhs,
                const ft::random_access_iterator<Iterator2>& rhs) {
  return (lhs.base() <= rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator>=(const ft::random_access_iterator<Iterator1>& lhs,
                const ft::random_access_iterator<Iterator2>& rhs) {
  return (lhs.base() >= rhs.base());
}

}  // namespace ft

#endif