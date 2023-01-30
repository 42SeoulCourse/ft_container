#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
namespace ft {

// Iterator traits =============================================================
template <typename Iterator>
class reverse_iterator {
  // Member types ==============================================================
 public:
  typedef Iterator iterator_type;
  typedef typename ft::iterator_traits<Iterator>::iterator_category
                                                             iterator_category;
  typedef typename ft::iterator_traits<Iterator>::value_type value_type;
  typedef
      typename ft::iterator_traits<Iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<Iterator>::pointer     pointer;
  typedef typename ft::iterator_traits<Iterator>::reference   reference;

 private:
  iterator_type _iter;

  // Constructors ==============================================================
 public:
  reverse_iterator() : _iter() {}
  template <class U>
  reverse_iterator(const reverse_iterator<U>& other) : _iter(other.base()) {}
  explicit reverse_iterator(iterator_type it) : _iter(it) {}
  virtual ~reverse_iterator() {}

  template <typename U>
  reverse_iterator& operator=(const reverse_iterator& other) {
    _iter = other.base();
    return (*this);
  }

  //  Operator overloads =======================================================
  iterator_type base() const { return (_iter); }

  reverse_iterator& operator+=(difference_type n) {
    _iter -= n;
    return (*this);
  }
  // a = b(보존) + 3
  reverse_iterator operator+(difference_type n) const {
    reverse_iterator tmp = (*this);
    return (tmp += n);
  }

  reverse_iterator operator-=(difference_type n) {
    _iter += n;
    return (*this);
  }

  reverse_iterator operator-(difference_type n) const {
    reverse_iterator tmp = (*this);
    return (tmp -= n);
  }

  difference_type operator-(reverse_iterator other) {
    return (other._iter - _iter);
  }

  reverse_iterator& operator--() {
    ++_iter;
    return (*this);
  }

  reverse_iterator operator--(int) {
    reverse_iterator tmp = (*this);
    ++_iter;
    return (tmp);
  }

  reverse_iterator& operator++() {
    --_iter;
    return (*this);
  }

  reverse_iterator operator++(int) {
    reverse_iterator tmp = (*this);
    --_iter;
    return (tmp);
  }

  reference operator*() {
    iterator_type tmp = _iter;
    return *(--tmp);
  }

  const reference operator*() const {
    iterator_type tmp = _iter;
    return *(--tmp);
  }

  pointer operator->() const {
    iterator_type tmp = _iter;
    return &(operator*());
  }

  const reference operator[](difference_type n) const {
    return *(_iter - n - 1);
  }
  reference operator[](difference_type n) { return *(_iter - n - 1); }
};

template <typename Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
  return (lhs.base() == rhs.base());
}

template <typename Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
  return (lhs.base() != rhs.base());
}

template <typename Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs) {
  return (lhs.base() > rhs.base());
}

template <typename Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
  return (lhs.base() >= rhs.base());
}

template <typename Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs,
               const reverse_iterator<Iterator>& rhs) {
  return (lhs.base() < rhs.base());
}

template <typename Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs,
                const reverse_iterator<Iterator>& rhs) {
  return (lhs.base() <= rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs) {
  return (lhs.base() == rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs) {
  return (lhs.base() != rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs) {
  return (lhs.base() > rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs) {
  return (lhs.base() >= rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs) {
  return (lhs.base() < rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs) {
  return (lhs.base() <= rhs.base());
}

template <typename Iterator>
reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::difference_type n,
    const reverse_iterator<Iterator>&                    reverse_iter) {
  return (reverse_iter + n);
}

template <typename Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
  return (rhs.base() - lhs.base());
}

}  // namespace ft

#endif
