#include <vector>
#include <memory>
#include <iostream>

// void test(std::allocator<int> alloc) {
//   int* p = alloc.allocate(10);
// }

int main() {
  // vector constructor test
  std::vector<int> v(10, 5);
  std::cout << v.size() << std::endl;
  std::cout << v.capacity() << std::endl;
  for (std::vector<int>::iterator it = v.begin() ; it != v.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << std::endl;

  // vector address & size & capacity max_size test
  std::vector<int> vector_int;
  std::cout << "vector_int address: " <<&vector_int << std::endl;
  std::cout << "vector_int size: " << vector_int.size() << std::endl;
  std::cout << "vector_int capacity: " <<vector_int.capacity() << std::endl;
  std::cout << "vector_int max_size: "<< vector_int.max_size() << std::endl;

  std::vector<long> vector_long;
  std::cout << "vector_long max_size: " << vector_long.max_size() << std::endl;

  // allocator test  
  int *p = vector_int.get_allocator().allocate(1);
  for (int i = 0; i < 10; i++)
    vector_int.get_allocator().construct(&p[i], i);
  
  std::cout << "The allocated array [p] contains:";
  for (int i = 0; i < 10; i++) std::cout << ' ' << p[i];
  std::cout << '\n';
  std::cout << "address of p[1]: " << &p[1] << std::endl;
  std::cout << "address of p[1]: " << vector_int.get_allocator().address(p[1]) << std::endl;

  // 오염 테스트
  int *p2 = vector_int.get_allocator().allocate(1);
  for (int i = 0; i < 10; i++)
    vector_int.get_allocator().construct(&p2[i], 15);

  std::cout << "The allocated array [p2] contains:";
  for (int i = 0; i < 10; i++) std::cout << ' ' << p2[i];
  std::cout << '\n';
  std::cout << "address of p2[1]: " << &p2[1] << std::endl;
  std::cout << "address of p2[1]: " << vector_int.get_allocator().address(p2[1]) << std::endl;
  
  std::cout << "The allocated array [p] contains:";
  for (int i = 0; i < 10; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  // leak test
  // test(vector_int.get_allocator());
  
  // system("leaks a.out");
  return 0;
}