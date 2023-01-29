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
  for (int i; (&*first) + i != (&*last); i++) {
    std::cout << (&*first) + i << std::endl;
  }

  std::cout << std::endl;

  iter_type first0 = myvector.begin();
  iter_type last0 = myvector.end();
  for (; &*first != &*last; first++) {
    std::cout << (&*first) << std::endl;
  }

  std::cout << std::endl;

  iter_type first1 = myvector.begin();
  iter_type last1 = myvector.end();
  for (; (first1) != (last1); first1++) {
    std::cout << &*first1 << std::endl;
  }
  std::cout << std::endl;

  iter_type first2 = myvector.begin();
  iter_type last2 = myvector.end();
  iter_type practice = myvector.begin();
  practice += 2;

  size_t result = &*practice - &*first2;

  return 0;
}