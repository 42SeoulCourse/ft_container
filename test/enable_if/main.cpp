#include <iostream>

#include "enable_if.hpp"

// class C {
//  public:
//   typedef double value;
// };

// class B {
//  public:
//   const static int value = 10;
// };

class A {
 public:
  A(int num) { std::cout << "integer overload" << std::endl; };

  //	template <typename T>
  //	A(T t) { std::cout << "template overload" << std::endl; };

  template <typename T>
  A(T t, typename ft::enable_if<ft::is_integral<T>::value, T>::type* = 0) {
    std::cout << "template overload" << std::endl;
  };
};

int main() {
  float num = 10;
  A     a = A(num);
  // C::value     i;
  // int          j = B::value;

  return 0;
}
