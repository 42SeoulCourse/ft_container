#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

#include "enable_if.hpp"

namespace ft {

template <class T, class Allocator = std::allocator<T>>
class vector {
  /********** Member types **********/
 public:
  typedef T                            value_type;
  typedef Allocator                    allocator_type;
  typedef std::size_t                  size_type;
  typedef std::ptrdiff_t               difference_type;
  typedef value_type&                  reference;
  typedef const value_type&            const_reference;
  typedef Allocator::value_type*       pointer;
  typedef Allocator::const value_type* const_pointer;
  typedef typename std::iterator<std::random_access_iterator_tag, T> iterator;
  typedef typename std::iterator<std::random_access_iterator_tag, const T>
                                                const_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  /***************************** Member functions *****************************/

 public:
  // Common Things =============================================================
  // constructors for c++98 __ constructs the vector
  vector() : _size(0), _capacity(0), _data(NULL){};
  explicit vector(const Allocator& alloc){};
  explicit vector(size_type count, const value_type& value = value_type(),
                  const Allocator& alloc = Allocator()){};
  template <class InputIt>
  vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()){};
  vector(const vector& other){};

  // destructor for c++98 __ destructs the vector
  ~vector(){};

  // operator= for c++98 __ assigns new contents to the container
  // returns *this
  vector& operator=(const vector& other){};

  // get_allocator for c++98 __ returns the associated allocator
  allocator_type get_allocator() const {};

  // Element access ============================================================
  // at for c++98 __ access specified element with bounds checking.
  // Return reference to element at pos, exception if out of range is thrown
  reference       at(size_type pos){};
  const_reference at(size_type pos) const {};

  // operator[] for c++98 __ access specified element
  // Return reference to element at pos, no bounds checking is performed.
  reference       operator[](size_type pos){};
  const_reference operator[](size_type pos) const {};

  // front for c++98 __ access the first element
  // Return reference to the first element in the vector container
  // Calling front on an empty container is undefined.
  reference       front(){};
  const_reference front() const {};

  // back for c++98 __ access the last element
  // Return reference to the last element in the vector container
  // Calling back on an empty container is undefined.
  reference       back(){};
  const_reference back() const {};

  // Iterators =================================================================
  // begin for c++98 __ returns an iterator to the beginning
  // Returns an iterator to the first element of the vector.
  // If the vector is empty, the returned iterator will be equal to end().
  iterator       begin(){};
  const_iterator begin() const {};

  // end for c++98 __ returns an iterator to the end
  // Returns an iterator to the element following the last element of the
  // vector container.
  // This element acts as a placeholder; attempting to access it results in
  // undefined behavior.
  iterator       end(){};
  const_iterator end() const {};

  // rbegin for c++98 __ returns a reverse iterator to the beginning
  // Returns a reverse iterator to the first element of the reversed vector.
  // It corresponds to the last element of the non-reversed vector. If the
  // vector is empty, the returned iterator is equal to rend().
  reverse_iterator       rbegin(){};
  const_reverse_iterator rbegin() const {};

  // rend for c++98 __ returns a reverse iterator to the end
  // Returns a reverse iterator to the element following the last element of the
  // reversed vector. It corresponds to the element preceding the first element
  // of the non-reversed vector. This element acts as a placeholder, attempting
  // to access it results in undefined behavior.
  reverse_iterator       rend(){};
  const_reverse_iterator rend() const {};

  // Capacity ==================================================================
  // empty for c++98 __ checks whether the container is empty
  // returns true if the container is empty, false otherwise.
  // Checks if the container has no elements, i.e. whether begin() == end().
  bool empty() const {};

  // size for c++98 __ returns the number of elements
  // Returns the number of elements in the vector,
  // i.e. std::distance(begin(), end()).
  size_type size() const {};

  // max_size for c++98 __ returns the maximum possible number of elements
  // Returns the maximum number of elements that the vector can hold due to
  // system or library implementation limitations,
  // i.e. std::distance(begin(), end()) for the largest container.
  size_type max_size() const {};

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
  void reserve(size_type new_cap){};

  // capacity for c++98 __ Returns the number of elements that the container has
  // currently allocated space for.
  size_type capacity() const {};

  // Modifiers =================================================================
  // assign for c++98 __ assigns new contents to the container
  template <class InputIterator>
  void assign(InputIterator first, InputIterator last){};
  void assign(size_type n, const value_type& val){};

  // push_back for c++98 __ adds an element to the end
  // This effectively increases the container size by one, which causes an
  // automatic reallocation of the allocated storage space if -and only if- the
  // new vector size surpasses the current vector capacity.
  void push_back(const value_type& val){};

  // pop_back for c++98 __ removes the last element
  // This effectively reduces the container size by one.
  void pop_back(){};

  // insert for c++98 __ inserts elements
  // Inserts elements at the specified location in the container.
  // inserts value before pos
  iterator insert(iterator position, const value_type& val);
  void     insert(iterator position, size_type n, const value_type& val);
  template <class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last);

  // erase for c++98 __ removes elements
  // Removes from the vector either a single element(position) or a range of
  // elements([first, last]).
  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);

  // swap for c++98 __ exchanges the contents of the container
  // Exchanges the content of the container by the content of x, which is
  // another vector object of the same type. Sizes may differ.
  void swap(vector& x){};

  // clear for c++98 __ clears the contents
  // Erases all elements from the vector(container is now empty). After this
  // call, size() returns zero.
  // Leaves the capacity() of the vector unchanged (note: the standard's
  // restriction on the changes to capacity is in the specification of
  // vector::reserve, see above).
  void clear(){};
};

// relational operators for c++98
template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);

// swap for c++98 __ exchanges the contents of the container
template <class T, class Alloc>
void swap(vector<T, Alloc>& x, vector<T, Alloc>& y);

}  // namespace ft

#endif