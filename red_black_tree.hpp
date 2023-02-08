#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "iterator.hpp"

namespace ft {
// 컬러 설정
typedef bool             RB_tree_node_color;
const RB_tree_node_color RED = false;
const RB_tree_node_color BLACK = true;

// 노드 구조체 및 successor, predecessor
template <typename V>
struct RB_tree_node {
  typedef RB_tree_node_color         color_type;
  typedef RB_tree_node_color<Value> *node_type;

  V          value;
  color_type color;
  node_type  parent;
  node_type  left;
  node_type  right;

  // 노드가 어떤 타입인지 모르기때문에 x라는 미지수를 사용하자
  static node_type minimum(node_type x) {
    while (x->left != 0) x = x->left;
    return x;
  }
  static node_type maximum(node_type x) {
    while (x->right != 0) x = x->right;
    return x;
  }
};

template <typename V>
class RB_tree_iterator {
  typedef V                              value_type;
  typedef V                             &reference;
  typedef V                             *pointer;
  typedef ptrdiff_t                      difference_type;
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef RB_tree_node<V>               *node_type;
  node_type                              node;

 public:
  RB_tree_iterator() : node(0) {}
  RB_tree_iterator(node_type x) : node(x) {}
  RB_tree_iterator(const RB_tree_iterator<V> &it) : node(it.node) {}

  // reference operator*() const { return node_type(node)->value; }
  reference operator*() const { return node->value; }
  pointer   operator->() const { return &(operator*()); }

  RB_tree_iterator &operator++() {
    increment();
    return *this;
  }

  RB_tree_iterator operator++(int) {
    RB_tree_iterator tmp = *this;
    increment();
    return tmp;
  }

  RB_tree_iterator &operator--() {
    decrement();
    return *this;
  }

  RB_tree_iterator operator--(int) {
    RB_tree_iterator tmp = *this;
    decrement();
    return tmp;
  }

  bool operator==(const RB_tree_iterator &it) const { return node == it.node; }
  bool operator!=(const RB_tree_iterator &it) const { return node == it.node; }

 protected:
  void increment() {
    // 오른쪽으로 갔다가, 왼쪽으로 간다.
    if (node->right != 0) {
      node = node->right;
      while (node->left != 0) node = node->left;
    } else {  // 오른쪽이 없으면, 부모로 간다. 부모가 왼쪽일 때까지 올라간다.
              // 부모가 왼쪽이면, 부모를 리턴한다.
      node_type y = node->parent;
      while (node == y->right) {
        node = y;
        y = y->parent;
      }
      if (node->right != y) node = y;
    }
  }

  void decrement() {
    // 노드가 헤더인지 아닌지 확인. 헤더를 RED 로, 헤더의 parent 는 root 이다.
    // head 를 end 라고 생각하면, -- 했을 때 right most 값
    if (node->color == RED && node->parent->parent == node)
      node = node->right;
    else if (node->left != 0) {  // 왼쪽 자식이 있으면 왼쪽 자식의 right most 값
      node_type y = node->left;
      while (y->right != 0) y = y->right;
      node = y;
    } else {  // 왼쪽 자식이 없으면 부모로 올라간다. 부모가 오른쪽일 때까지
              // 올라간다. 그때 오른쪽 노드의 부모
      node_type y = node->parent;
      while (node == y->left) {
        node = y;
        y = y->parent;
      }
      node = y;
    }
  }
};

template <typename V>
class RB_tree_const_iterator {
  typedef V                              value_type;
  typedef const V                             &reference;
  typedef const V                             *pointer;
  typedef ptrdiff_t                      difference_type;
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef RB_tree_node<V>               *node_type;
  node_type                              node;

 public:
  RB_tree_const_iterator() : node(0) {}
  RB_tree_const_iterator(node_type x) : node(x) {}
  RB_tree_const_iterator(const RB_tree_iterator<V> &it) : node(it.node) {}
  RB_tree_const_iterator(const RB_tree_const_iterator<V> &it) : node(it.node) {}

  // reference operator*() const { return node_type(node)->value; }
  reference operator*() const { return node->value; }
  pointer   operator->() const { return &(operator*()); }

  RB_tree_iterator &operator++() {
    increment();
    return *this;
  }

  RB_tree_iterator operator++(int) {
    RB_tree_iterator tmp = *this;
    increment();
    return tmp;
  }

  RB_tree_iterator &operator--() {
    decrement();
    return *this;
  }

  RB_tree_iterator operator--(int) {
    RB_tree_iterator tmp = *this;
    decrement();
    return tmp;
  }

  bool operator==(const RB_tree_iterator &it) const { return node == it.node; }
  bool operator!=(const RB_tree_iterator &it) const { return node == it.node; }

 protected:
  void increment() {
    // 오른쪽으로 갔다가, 왼쪽으로 간다.
    if (node->right != 0) {
      node = node->right;
      while (node->left != 0) node = node->left;
    } else {  // 오른쪽이 없으면, 부모로 간다. 부모가 왼쪽일 때까지 올라간다.
              // 부모가 왼쪽이면, 부모를 리턴한다.
      node_type y = node->parent;
      while (node == y->right) {
        node = y;
        y = y->parent;
      }
      if (node->right != y) node = y;
    }
  }

  void decrement() {
    // 노드가 헤더인지 아닌지 확인. 헤더를 RED 로, 헤더의 parent 는 root 이다.
    // head 를 end 라고 생각하면, -- 했을 때 right most 값
    if (node->color == RED && node->parent->parent == node)
      node = node->right;
    else if (node->left != 0) {  // 왼쪽 자식이 있으면 왼쪽 자식의 right most 값
      node_type y = node->left;
      while (y->right != 0) y = y->right;
      node = y;
    } else {  // 왼쪽 자식이 없으면 부모로 올라간다. 부모가 오른쪽일 때까지
              // 올라간다. 그때 오른쪽 노드의 부모
      node_type y = node->parent;
      while (node == y->left) {
        node = y;
        y = y->parent;
      }
      node = y;
    }
  }
};

};  // namespace ft

#endif RED_BLACK_TREE_HPP