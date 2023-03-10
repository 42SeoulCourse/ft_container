#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iterator>

#include "iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {
typedef bool             RB_tree_node_color;
const RB_tree_node_color RED = false;
const RB_tree_node_color BLACK = true;

template <typename Value>
struct RB_tree_node {
  typedef RB_tree_node_color   color_type;
  typedef RB_tree_node<Value> *node_type;

  Value      value_field;
  color_type color;
  node_type  parent;
  node_type  left;
  node_type  right;

  static node_type minimum(node_type x) {
    while (x->left != 0) x = x->left;
    return x;
  }
  static node_type maximum(node_type x) {
    while (x->right != 0) x = x->right;
    return x;
  }
};

template <typename Value>
struct RB_tree_iterator {
  typedef Value                          value_type;
  typedef Value                         &reference;
  typedef Value                         *pointer;
  typedef ptrdiff_t                      difference_type;
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef RB_tree_node<Value>           *node_type;

  node_type node;

 public:
  RB_tree_iterator() {}
  RB_tree_iterator(node_type x) { node = x; }
  RB_tree_iterator(const RB_tree_iterator<Value> &it) { node = it.node; }

  // reference operator*() const { return node_type(node)->value; }
  reference operator*() const { return node->value_field; }
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

  bool operator==(const RB_tree_iterator<Value> &x) const {
    return node == x.node;
  }
  bool operator!=(const RB_tree_iterator<Value> &x) const {
    return node != x.node;
  }

 protected:
  void increment() {
    // ??????????????? ?????????, ???????????? ??????.
    if (node->right != 0) {
      node = node->right;
      while (node->left != 0) node = node->left;
    } else {  // ???????????? ?????????, ????????? ??????. ????????? ????????? ????????? ????????????.
              // ????????? ????????????, ????????? ????????????.
      node_type y = node->parent;
      while (node == y->right) {
        node = y;
        y = y->parent;
      }
      if (node->right != y) node = y;
    }
  }

  void decrement() {
    // ????????? ???????????? ????????? ??????. ????????? RED ???, ????????? parent ??? root ??????.
    // head ??? end ?????? ????????????, -- ?????? ??? right most ???
    if (node->color == RED && node->parent->parent == node)
      node = node->right;
    else if (node->left != 0) {  // ?????? ????????? ????????? ?????? ????????? right most ???
      node_type y = node->left;
      while (y->right != 0) y = y->right;
      node = y;
    } else {  // ?????? ????????? ????????? ????????? ????????????. ????????? ???????????? ?????????
              // ????????????. ?????? ????????? ????????? ??????
      node_type y = node->parent;
      while (node == y->left) {
        node = y;
        y = y->parent;
      }
      node = y;
    }
  }
};

template <typename Value>
struct RB_tree_const_iterator {
  typedef Value                          value_type;
  typedef const Value                   &reference;
  typedef const Value                   *pointer;
  typedef ptrdiff_t                      difference_type;
  typedef ft::bidirectional_iterator_tag iterator_category;

  typedef RB_tree_node<value_type> *node_type;

  node_type node;

  RB_tree_const_iterator() {}
  RB_tree_const_iterator(node_type x) { node = x; }
  RB_tree_const_iterator(const RB_tree_iterator<value_type> &it) {
    node = it.node;
  }
  RB_tree_const_iterator(const RB_tree_const_iterator<value_type> &it) {
    node = it.node;
  }

  // reference operator*() const { return node_type(node)->value; }
  reference operator*() const { return node->value_field; }
  pointer   operator->() const { return &(operator*()); }

  RB_tree_const_iterator &operator++() {
    increment();
    return *this;
  }

  RB_tree_const_iterator operator++(int) {
    RB_tree_const_iterator tmp = *this;
    increment();
    return tmp;
  }

  RB_tree_const_iterator &operator--() {
    decrement();
    return *this;
  }

