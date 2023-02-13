#ifndef MAP_HPP
#define MAP_HPP

#include "red_black_tree.hpp"
#include "utils.hpp"

namespace ft {

template <typename Pair>
struct Select1st : public std::unary_function<Pair, typename Pair::first_type> {
  typename Pair::first_type       &operator()(Pair &x) const { return x.first; }
  const typename Pair::first_type &operator()(const Pair &x) const {
    return x.first;
  }
};

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<std::pair<const Key, T> > >
class map {
 public:
  typedef Key                                    key_type;
  typedef T                                      mapped_type;
  typedef std::pair<const key_type, mapped_type> value_type;
  typedef Compare                                key_compare;
  typedef Alloc                                  allocator_type;

  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    friend class map;

   protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

   public:
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

 private:
  typedef RB_tree<key_type, value_type, Select1st<value_type>, Compare, Alloc>
             _Tree_type;
  _Tree_type _tree;

 public:
  typedef typename _Tree_type::pointer         pointer;
  typedef typename _Tree_type::const_pointer   const_pointer;
  typedef typename _Tree_type::reference       reference;
  typedef typename _Tree_type::const_reference const_reference;

  typedef typename _Tree_type::iterator               iterator;
  typedef typename _Tree_type::const_iterator         const_iterator;
  typedef typename _Tree_type::reverse_iterator       reverse_iterator;
  typedef typename _Tree_type::const_reverse_iterator const_reverse_iterator;

  typedef typename _Tree_type::size_type       size_type;
  typedef typename _Tree_type::difference_type difference_type;

  /* constructor */
  // RB_tree 에서 Compare, Alloc 을 받는 생성자를 만듬. key_type과 value_type,
  // Select1st 는 map 에서 정의된다.
  map() : _tree(Compare(), allocator_type()) {}
  explicit map(const Compare        &comp,
               const allocator_type &alloc = allocator_type())
      : _tree(comp, alloc) {}

  template <typename InputIterator>
  map(InputIterator first, InputIterator last, const Compare &comp,
      const allocator_type &alloc = allocator_type())
      : _tree(comp, alloc) {
    _tree.insert_unique(first, last);
  }

  map(const map &x) : _tree(x._tree) {}

  /* assignment operator */
  map &operator=(const map &x) {
    _tree = x._tree;
    return *this;
  }

  /* destructor */
  ~map() {}

  /* iterators */
  iterator               begin() { return _tree.begin(); }
  const_iterator         begin() const { return _tree.begin(); }
  iterator               end() { return _tree.end(); }
  const_iterator         end() const { return _tree.end(); }
  reverse_iterator       rbegin() { return _tree.rbegin(); }
  const_reverse_iterator rbegin() const { return _tree.rbegin(); }
  reverse_iterator       rend() { return _tree.rend(); }
  const_reverse_iterator rend() const { return _tree.rend(); }

  /* capacity */
  bool      empty() const { return _tree.empty(); }
  size_type size() const { return _tree.size(); }
  size_type max_size() const { return _tree.max_size(); }

  /* element access */
  mapped_type &operator[](const key_type &k) {
    iterator i = lower_bound(k);
    if (i == end() || key_comp()(k, (*i).first))
      i = insert(i, value_type(k, mapped_type()));
    return (*i).second;
  }

  /* modifiers */
  pair<iterator, bool> insert(const value_type &x) {
    return _tree.insert_unique(x);
  }
  iterator insert(iterator position, const value_type &x) {
    return _tree.insert_unique(position, x);
  }
  template <typename InputIterator>
  void insert(InputIterator first, InputIterator last) {
    _tree.insert_unique(first, last);
  }

  void      erase(iterator position) { _tree.erase(position); }
  size_type erase(const key_type &x) { return _tree.erase(x); }
  void      erase(iterator first, iterator last) { _tree.erase(first, last); }
  void      clear() { _tree.clear(); }
  void      swap(map &x) { _tree.swap(x._tree); }

  /* observers */
  allocator_type get_allocator() const { return _tree.get_allocator(); }
  key_compare    key_comp() const { return _tree.key_comp(); }
  value_compare  value_comp() const { return value_compare(_tree.key_comp()); }

  /* lookup */
  iterator       find(const key_type &x) { return _tree.find(x); }
  const_iterator find(const key_type &x) const { return _tree.find(x); }
  size_type      count(const key_type &x) const { return _tree.count(x); }
  iterator       lower_bound(const key_type &x) { return _tree.lower_bound(x); }
  const_iterator lower_bound(const key_type &x) const {
    return _tree.lower_bound(x);
  }
  iterator       upper_bound(const key_type &x) { return _tree.upper_bound(x); }
  const_iterator upper_bound(const key_type &x) const {
    return _tree.upper_bound(x);
  }
  pair<iterator, iterator> equal_range(const key_type &x) {
    return _tree.equal_range(x);
  }
  pair<const_iterator, const_iterator> equal_range(const key_type &x) const {
    return _tree.equal_range(x);
  }
};

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator==(const map<Key, T, Compare, Alloc> &x,
                const map<Key, T, Compare, Alloc> &y) {
  return (x == y);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator!=(const map<Key, T, Compare, Alloc> &x,
                const map<Key, T, Compare, Alloc> &y) {
  return !(x == y);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<(const map<Key, T, Compare, Alloc> &x,
               const map<Key, T, Compare, Alloc> &y) {
  return (x < y);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator<=(const map<Key, T, Compare, Alloc> &x,
                const map<Key, T, Compare, Alloc> &y) {
  return !(y < x);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>(const map<Key, T, Compare, Alloc> &x,
               const map<Key, T, Compare, Alloc> &y) {
  return (y < x);
}

template <typename Key, typename T, typename Compare, typename Alloc>
bool operator>=(const map<Key, T, Compare, Alloc> &x,
                const map<Key, T, Compare, Alloc> &y) {
  return !(x < y);
}

template <typename Key, typename T, typename Compare, typename Alloc>
void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
  x.swap(y);
}

}  // namespace ft

#endif