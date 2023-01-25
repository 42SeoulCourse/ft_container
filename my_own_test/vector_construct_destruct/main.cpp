#include "vector.hpp"

int main() {
  ft::vector<int> v1;
  ft::vector<int> v2(v1);
  ft::vector<int> v3;
  v3 = v2;
  return 0;
}