#include <iostream>  // std::cout
#include <iterator>  // std::reverse_iterator
#include <vector>    // std::vector

int main() {
  std::vector<int> myvector;
  for (int i = 0; i < 10; i++) myvector.push_back(i);

  typedef std::vector<int>::iterator iter_type;
  std::cout << "vector: " << std::endl;
  for (iter_type itr = myvector.begin(); itr != myvector.end(); itr++) {
    std::cout << *itr;
  }
  std::cout << std::endl;
  iter_type first = myvector.begin();
  iter_type last = myvector.end();
  // for (; &*first != &*last; first++) 둘 다 됨
  for (; first != last; first++) {
    std::cout << *first;
  }
  std::cout << std::endl;
  return 0;
}