#include <map>

#include "enable_if.hpp"
#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "util.h"
#include "vector.hpp"

class hanbin {
 public:
  int a;

 public:
  friend bool operator==(const hanbin& x, const hanbin& y);
  friend bool operator<(const hanbin& x, const hanbin& y);
};

bool operator==(const hanbin& x,
                const hanbin& y) {
  return x.a == y.a;
}

bool operator!=(const hanbin& x,
                const hanbin& y) {
  return !(x == y);
}

bool operator<(const hanbin& x,
               const hanbin& y) {
  return x.a < y.a;
}

bool operator>(const hanbin& x,
               const hanbin& y) {
  return y < x;
}

bool operator<=(const hanbin& x,
                const hanbin& y) {
  return !(y < x);
}

bool operator>=(const hanbin& x,
                const hanbin& y) {
  return !(x < y);
}

int main() {
  std::map<hanbin, int> stdmap;
  ft::map<hanbin*, int> map;

  stdmap.insert(std::make_pair(hanbin(), 20));

  map.insert(ft::make_pair(new hanbin(), 20));
  map.insert(ft::make_pair(new hanbin(), 10));
  for (auto it = map.begin(); it != map.end(); ++it) {
    std::cout << (*it).second << std::endl;
  }
  ft::reverse_iterator b = map.rbegin();
  ft::reverse_iterator c(b.base());
}