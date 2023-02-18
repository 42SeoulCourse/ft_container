#include <iostream>
#include <iterator>

template <typename T>
class Base {
 public:
  typedef T   a;
  typedef std::string b;
};

template <typename T>
class Base2 {
 public:
  // 네임스페이스가 있으면 무조건 typename 이 필요
  typedef typename Base<T>::a d;  // 자료형 재정의
  typename Base<T>::b         e;  // 변수 선언

  // 없으면 상관 없음
  typedef T f;  // 자료형 재정의
  T         g;  // 변수 선언
};

int main() {
  Base2<std::string> test;

  Base2<std::string>::d what = "hello";
  test.e = "there!!";
  test.g = "I am jaekim";

  std::cout << what << " ";
  std::cout << test.e << std::endl;
  std::cout << test.g << std::endl;
}