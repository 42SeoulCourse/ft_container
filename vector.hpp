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
  typedef T                                            value_type;
  typedef Allocator                                    allocator_type;
  typedef typename allocator_type::size_type           size_type;
  typedef typename allocator_type::reference           reference;
  typedef typename allocator_type::const_reference     const_reference;
  typedef typename allocator_type::pointer             pointer;
  typedef typename allocator_type::const_pointer       const_pointer;
  typedef ft::random_access_iterator<value_type>       iterator;
  typedef ft::random_access_iterator<const value_type> const_iterator;
  typedef ft::reverse_iterator<iterator>               reverse_iterator;
  typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;
  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;

  /***************************** Member variables *****************************/
 private:
  pointer        _start;
  pointer        _end;
  pointer        _capa_end;
  allocator_type _alloc;

  /***************************** Member functions *****************************/
 public:
  // Common Things =============================================================
  // constructors for c++98 __ constructs the vector
  explicit vector()
      : _start(NULL), _end(NULL), _capa_end(NULL), _alloc(allocator_type()) {
    std::cout << "Create vector by Defalut vector constructor" << std::endl;
  }

  explicit vector(const allocator_type& alloc = allocator_type())
      : _start(NULL), _end(NULL), _capa_end(NULL), _alloc(alloc) {
    std::cout << "Create vector by allocator constructor" << std::endl;
  }

  explicit vector(size_type count, const value_type& value = value_type(),
                  const Allocator& alloc = allocator_type())
      : _alloc(alloc) {
    std::cout << "Create vector by Fill vector constructor" << std::endl;
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
    std::cout << "Create vector by Iterator vector constructor" << std::endl;
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

  // 매개변수를 const 로 받기 때문에 내부에서 직접 start를 바꿀 수 없기 때문에
  // p에 옮겨서 복사했다.
  vector(const vector& other) : _alloc(other._alloc) {
    std::cout << "Create vector by Copy vector constructor" << std::endl;
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
    std::cout << "Create vector by assignment operation" << std::endl;
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
    std::cout << "Destructs vector" << std::endl;
    this->clear();
    _alloc.deallocate(_start, this->capacity());
  }

  // get_allocator for c++98 __ returns the associated allocator
  allocator_type get_allocator() const { return this->_alloc; }

  // Element access ============================================================
  // at for c++98 __ access specified element with bounds checking.
  // Return reference to element at pos, exception if out of range is thrown
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

  // operator[] for c++98 __ access specified element
  // Return reference to element at pos, no bounds checking is performed.
  reference             operator[](size_type pos) { return this->_start[pos]; }
  const const_reference operator[](size_type pos) const {
    return this->_start[pos];
  }

  // front for c++98 __ access the first element
  // Return reference to the first element in the vector container
  // Calling front on an empty container is undefined.
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

  // back for c++98 __ access the last element
  // Return reference to the last element in the vector container
  // Calling back on an empty container is undefined.
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
  // begin for c++98 __ returns an iterator to the beginning
  // Returns an iterator to the first element of the vector.
  // If the vector is empty, the returned iterator will be equal to end().
  iterator       begin() { return (_start); }
  const_iterator begin() const { return (_start); }

  // end for c++98 __ returns an iterator to the end
  // Returns an iterator to the element following the last element of the
  // vector container.
  // This element acts as a placeholder; attempting to access it results in
  // undefined behavior.
  iterator       end() { return (_end); }
  const_iterator end() const { return (_end); }

  // rbegin for c++98 __ returns a reverse iterator to the beginning
  // Returns a reverse iterator to the first element of the reversed vector.
  // It corresponds to the last element of the non-reversed vector. If the
  // vector is empty, the returned iterator is equal to rend().
  reverse_iterator             rbegin() { return (reverse_iterator(_end)); }
  const const_reverse_iterator rbegin() const {
    return (reverse_iterator(_end));
  }

  // rend for c++98 __ returns a reverse iterator to the end
  // Returns a reverse iterator to the element following the last element of the
  // reversed vector. It corresponds to the element preceding the first element
  // of the non-reversed vector. This element acts as a placeholder, attempting
  // to access it results in undefined behavior.
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
  // i.e. std::distance(begin(), end()). 우리는 distance를 사용 못한다.
  size_type size() const { return (this->_end - this->_start); }

  // max_size for c++98 __ returns the maximum possible number of elements
  // Returns the maximum number of elements that the vector can hold due to
  // system or library implementation limitations,
  // i.e. std::distance(begin(), end()) for the largest container.
  size_type max_size() const { return (_alloc.max_size()); }

  // reserve for c++98 __ requests that the vector capacity be at least enough
  // Increase the capacity of the vector (the total number of elements that the
  // vector can hold without requiring reallocation) to a value that's greater
  // or equal to new_cap. If new_cap is greater than the current capacity(), new
  // storage is allocated, otherwise the function does nothing.
  // reserve() does not change the size of the vector.
  // If new_cap is greater than capacity(),
  // all iterators, including the past - the - end iterator,
  // and all references to the elements are invalidated.Otherwise,
  // no iterators or references are invalidated.
  // After a call to reserve(),
  // insertions will not trigger reallocation unless the insertion would make
  // the size of the vector greater than the value of capacity().
  void reserve(size_type new_cap) {
    try {
      if (new_cap <= capacity()) {
        throw std::invalid_argument(
            "New capacity must be greater than current");
      }
      T* new_vector = new T[new_cap];
      for (size_type i = 0; i < new_cap; i++) {
        new_vector[i] = _start[i];
      }
      delete[] _start;
      _start = new_vector;
      capacity = new_cap;
    } catch (const std::invalid_argument& e) {
      std::cerr << e.what() << std::endl;
    }
  }

  // capacity for c++98 __ Returns the number of elements that the container has
  // currently allocated space for.
  size_type capacity() const { return (_capa_end - _start); }

  // Modifiers =================================================================
  // assign for c++98 __ assigns new contents to the container
  template <typename InputIterator>
  void assign(InputIterator first, InputIterator last) {}
  void assign(size_type n, const value_type& val) {}

  // push_back for c++98 __ adds an element to the end
  // This effectively increases the container size by one, which causes an
  // automatic reallocation of the allocated storage space if -and only if- the
  // new vector size surpasses the current vector capacity.
  void push_back(const value_type& val) {}

  // pop_back for c++98 __ removes the last element
  // This effectively reduces the container size by one.
  void pop_back() {}

  // insert for c++98 __ inserts elements
  // Inserts elements at the specified location in the container.
  // inserts value before pos
  iterator insert(iterator position, const value_type& val) {}
  void     insert(iterator position, size_type n, const value_type& val);
  template <typename InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last);

  // erase for c++98 __ removes elements
  // Removes from the vector either a single element(position) or a range of
  // elements([first, last]).
  iterator erase(iterator position) {}
  iterator erase(iterator first, iterator last) {}

  // swap for c++98 __ exchanges the contents of the container
  // Exchanges the content of the container by the content of x, which is
  // another vector object of the same type. Sizes may differ.
  void swap(vector& x) {}

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
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <typename T, typename Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <typename T, typename Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <typename T, typename Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <typename T, typename Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <typename T, typename Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

// swap for c++98 __ exchanges the contents of the container
template <typename T, typename Alloc>
void swap(vector<T, Alloc>& x, vector<T, Alloc>& y);

}  // namespace ft

#endif