// vector::reserve
#include <iostream>
#include <vector>

int main() {
  std::vector<int>::size_type capa;
  //   std::vector<int> bar(400); 은 capacity 400, size 400, 0 으로 초기화
  
  // reserve 전 후 주소 검사
  std::vector<int> bar(100, 1);
  int*             before_reserve = &*bar.begin();
  std::cout << "bar.begin() 주소:" << before_reserve << std::endl;
  
  //   reserve 로 capacity 할당
  bar.reserve(200);
  int*             after_reserve = &*bar.begin();
  std::cout << "bar.begin() 주소: " << &*bar.begin() << std::endl;
  std::cout << "after - before: " << &*after_reserve - &*before_reserve << std::endl;
  std::cout << "before - after: " << &*before_reserve - &*after_reserve << std::endl;
  capa = bar.capacity();
  std::cout << "capa : " << capa << std::endl;
  
  // for (auto i = 0; i < bar.size(); i++) {
  //   std::cout << "bar[" << i << "] = " << bar[i] << std::endl;
  // }
  //   reserve 는 에러를 던지지 않는다.
  // try {
  //   bar.reserve(200);
  // } catch (...) {
  //   std::cout << "error" << std::endl;
  // }
  // std::cout << "capacity : " << bar.capacity() << std::endl;
  // std::cout << "making bar grow:\n";
  // for (int i = 0; i < 80; i++) {
  //   bar.push_back(i);
  //   if (capa != bar.capacity()) {
  //     capa = bar.capacity();
  //     std::cout << "capacity changed: " << capa << '\n';
  //     std::cout << "capacity changed: " << bar.max_size() << '\n';
  //   }
  // }
  for (std::vector<int>::iterator it = bar.begin(); it != bar.end(); it++)
    std::cout << " " << *it;
  std::cout << '\n';
  std::cout << "size changed: " << bar.size() << '\n';
  std::cout << "capacity changed: " << bar.capacity() << '\n';

  return 0;
}