  RB_tree_const_iterator operator--(int) {
    RB_tree_const_iterator tmp = *this;
    decrement();
    return tmp;
  }

  bool operator==(const RB_tree_const_iterator &it) const {
    return node == it.node;
  }
  bool operator!=(const RB_tree_const_iterator &it) const {
    return node != it.node;
  }

 protected:
  void increment() {
    if (node->right != 0) {
      node = node->right;
      while (node->left != 0) node = node->left;
    } else {
      node_type y = node->parent;
      while (node == y->right) {
        node = y;
        y = y->parent;
      }
      if (node->right != y) node = y;
    }
  }

  void decrement() {
    if (node->color == RED && node->parent->parent == node)
      node = node->right;
    else if (node->left != 0) {  // ?????? ????????? ????????? ?????? ????????? right most ???
      node_type y = node->left;
      while (y->right != 0) y = y->right;
      node = y;
    } else {  // ?????? ????????? ????????? ????????? ????????????. ????????? ???????????? ?????????
              // ????????????. ?????? ????????? ????????? ??????
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
  typedef typename allocator_type::template rebind<RB_tree_node<T> >::other
                 node_allocator_type;
  allocator_type get_allocator() const { return node_allocator; }

 protected:
  RB_tree_node<T>    *header;
  allocator_type      value_allocator;
  node_allocator_type node_allocator;

  RB_tree_node<T> *get_node() { return node_allocator.allocate(1); }
  void             put_node(RB_tree_node<T> *p) { node_allocator.deallocate(p, 1); }

 public:
  RB_tree_base(const allocator_type &alloc = allocator_type())
      : value_allocator(alloc) {
    header = get_node();
  }
  ~RB_tree_base() { put_node(header); }
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Allocator = std::allocator<Value> >
class RB_tree : protected RB_tree_base<Value, Allocator> {
  typedef RB_tree_base<Value, Allocator> base;
  typedef RB_tree_node<Value>           *node_type;
  typedef RB_tree_node_color             color_type;
  using base::get_node;
  using base::header;
  using base::put_node;
  using base::value_allocator;

 public:
  // ?????? ?????? ??????
  typedef Key               key_type;
  typedef Value             value_type;
  typedef value_type       *pointer;
  typedef const value_type *const_pointer;
  typedef value_type       &reference;
  typedef const value_type &const_reference;
  typedef size_t            size_type;
  typedef ptrdiff_t         difference_type;

  // ?????? ???????????????
  typedef RB_tree_iterator<value_type>       iterator;
  typedef RB_tree_const_iterator<value_type> const_iterator;

  typedef ft::reverse_iterator<iterator>       reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  // ?????? ?????????
  typedef typename base::allocator_type allocator_type;
  allocator_type                        get_allocator() const { return base::get_allocator(); }

 private:
  size_type node_count;   // ?????? ??????
  Compare   key_compare;  // ??? ?????? ??????

  node_type create_node(const value_type &x) {
    node_type tmp = get_node();
    try {
      value_allocator.construct(&tmp->value_field, x);
      tmp->left = 0;
      tmp->right = 0;
    } catch (...) {
      put_node(tmp);
      throw;
    }
    return tmp;
  }

  node_type clone_node(node_type x) {
    node_type tmp = create_node(x->value_field);
    tmp->color = x->color;
    tmp->left = 0;
    tmp->right = 0;
    return tmp;
  }

  void destroy_node(node_type p) {
    value_allocator.destroy(&p->value_field);
    put_node(p);
  }

  // ????????? min, max
  node_type &root() const { return (node_type &)(header->parent); }
  node_type &leftmost() const { return (node_type &)(header->left); }
  node_type &rightmost() const { return (node_type &)(header->right); }

  static node_type minimum(node_type x) {
    return RB_tree_node<Value>::minimum(x);
  }
  static node_type maximum(node_type x) {
    return RB_tree_node<Value>::maximum(x);
  }

  // ????????? ??????, ?????????, ?????? ??????
  static bool is_left_child(node_type x) { return x == x->parent->left; }
  static bool is_right_child(node_type x) { return x == x->parent->right; }
  static bool is_root(node_type x) { return x->parent == 0; }

  // ????????? ??????
  static node_type &uncle(node_type x) {
    return (is_left_child(x->parent) ? x->parent->parent->right
                                     : x->parent->parent->left);
  }
  // ????????? ??????
  static node_type &sibling(node_type x) {
    return (is_left_child(x) ? x->parent->right : x->parent->left);
  }

  static reference   value(node_type x) { return x->value_field; }
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

  RB_tree(const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &x)
      : base(x.get_allocator()), node_count(0), key_compare(x.key_compare) {
    if (x.root() == 0) {
      empty_initialize();
    } else {
      root() = copy(x.root(), header);
      leftmost() = minimum(root());
      rightmost() = maximum(root());
    }
    node_count = x.node_count;
  }

  ~RB_tree() { clear(); }

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

 public:
  // ?????????
  Compare                key_comp() const { return key_compare; }
  iterator               begin() { return leftmost(); }
  const_iterator         begin() const { return leftmost(); }
  iterator               end() { return header; }
  const_iterator         end() const { return header; }
  reverse_iterator       rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator       rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  bool      empty() const { return node_count == 0; }
  size_type size() const { return node_count; }
  size_type max_size() const { return size_type(-1); }

  void swap(RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &t) {
    std::swap(header, t.header);
    std::swap(node_count, t.node_count);
    std::swap(key_compare, t.key_compare);
  }

  pair<iterator, bool> insert_unique(const value_type &v) {
    node_type y = header;
    node_type x = root();
    bool      comp = true;
    // ?????? ??????
    while (x != 0) {
      y = x;
      comp = key_compare(KeyOfValue()(v), key(x));
      x = comp ? x->left : x->right;  // nil ??? ????????? ??????
    }
    // ????????? ??????
    iterator j = iterator(y);
    if (comp) {
      if (j == begin())
        return pair<iterator, bool>(insert(y, v), true);
      else
        --j;
    }
    // ?????? ???????????? ????????? false
    if (key_compare(key(j.node), KeyOfValue()(v)))
      return pair<iterator, bool>(insert(y, v), true);
    return pair<iterator, bool>(j, false);
  }

  iterator insert_unique(iterator position, const value_type &v) {
    if (position.node == header->left) {  // ????????? ????????? begin();
      if (size() > 0 && key_compare(KeyOfValue()(v), key(position.node)))
        return insert(position.node, v);  // ????????? ????????? ?????? ?????? ???
      else
        return insert_unique(v)
            .first;                        // ????????? ????????? ?????? ?????? ????????? ????????? ???
    } else if (position.node == header) {  // ????????? ????????? ????????? ???
      if (key_compare(key(rightmost()), KeyOfValue()(v)))
        return insert(rightmost(),
                      v);  // ????????? ????????? ?????? ??? ????????? ????????? ???
      else
        return insert_unique(v).first;  // ????????? ????????? ?????? ??? ????????? ???
    } else {
      iterator before = position;
      --before;
      if (key_compare(key(before.node), KeyOfValue()(v)) &&
          key_compare(KeyOfValue()(v), key(position.node)))
        if (position.node->left == 0)
          return insert(position.node,
                        v);  // ????????? ????????? position??? ????????? ???
        else
          return insert_unique(v).first;  // ????????? ????????? position??? ????????? ???
      else
        return insert_unique(v).first;  // ????????? ????????? position??? ????????? ?????? ???
    }
  }

  template <typename InputIterator>
  void insert_unique(InputIterator first, InputIterator last) {
    for (; first != last; ++first) insert_unique(*first);
  };

  // delete
  void erase(iterator position) {
    node_type n = RB_tree_rebalance_for_erase(position.node);
    destroy_node(n);
    --node_count;
  }

  size_type erase(const key_type &x) {
    ft::pair<iterator, iterator> p = equal_range(x);
    size_type                    n = ft::distance(p.first, p.second);
    erase(p.first, p.second);
    return n;
  }

  void erase(iterator first, iterator last) {
    if (first == begin() && last == end())
      clear();
    else
      while (first != last) erase(first++);
  }

  void erase(const key_type *first, const key_type *last) {
    while (first != last) erase(*first++);
  }

  void clear() {
    if (node_count != 0) {
      erase(root());
      leftmost() = header;
      root() = 0;
      rightmost() = header;
      node_count = 0;
    }
  }

 public:
  iterator find(const key_type &k) {
    node_type y = header;
    node_type x = root();
    while (x != 0) {
      // k ??? x ?????? ????????? ????????? ????????????
      if (key_compare(key(x), k) == false) {
        // ????????? y = x ??? ?????? y ??? ?????? ????????? ??????, ?????? j??? ??????
        y = x;
        x = x->left;
      } else
        x = x->right;
    }
    iterator j = iterator(y);
    // j ??? end() ????????? k ??? j ?????? ????????? end() ??????
    // ????????? j ??????
    return (j == end() || key_compare(k, key(j.node))) ? end() : j;
  }

  const_iterator find(const key_type &k) const {
    node_type y = header;
    node_type x = root();

    while (x != 0) {
      if (key_compare(key(x), k) == false) {
        y = x;
        x = x->left;
      } else
        x = x->right;
    }
    const_iterator j = const_iterator(y);
    return ((j == end() || key_compare(k, key(j.node))) ? end() : j);
  }

  size_type count(const key_type &k) const {
    ft::pair<const_iterator, const_iterator> p = equal_range(k);
    size_type                                n = ft::distance(p.first, p.second);
    return n;
  }

  // key_compare(element(x), k) ??? false ??? ??????. x >= k
  iterator lower_bound(const key_type &k) {
    node_type y = header;
    node_type x = root();

    while (x != 0) {
      if (key_compare(key(x), k) == false) {
        y = x;
        x = x->left;
      } else
        x = x->right;
    }
    return iterator(y);
  }

  iterator upper_bound(const key_type &k) {
    node_type y = header;
    node_type x = root();

    while (x != 0) {
      if (key_compare(k, key(x))) {
        y = x;
        x = x->left;
      } else
        x = x->right;
    }
    return iterator(y);
  }

  const_iterator lower_bound(const key_type &k) const {
    node_type y = header;
    node_type x = root();

    while (x != 0) {
      if (key_compare(key(x), k) == false) {
        y = x;
        x = x->left;
      } else
        x = x->right;
    }
    return const_iterator(y);
  }

  const_iterator upper_bound(const key_type &k) const {
    node_type y = header;
    node_type x = root();

    while (x != 0) {
      if (key_compare(k, key(x))) {
        y = x;
        x = x->left;
      } else
        x = x->right;
    }
    return const_iterator(y);
  }

  ft::pair<iterator, iterator> equal_range(const key_type &k) {
    return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
  }

  ft::pair<const_iterator, const_iterator> equal_range(
      const key_type &k) const {
    return ft::pair<const_iterator, const_iterator>(lower_bound(k),
                                                    upper_bound(k));
  }

 private:
  void empty_initialize() {
    color(header) = RED;
    root() = 0;
    leftmost() = header;
    rightmost() = header;
  }

  // insert
  iterator insert(node_type y, const value_type &v) {
    node_type z;

    if (y == header || key_compare(KeyOfValue()(v), key(y))) {
      z = create_node(v);
      y->left = z;
      if (y == header) {
        root() = z;
        rightmost() = z;
      } else if (y == leftmost())
        leftmost() = z;
    } else {
      z = create_node(v);
      y->right = z;
      if (y == rightmost()) rightmost() = z;
    }
    z->parent = y;
    z->left = 0;
    z->right = 0;
    RB_tree_rebalance_for_insert(z);
    ++node_count;
    return iterator(z);
  }

  node_type copy(node_type x, node_type p) {
    node_type top = clone_node(x);
    top->parent = p;

    try {
      if (x->right) top->right = copy(x->right, top);
      p = top;
      x = x->left;

      while (x != 0) {
        node_type y = clone_node(x);
        p->left = y;
        y->parent = p;
        if (x->right) y->right = copy(x->right, y);
        p = y;
        x = x->left;
      }
    } catch (...) {
      erase(top);
      throw;
    }
    return top;
  }

  void erase(node_type x) {
    while (x != 0) {
      erase(x->right);
      node_type y = x->left;
      destroy_node(x);
      x = y;
    }
  }

  void RB_tree_rotate_left(node_type x) {
    node_type y = x->right;
    x->right = y->left;
    if (y->left != 0) y->left->parent = x;
    y->parent = x->parent;

    if (x == root())
      root() = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  void RB_tree_rotate_right(node_type x) {
    node_type y = x->left;
    x->left = y->right;
    if (y->right != 0) y->right->parent = x;
    y->parent = x->parent;

    if (x == root())
      root() = y;
    else if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
    y->right = x;
    x->parent = y;
  }

  void RB_tree_rebalance_for_insert(node_type n) {
    n->color = RED;

    // case4 ?????? ????????? ??????
    if (n == root()) {
      n->color = BLACK;
      return;
    }
    // case5 ?????? ????????? ????????? ??????
    if (n->parent->color == BLACK) return;
    // case1 ?????? ????????? ????????? ????????? ??????
    node_type u = uncle(n);
    if (u && u->color == RED) {
      n->parent->color = BLACK;
      u->color = BLACK;
      n->parent->parent->color = RED;
      RB_tree_rebalance_for_insert(n->parent->parent);
      return;
    }
    // case2 ?????? ????????? ????????? ?????????, ????????? ?????? ??? ???????????? ??????, ????????? ??????
    if (n == n->parent->right && n->parent == n->parent->parent->left) {
      RB_tree_rotate_left(n->parent);
      n = n->left;
    } else if (n == n->parent->left && n->parent == n->parent->parent->right) {
      RB_tree_rotate_right(n->parent);
      n = n->right;
    }
    // case3 ?????? ????????? ????????? ??????, ????????? ?????? ??? ???????????? ??????, ????????? ??????
    n->parent->color = BLACK;
    n->parent->parent->color = RED;
    if (n == n->parent->left && n->parent == n->parent->parent->left)
      RB_tree_rotate_right(n->parent->parent);
    else
      RB_tree_rotate_left(n->parent->parent);
  }

  node_type RB_tree_rebalance_for_erase(node_type target) {
    node_type successor = target;
    node_type c = 0;
    node_type c_parent = 0;

    // ?????? ?????? ??????
    if (successor->left == 0)        // target has at most one non-null child. successor == target.
      c = successor->right;          // c might be null.
    else if (successor->right == 0)  // target has exactly one non-null child. successor == target.
      c = successor->left;           // c is not null.
    else {                           // target has two non-null children.
      successor = successor->right;  // Set successor to target's successor. c might be null.
      while (successor->left != 0) successor = successor->left;
      c = successor->right;
    }

    // ????????? ????????? ????????? 2?????? ??????
    if (successor != target) {
      target->left->parent = successor;
      successor->left = target->left;
      if (successor != target->right) {
        c_parent = successor->parent;
        if (c) c->parent = successor->parent;
        successor->parent->left = c;
        successor->right = target->right;
        target->right->parent = successor;
      } else
        c_parent = successor;
      if (root() == target)
        root() = successor;
      else if (target->parent->left == target)
        target->parent->left = successor;
      else
        target->parent->right = successor;
      successor->parent = target->parent;
      std::swap(successor->color, target->color);
      successor = target;
      // successor now points to node to be actually deleted
    } else {  // successor ==target
      c_parent = successor->parent;
      if (c) c->parent = successor->parent;

      if (root() == target)
        root() = c;
      else if (target->parent->left == target)
        target->parent->left = c;
      else
        target->parent->right = c;

      if (leftmost() == target) {
        if (target->right == 0)  // target->left must be null also
          leftmost() = target->parent;
        // makes leftmost == header if target == root
        else
          leftmost() = RB_tree_node<Value>::minimum(c);
      }
      if (rightmost() == target) {
        if (target->left == 0)  // target->right must be null also
          rightmost() = target->parent;
        // make s rightmost == header if target == root
        else  // c == target->left
          rightmost() = RB_tree_node<Value>::maximum(c);
      }
    }

    // simple_case:
    if (successor->color == BLACK) {
      if (c && c->color == RED) {
        c->color = BLACK;
        return successor;
      }
    } else {
    delete_case1:
      if (c != root()) return successor;

      // delete_case2:
      node_type s = sibling(c);
      if (s->color == RED) {
        c->parent->color = RED;
        s->color = BLACK;
        if (is_left_child(c))
          RB_tree_rotate_left(c->parent);
        else
          RB_tree_rotate_right(c->parent);
      }
      // delete_case3:
      s = sibling(c);
      if ((c->parent->color == BLACK) && (s->color == BLACK) &&
          (s->left == 0 || s->left->color == BLACK) &&
          (s->right == 0 || s->right->color == BLACK)) {
        s->color = RED;
        c = c->parent;
        goto delete_case1;
      }

      // delete_case4:
      s = sibling(c);
      if ((c->parent->color == RED) && (s->color == BLACK) &&
          (s->left == 0 || s->left->color == BLACK) &&
          (s->right == 0 || s->right->color == BLACK)) {
        s->color = RED;
        c->parent->color = BLACK;
        return c;
      }

      // delete_case5:
      s = sibling(c);
      if (s->color == BLACK) {  // this if statement is trivial,
        // due to case 2 (even though case 2 changed the sibling to a sibling's
        // child, the sibling's child can't be red, since no red parent can have
        // a red child).
        if (is_left_child(c) && (s->right == 0 || s->right->color == BLACK) &&
            (s->left->color ==
             RED)) {  // this last test is trivial too due to cases 2-4.
          s->color = RED;
          s->left->color = BLACK;
          RB_tree_rotate_right(s);
        } else if (is_right_child(c) &&
                   (s->left == 0 || s->left->color == BLACK) &&
                   (s->right->color == RED)) {  // this last test is trivial too
                                                // due to cases 2-4.
          s->color = RED;
          s->right->color = BLACK;
          RB_tree_rotate_left(s);
        }
      }

      // delete_case6:
      s = sibling(c);
      s->color = c->parent->color;
      c->parent->color = BLACK;
      if (is_left_child(c)) {
        if (s->right) s->right->color = BLACK;
        RB_tree_rotate_left(c->parent);
      } else {
        if (s->left) s->left->color = BLACK;
        RB_tree_rotate_right(c->parent);
      }
    }

    return successor;
  }
};

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Allocator>
bool operator==(const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
                const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &y) {
  return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Allocator>
bool operator<(const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
               const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &y) {
  return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Allocator>
bool operator!=(const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
                const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &y) {
  return !(x == y);
}

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Allocator>
bool operator>(const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
               const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &y) {
  return y < x;
}

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Allocator>
bool operator<=(const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
                const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &y) {
  return !(y < x);
}

template <typename Key, typename Value, typename KeyOfValue, typename Compare,
          typename Allocator>
bool operator>=(const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &x,
                const RB_tree<Key, Value, KeyOfValue, Compare, Allocator> &y) {
  return !(x < y);
}

};  // namespace ft

#endif