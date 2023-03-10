#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>

#include "enable_if.hpp"
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector {
  /********** Member types **********/
 public:
  typedef T                                                       value_type;
  typedef Allocator                                               allocator_type;
  typedef typename allocator_type::size_type                      size_type;
  typedef typename allocator_type::reference                      reference;
  typedef typename allocator_type::const_reference                const_reference;
  typedef typename allocator_type::pointer                        pointer;
  typedef typename allocator_type::const_pointer                  const_pointer;
  typedef ft::random_access_iterator<value_type>                  iterator;
  typedef ft::random_access_iterator<const value_type>            const_iterator;
  typedef ft::reverse_iterator<iterator>                          reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
  typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

  /***************************** Member variables *****************************/
 private:
  pointer        _start;
  pointer        _end;
  pointer        _capa_end;
  allocator_type _alloc;

  /***************************** Member functions *****************************/
 public:
  // constructors for c++98 __ constructs the vector
  explicit vector(const allocator_type& alloc = allocator_type())
      : _start(NULL), _end(NULL), _capa_end(NULL), _alloc(alloc) {
  }

  explicit vector(size_type count, const value_type& value = value_type(),
                  const Allocator& alloc = allocator_type())
      : _alloc(alloc) {
    _start = _alloc.allocate(count);
    _end = _start;
    _capa_end = _start + count;
    try {
      for (size_type i = 0; i < count; i++) _alloc.construct(_end++, value);
    } catch (...) {
      for (pointer p = _start; p != _end; p++) _alloc.destroy(p);
      _alloc.deallocate(_start, count);
      throw;
    }
  }

  template <typename InputIterator>
  vector(
      InputIterator first, InputIterator last,
      const Allocator& alloc = Allocator(),
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
      : _alloc(alloc) {
    size_type count = ft::distance(first, last);
    _start = _alloc.allocate(count);
    _end = _start;
    _capa_end = _start + count;
    try {
      for (size_type i = 0; i < count; i++) _alloc.construct(_end++, *first++);
    } catch (...) {
      for (pointer p = _start; p != _end; p++) _alloc.destroy(p);
      _alloc.deallocate(_start, count);
      throw;
    }
  }

  vector(const vector& other) : _alloc(other._alloc) {
    size_type count = other.size();
    _start = _alloc.allocate(count);
    _end = _start;
    _capa_end = _start + count;
    pointer p = other._start;
    try {
      for (size_type i = 0; i < count; i++) _alloc.construct(_end++, *p++);
    } catch (...) {
      for (pointer p = _start; p != _end; p++) _alloc.destroy(p);
      _alloc.deallocate(_start, count);
      throw;
    }
  }

  vector& operator=(const vector& other) {
    if (this == &other) return (*this);
    this->clear();
    if (this->capacity() < other.size()) {
      _alloc.deallocate(_start, this->capacity());
      _start = _alloc.allocate(other.size());
      _capa_end = _start + other.size();
    }
    _end = _start;
    pointer p = other._start;
    try {
      for (size_type i = 0; i < other.size(); i++)
        _alloc.construct(_end++, *p++);
    } catch (...) {
      for (pointer p = _start; p != _end; p++) _alloc.destroy(p);
      _alloc.deallocate(_start, other.size());
      throw;
    }
    return (*this);
  }

  ~vector() {
    this->clear();
    _alloc.deallocate(_start, this->capacity());
  }

  allocator_type get_allocator() const { return this->_alloc; }

  // Element access ============================================================
  reference at(size_type position) {
    if (position >= this->size()) {
      throw std::out_of_range("vector::at");
    }
    return ((*this)[position]);
  }
  const const_reference at(size_type position) const {
    if (position >= this->size()) {
      throw std::out_of_range("vector::at");
    }
    return ((*this)[position]);
  }

  reference             operator[](size_type pos) { return this->_start[pos]; }
  const const_reference operator[](size_type pos) const {
    return this->_start[pos];
  }

  reference front() {
    try {
      if (this->empty()) throw std::out_of_range("vector is empty");
      return (*this->_start);
    } catch (std::out_of_range& e) {
      std::cout << e.what() << std::endl;
      return (*this->_start);
    }
  }
  const const_reference front() const {
    try {
      if (this->empty()) throw std::out_of_range("vector is empty");
      return (*this->_start);
    } catch (std::out_of_range& e) {
      std::cout << e.what() << std::endl;
      return (*this->_start);
    }
  }

  reference back() {
    try {
      if (this->empty()) throw std::out_of_range("vector is empty");
      return (*(this->_end - 1));
    } catch (std::out_of_range& e) {
      std::cout << e.what() << std::endl;
      return (*(this->_end - 1));
    }
  }
  const_reference back() const {
    try {
      if (this->empty()) throw std::out_of_range("vector is empty");
      return (*(this->_end - 1));
    } catch (std::out_of_range& e) {
      std::cout << e.what() << std::endl;
      return (*(this->_end - 1));
    }
  }

  // Iterators =================================================================
  iterator       begin() { return (_start); }
  const_iterator begin() const { return (_start); }

  iterator       end() { return (_end); }
  const_iterator end() const { return (_end); }

  reverse_iterator             rbegin() { return (reverse_iterator(_end)); }
  const const_reverse_iterator rbegin() const {
    return (reverse_iterator(_end));
  }

  reverse_iterator             rend() { return (reverse_iterator(_start)); }
  const const_reverse_iterator rend() const {
    return (reverse_iterator(_start));
  }

  // Capacity ==================================================================
  // empty for c++98 __ checks whether the container is empty
  // returns true if the container is empty, false otherwise.
  // Checks if the container has no elements, i.e. whether begin() == end().
  bool empty() const { return (_start == _end); }

  // size for c++98 __ returns the number of elements
  // Returns the number of elements in the vector,
  // i.e. std::distance(begin(), end()). ????????? distance??? ?????? ?????????.
  size_type size() const { return (this->_end - this->_start); }

  // resize for c++98
  void resize(size_type n, value_type val = value_type()) {
    if (n > this->max_size())
      throw std::length_error("ft::vector::resize: n > max_size()");
    if (this->size() == n)
      return;
    if (n < this->size()) {
      while (this->size() != n)
        pop_back();
    } else {
      if (this->capacity() * 2 < n) reserve(n);
      while (this->size() != n) push_back(val);
    }
  }

  // max_size for c++98 __ returns the maximum possible number of elements
  // Returns the maximum number of elements that the vector can hold due to
  // system or library implementation limitations,
  // i.e. std::distance(begin(), end()) for the largest container.
  size_type max_size() const { return (_alloc.max_size()); }

  // reserve for c++98 __ requests that the vector capacity be at least enough
  // Increase the capacity of the vector (the total number of elements that the
  // vector can hold without requiring reallocation) to a value that's greater
  // or equal to new_cap. new_cap ??? capacity ?????? ??? ?????? capacity ??? ????????? ???
  // ??????. test ???????????? ????????? ???????????????, reserve ?????? ?????? ????????? ????????????.
  void reserve(size_type new_cap) {
    try {
      if (new_cap > this->max_size()) {
        throw std::length_error("new capacity must be less than max_size");
      }
      if (new_cap < this->capacity()) {
        return;
      }
      pointer   prev = _start;
      pointer   prev_end = _end;
      size_type prev_capa = this->capacity();
      size_type prev_size = this->size();

      _start = _alloc.allocate(new_cap);
      _end = _start;
      _capa_end = _start + new_cap;
      while (prev != prev_end) {
        _alloc.construct(_end, *prev);
        _alloc.destroy(prev);
        ++_end;
        ++prev;
      }
      _alloc.deallocate(prev - prev_size, prev_capa);
    } catch (const std::length_error& e) {
      std::cerr << e.what() << std::endl;
    }
  }

  // capacity for c++98 __ Returns the number of elements that the container has
  // currently allocated space for.
  size_type capacity() const { return (_capa_end - _start); }

  // Modifiers =================================================================
  // assign for c++98 __ assigns new contents to the container
  template <typename InputIterator>
  void assign(InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                     InputIterator>::type* = 0) {
    this->clear();
    size_type new_size = ft::distance(first, last);
    if (new_size <= this->capacity()) {
      for (; first != last; ++first, ++_end) _alloc.construct(_end, *first);
    } else {
      this->reserve(new_size);
      for (; first != last; ++first, ++_end) _alloc.construct(_end, *first);
    }
  }
  void assign(size_type count, const value_type& val) {
    this->clear();
    if (this->capacity() < count) {
      this->reserve(count);
      while (count--) _alloc.construct(_end++, val);
    } else {
      while (count--) _alloc.construct(_end++, val);
    }
  }

  // push_back for c++98 __ adds an element to the end
  // This effectively increases the container size by one, which causes an
  // automatic reallocation of the allocated storage space if -and only if- the
  // new vector size surpasses the current vector capacity.
  void push_back(const value_type& val) {
    if (_end == _capa_end) {
      size_type size = this->size();
      if (size == 0) {
        this->reserve(1);
      } else {
        this->reserve(2 * size);  // capacity() ?????? ?????????????????? ????????????. _end
                                  // ??? _capa_end ??? ?????? ????????? ????????? 2???
      }
    }
    _alloc.construct(_end, val);
    _end++;
  }

  // pop_back for c++98 __ removes the last element
  // This effectively reduces the container size by one.
  void pop_back() {
    if (this->size() != 0) {
      _alloc.destroy(--_end);
    }
  }

  // insert for c++98 __ inserts elements
  // Inserts elements at the specified location in the container.
  // inserts value before pos

  // ???????????? ???????????? ?????????. ????????? reserve ???????????? ??????. end ?????? ?????? ??????
  // ????????? ?????? ????????? ??????, ????????????. ????????? insert, end ??? ++??? ?????????
  iterator insert(iterator position, const value_type& val) {
    size_type pos = &*position - _start;
    size_type rpos = _end - &*position;

    if (this->size() == 0)
      this->reserve(1);
    else if (_end == _capa_end)
      this->reserve(2 * this->size());
    for (size_type i = 0; i < rpos; i++) {
      _alloc.construct(_end - i, *(_end - i - 1));
      _alloc.destroy(_end - i - 1);
    }
    _alloc.construct(_start + pos, val);
    _end++;
    return (iterator(_start + pos));
  }
  void insert(iterator position, size_type n, const value_type& val) {
    if (position > this->end() || position < this->begin()) return;

    size_type next_size = this->size() + n;
    size_type pos = &*position - _start;
    size_type prev_capa = this->capacity();
    size_type alloced_size = 0;
    pointer   new_start = 0;
    pointer   prev_capa_end = _capa_end;

    if (this->max_size() < next_size)
      throw std::length_error(
          "vector::insert: vector size exceeds maximum size");
    if (this->capacity() < next_size) {
      new_start = _alloc.allocate(next_size);
      _capa_end = new_start + next_size;
      alloced_size = next_size;
    } else {
      new_start = _alloc.allocate(this->capacity());
      _capa_end = new_start + this->capacity();
      alloced_size = this->capacity();
    }
    try {
      for (size_type i = 0; i < pos; ++i)
        _alloc.construct(new_start + i, *(_start + i));
      for (size_type i = 0; i < n; ++i)
        _alloc.construct(new_start + pos + i, val);
      for (size_type i = 0; i < this->size() - pos; ++i)
        _alloc.construct(new_start + pos + n + i, *(_start + pos + i));
    } catch (...) {
      for (size_type i = 0; i < pos; ++i) _alloc.destroy(new_start + i);
      for (size_type i = 0; i < n; ++i) _alloc.destroy(new_start + pos + i);
      for (size_type i = 0; i < this->size() - pos; ++i)
        _alloc.destroy(new_start + pos + n + i);
      _alloc.deallocate(new_start, alloced_size);
      _capa_end = prev_capa_end;
      throw;
    }

    for (size_type i = 0; i < this->size(); ++i) _alloc.destroy(_start + i);
    _alloc.deallocate(_start, prev_capa);
    _end = new_start + n + this->size();
    _start = new_start;
  }
  template <typename InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                     InputIterator>::type* = 0) {
    if (position > this->end() || position < this->begin()) return;

    size_type num = ft::distance(first, last);
    size_type next_size = this->size() + num;
    size_type prev_capa = this->capacity();
    size_type pos = &*position - _start;
    size_type alloced_size = 0;
    pointer   new_start = 0;
    pointer   prev_capa_ptr = _capa_end;

    if (this->max_size() < next_size)
      throw std::length_error(
          "vector::insert: vector size exceeds maximum size");
    if (this->capacity() < next_size) {
      new_start = _alloc.allocate(next_size);
      _capa_end = new_start + next_size;
      alloced_size = next_size;
    } else {
      new_start = _alloc.allocate(this->capacity());
      _capa_end = new_start + this->capacity();
      alloced_size = this->capacity();
    }
    try {
      for (size_type i = 0; i < pos; ++i)
        _alloc.construct(new_start + i, *(_start + i));
      for (size_type i = 0; i < num; ++i)
        _alloc.construct(new_start + pos + i, *(&*first++));
      for (size_type i = 0; i < this->size() - pos; ++i)
        _alloc.construct(new_start + pos + num + i, *(_start + pos + i));
    } catch (...) {
      for (size_type i = 0; i < pos; ++i) _alloc.destroy(new_start + i);
      for (size_type i = 0; i < num; ++i) _alloc.destroy(new_start + pos + i);
      for (size_type i = 0; i < this->size() - pos; ++i)
        _alloc.destroy(new_start + pos + num + i);
      _alloc.deallocate(new_start, alloced_size);
      _capa_end = prev_capa_ptr;
      throw;
    }
    for (size_type i = 0; i < this->size(); ++i) _alloc.destroy(_start + i);
    _alloc.deallocate(_start, prev_capa);
    _end = new_start + num + this->size();
    _start = new_start;
  }

  // erase for c++98 __ removes elements
  // Removes from the vector either a single element(position) or a range of
  // elements([first, last]).
  iterator erase(iterator position) {
    return (this->erase(position, position + 1));
  }
  iterator erase(iterator first, iterator last) {
    pointer prev_first = &*first;

    for (; first != last; ++first) _alloc.destroy(&*first);
    for (int i = 0; &*last + i != _end; ++i) {
      _alloc.construct(prev_first + i, *(&*last + i));
      _alloc.destroy(&*last + i);
    }
    _end -= (&*first -
             prev_first);  // ????????? ???????????? _end??? ????????? ????????? ?????? ???.
    return prev_first;
  }

  // swap for c++98 __ exchanges the contents of the container
  void swap(vector& x) {
    pointer        temp_start;
    pointer        temp_end;
    pointer        temp_capa_end;
    allocator_type temp_alloc;

    temp_start = _start;
    temp_end = _end;
    temp_capa_end = _capa_end;
    temp_alloc = _alloc;

    _start = x._start;
    _end = x._end;
    _capa_end = x._capa_end;
    _alloc = x._alloc;

    x._start = temp_start;
    x._end = temp_end;
    x._capa_end = temp_capa_end;
    x._alloc = temp_alloc;
  }

  // clear for c++98 __ clears the contents
  // Erases all elements from the vector(container is now empty). After this
  // call, size() returns zero.
  // Leaves the capacity() of the vector unchanged (note: the standard's
  // restriction on the changes to capacity is in the specification of
  // vector::reserve, see above).
  void clear() {
    while (_start != _end) {
      _alloc.destroy(--_end);
    }
  }
};  // class vector

// relational operators for c++98
template <typename T, typename Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  if (lhs.size() != rhs.size()) return false;
  typename vector<T, Alloc>::const_iterator lhs_it = lhs.begin();
  typename vector<T, Alloc>::const_iterator rhs_it = rhs.begin();

  while (lhs_it != lhs.end()) {
    if (*lhs_it != *rhs_it) return false;
    ++lhs_it;
    ++rhs_it;
  }
  return true;
}

template <typename T, typename Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <typename T, typename Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template <typename T, typename Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <typename T, typename Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return rhs < lhs;
}

template <typename T, typename Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs < rhs);
}

// swap for c++98 __ exchanges the contents of the container
template <typename T, typename Alloc>
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) {
  lhs.swap(rhs);
}

}  // namespace ft

#endif