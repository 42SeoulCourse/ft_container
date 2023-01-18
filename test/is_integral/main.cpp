#include "vector.hpp"

int main() {
  std::cout << ft::is_integral<int>::value << std::endl;
  std::cout << ft::is_integral<int>::value << std::endl;
  std::cout << ft::is_integral<float>::value << std::endl;
  std::cout << ft::is_integral<bool>::value << std::endl;
  std::cout << ft::is_integral<char>::value << std::endl;
  std::cout << ft::is_integral<signed char>::value << std::endl;
  std::cout << ft::is_integral<unsigned char>::value << std::endl;
  std::cout << ft::is_integral<wchar_t>::value << std::endl;
  std::cout << ft::is_integral<short>::value << std::endl;
  std::cout << ft::is_integral<unsigned short>::value << std::endl;
  std::cout << ft::is_integral<int>::value << std::endl;
  std::cout << ft::is_integral<unsigned int>::value << std::endl;
  std::cout << ft::is_integral<long>::value << std::endl;
  std::cout << ft::is_integral<unsigned long>::value << std::endl;
  std::cout << ft::is_integral<long long>::value << std::endl;
  std::cout << ft::is_integral<unsigned long long>::value << std::endl;
  return 0;
}