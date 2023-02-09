#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iterator>

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
  typedef const V                       &reference;
  typedef const V                       *pointer;
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

template <typename T, typename Allocator>
class RB_tree_base {
 public:
  typedef Allocator allocator_type;
  typedef typename Allocator::template rebind<RB_tree_base<T> >::other
                 node_allocator_type;
  allocator_type get_allocator() const { return node_allocator; }

 protected:
  RB_tree_node<T>    *header;
  allocator_type      value_allocator;
  node_allocator_type node_allocator;

  RB_tree_node<T> *get_node() { return node_allocator.allocate(1); }
  void put_node(RB_tree_node<T> *p) { node_allocator.deallocate(p, 1); }

 public:
  RB_tree_base(const allocator_type &alloc = allocator_type())
      : value_allocator(alloc) {
    header = get_node();
  }
  ~RB_tree_base() { put_node(header); }
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Alloc = std::allocator<Value> >
class RB_tree : protected RB_tree_base<V, Allocator> {
  typedef RB_tree_base<V, Allocator> base;
  typedef RB_tree_node<V>           *node_type;
  typedef RB_tree_node_color         color_type;
  // using Base::header;
  // using Base::get_node;
  // using Base::put_node;
  // using Base::value_allocator;

 public:
  // 트리 노드 요소
  typedef Key               key_type;
  typedef Value             value_type;
  typedef value_type       *pointer;
  typedef const value_type *const_pointer;
  typedef value_type       &reference;
  typedef const value_type &const_reference;
  typedef size_t            size_type;
  typedef ptrdiff_t         difference_type;

  // 트리 이터레이터
  typedef RB_tree_iterator<value_type>       iterator;
  typedef RB_tree_const_iterator<value_type> const_iterator;

  typedef ft::reverse_iterator<iterator>       reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // 트리 할당기
  typedef typename base::allocator_type allocator_type;
  allocator_type get_allocator() const { return base::get_allocator(); }

 private:
  size_type node_count;   // 노드 개수
  Compare   key_compare;  // 키 비교 함수

  node_type create_node(const value_type &x) {
    node_type tmp = get_node();
    try {
      value_allocator.construct(&tmp->value, x);
      tmp->left = 0;
      tmp->right = 0;
    } catch (...) {
      put_node(tmp);
      throw;
    }
    return tmp;
  }

  node_type clone_node(node_type x) {
    node_type tmp = create_node(x->value);
    tmp->color = x->color;
    tmp->left = 0;
    tmp->right = 0;
    return tmp;
  }

  void destroy_node(node_type p) {
    value_allocator.destroy(&p->value);
    put_node(p);
  }

  // 루트와 min, max
  node_type &root() const { return (link_type &)(header->parent); }
  node_type &leftmost() const { return (link_type &)(header->left;) }
  node_type &rightmost() const { return (link_type &)(header->right;) }

  static node_type minimum(node_type x) { return RB_tree_node<V>::minimum(x); }
  static node_type maximum(node_type x) { return RB_tree_node<V>::maximum(x); }

  // 노드의 왼쪽, 오른쪽, 루트 체크
  static bool is_left_child(link_type x) { return x == x->parent->left; }
  static bool is_right_child(link_type x) { return x == x->parent->right; }
  static bool is_root(node_type x) { return x->parent == 0; }

  // 노드의 삼촌
  static node_type &uncle(node_type x) {
    return (is_left_child(x->parent) ? x->parent->parent->right
                                     : x->parent->parent->left);
  }
  // 노드의 형제
  static node_type &sibling(node_type x) {
    return (is_left_child(x) ? x->parent->right : x->parent->left);
  }

  static reference   value(node_type x) { return x->value; }
  static const Key  &key(node_type x) { return KeyOfValue()(value(x)); }
  static color_type &color(node_type x) { return (color_type &)(x->color); }

 public:
  RB_tree() : base(allocator_type()), node_count(0), key_compare(Compare()) {
    empty_initialize();
  }

  RB_tree(const Compare &comp, const allocator_type &alloc = allocator_type())
      : base(alloc), node_count(0), key_compare(comp) {
    empty_initialize();
  }

  RB_tree(const Rb_tree<Key, Value, KeyOfValue, Compare, Allocator> &x)
      : base(x.get_allocator()), node_count(0), key_compare(x.key_compare) {
    if (x.root() == 0) {
      empty_initialize();
    } else {
      root() = copy(x.root(), header);
      leftmost() = minimum(root());
      rightmost() = maximum(root());
      node_count = x.node_count;
    }
  }

  ~RB_tree(){clear()};

  RB_tree &operator=(const RB_tree &x) {
    if (this != &x) {
      clear();
      node_count = 0;
      key_compare = x.key_compare;
      if (x.root() == 0) {
        root() = 0;
        leftmost() = header;
        rightmost() = header;
      } else {
        root() = copy(x.root(), header);
        leftmost() = minimum(root());
        rightmost() = maximum(root());
      }
      node_count = x.node_count;
    }
    return *this;
  }

  
};

};  // namespace ft

#endif RED_BLACK_TREE_HPP