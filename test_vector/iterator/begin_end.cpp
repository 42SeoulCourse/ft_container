#include <iostream>
#include <vector>

#include "../all.hpp"

int main() {
  ft::vector<int>           a;
  ft::vector<int>::iterator it;

  

// ft::vector begin&end test
  std::cout << "<------------ft::vector TEST------------>" << std::endl;
  for (size_t i = 0; i < 5; i++) {
    a.push_back(i);
  }

  it = a.begin();
  for (int i = 0; it != a.end(); it++, i++) {
    std::cout << "ft::" << i << "번째 : " << *it << std::endl;
  }

  // ft::vector rbegin&rend test
  std::cout << std::endl;
  std::cout << "reverse" << std::endl;
  std::cout << std::endl;
  ft::vector<int>::reverse_iterator rit;
  rit = a.rbegin();
  for (int i = 4; rit != a.rend(); rit++, i--) {
    std::cout << "ft::" << i << "번째 : " << *rit << std::endl;
  }
  std::cout << std::endl;


// std::vector begin&end test
  std::cout << "<------------std::vector TEST------------>" << std::endl;
  std::vector<int>           b;
  std::vector<int>::iterator it2;
  
  for (size_t i = 0; i < 5; i++) {
    b.push_back(i);
  }

  it2 = b.begin();
  for (int i = 0; it2 != b.end(); it2++, i++) {
    std::cout << "std::" << i << "번째 : " << *it2 << std::endl;
  }

  // std::vector rbegin&rend test
  std::cout << std::endl;
  std::cout << "reverse" << std::endl;
  std::cout << std::endl;
  std::vector<int>::reverse_iterator rit2;
  rit2 = b.rbegin();
  for (int i = 4; rit2 != b.rend(); rit2++, i--) {
    std::cout << "ft::" << i << "번째 : " << *rit2 << std::endl;
  }

  return (0);
}
