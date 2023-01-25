#include "vector.hpp"

int main() {
  std::allocator<int>         a = std::allocator<int>();

  typedef std::allocator<int> allocator_type;
  allocator_type              p = allocator_type();  
  return 0;
}