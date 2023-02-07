#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "iterator.hpp"

// 621 ~ 644 tree_node_base_type
// 716 ~ 742 tree_node_base <- 해야함
// 744 ~ 757 tree_node

// 713줄 __left_
// 2074 __right_, __parent_
namespace ft {

template <typename VoidPtr>
class tree_node_base;

template <typename Pointer>
class tree_end_node;

template <typename Tp, typename Value>
class tree_node;

/******************************************************************************/
// 621 ~ 644 tree_node_base_type
template <typename VoidPtr>
struct tree_node_base_types {
  typedef VoidPtr                      void_pointer;
  typedef tree_node_base<void_pointer> node_base_type;

  typedef typename rebind_pointer<void_pointer, node_base_ptr>::type
                                           node_base_pointer;
  typedef tree_end_node<node_base_pointer> end_node_type;
  typedef typename rebind_pointer<void_pointer, end_node_ptr>::type
      end_node_pointer;

  // #if defined(_LIBCPP_ABI_TREE_REMOVE_NODE_POINTER_UB)
  //   typedef __end_node_pointer __parent_pointer;
  // #else
  //   typedef typename conditional<is_pointer<__end_node_pointer>::value,
  //                                __end_node_pointer,
  //                                __node_base_pointer>::type
  //       __parent_pointer;
  // #endif

  //  private:
  //   static_assert(
  //       (is_same<typename pointer_traits<_VoidPtr>::element_type,
  //       void>::value),
  //       "_VoidPtr does not point to unqualified void type");
};

// 716 ~ 742 tree_node_base
template <typename VoidPtr>
class tree_node_base : public tree_node_base_types<VoidPtr>::end_node_type {
  typedef tree_node_base_types<VoidPtr> NodeBaseTypes;

 public:
  typedef typename NodeBaseTypes::node_base_pointer pointer;
  typedef typename NodeBaseTypes::parent_pointer    parent_pointer;

  pointer        right;
  parent_pointer parent;
  bool           is_black;

  //   _LIBCPP_INLINE_VISIBILITY
  //   pointer __parent_unsafe() const { return static_cast<pointer>(__parent_);
  //   }

  //   _LIBCPP_INLINE_VISIBILITY
  //   void __set_parent(pointer __p) {
  //     __parent_ = static_cast<__parent_pointer>(__p);
  //   }

 private:
  ~tree_node_base() = delete;
  tree_node_base(const tree_node_base&) = delete;
  tree_node_base& operator=(const tree_node_base&) = delete;
};

// 744 ~ 757 tree_node
template <typename Tp, typename VoidPtr>
class tree_node : public tree_node_base<VoidPtr> {
 public:
  typedef Tp node_value_type;

  node_value_type value;

 private:
  ~tree_node() = delete;
  tree_node(const tree_node&) = delete;
  tree_node& operator=(const tree_node&) = delete;
};

};  // namespace ft

#endif RED_BLACK_TREE_HPP