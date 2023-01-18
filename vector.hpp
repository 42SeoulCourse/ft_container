#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

#include "enable_if.hpp"

template <typename T>
class vector {
  /********** Member types **********/
 public:
  typedef T                                     value_type;
  typedef Allocator                             allocator_type;
  typedef std::size_t                           size_type;
  typedef std::ptrdiff_t                        difference_type;
  typedef value_type&                           reference;
  typedef const value_type&                     const_reference;
  typedef Allocator::value_type*                pointer;
  typedef Allocator::const value_type*          const_pointer;
  typedef value_type*                           iterator;  // T -> value_type
  typedef const value_type*                     const_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  /********** Member functions **********/
 public:
 
};

#endif