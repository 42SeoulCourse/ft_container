// #include <iostream>
// #include <vector>

// int main ()
// {
//   std::vector<int>::size_type sz;

//   std::vector<int> foo;
//   sz = foo.capacity();
//   std::cout << "making foo grow:\n";
//   for (int i=0; i<100; ++i) {
//     foo.push_back(i);
//     if (sz!=foo.capacity()) {
//       sz = foo.capacity();
//       std::cout << "capacity changed: " << sz << '\n';
//     }
//   }

//   std::vector<int> bar;
//   sz = bar.capacity();
//   bar.reserve(100);   // this is the only difference with foo above
//   std::cout << "making bar grow:\n";
//   for (int i=0; i<100; ++i) {
//     bar.push_back(i);
//     if (sz!=bar.capacity()) {
//       sz = bar.capacity();
//       std::cout << "capacity changed: " << sz << '\n';
//     }
//   }
//   return 0;
// }

#include <iostream>
#include <vector>

#include "../all.hpp"

int main() {
  ft::vector<int>::size_type sz;

  ft::vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i = 0; i < 100; ++i) {
    foo.push_back(i);
    std::cout << i << std::endl;
    if (sz != foo.capacity()) {
      sz = foo.capacity();
      std::cout << std::endl;
      std::cout << "size changed: " << foo.size() << '\n';
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
  std::cout << "*************************" << '\n';
  std::cout << "size changed: " << foo.size() << '\n';
  std::cout << "capacity changed: " << foo.capacity() << '\n';
  foo.resize(200);
  std::cout << "size changed: " << foo.size() << '\n';
  std::cout << "capacity changed: " << foo.capacity() << '\n';

  std::cout << std::endl;

  std::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);
  std::cout << "making bar grow:\n";
  for (int i = 0; i < 100; ++i) {
    std::cout << i << std::endl;
    bar.push_back(i);
    if (sz != bar.capacity()) {
      sz = bar.capacity();
      std::cout << std::endl;
      std::cout << "size changed: " << bar.size() << '\n';
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
  std::cout << "size changed: " << bar.size() << '\n';
  std::cout << "capacity changed: " << bar.capacity() << '\n';
  bar.resize(200);
  std::cout << "size changed: " << bar.size() << '\n';
  std::cout << "capacity changed: " << bar.capacity() << '\n';

  std::cout << std::endl;
  std::vector<int> ftVector;
  ftVector.resize(100);
  std::cout << "resize(100) ftVector size() : " << ftVector.size() << std::endl;
  std::cout << "ftVector max_size() : " << ftVector.max_size() << std::endl;
  std::cout << "ftVector capacity() : " << ftVector.capacity() << std::endl;
  std::cout << "ftVector contains:";
  for (int i = 0; i < ftVector.size(); i++)
    std::cout << ' ' << ftVector[i];
  std::cout << '\n';

  for (int i = 0; i < 100; ++i) {
    std::cout << i << std::endl;
    ftVector.push_back(i);
    if (sz != ftVector.capacity()) {
      sz = ftVector.capacity();
      std::cout << std::endl;
      std::cout << "size changed: " << ftVector.size() << '\n';
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
  for (int i = 0; i < ftVector.size(); i++)
    std::cout << ' ' << ftVector[i];
  std::cout << '\n';
  std::cout << "size changed: " << ftVector.size() << '\n';
  std::cout << "capacity changed: " << ftVector.capacity() << '\n';
  return 0;
}