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

  std::reverse_iterator<iter_type> _end(myvector.rend());
  std::reverse_iterator<iter_type> _begin(myvector.rbegin());
  typedef std::reverse_iterator<iter_type> rev;

  std::cout << "vector display using rev_iter with copy: ";
  std::cout << std::endl;
  for (rev itr = _begin; itr != _end; itr++) {
    std::cout << *itr;
  }
  std::cout << std::endl;

  std::cout << "vector display using base iter in rev_iter: ";
  std::cout << std::endl;
  for (iter_type itr = _end.base(); itr != _begin.base(); itr++) {
    std::cout << *itr;
  }
  std::cout << std::endl;

  std::reverse_iterator<iter_type> rev_begin = myvector.rbegin();
  std::cout << "vector display using rev_iter with assignment: ";
  std::cout << std::endl;
  for (std::reverse_iterator<iter_type> itr = rev_begin; itr != myvector.rend(); itr++) {
    std::cout << *itr;
  }

  std::cout << std::endl;
  return 0;
}