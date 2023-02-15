#include <iostream>
#include <vector>

int main() {
  std::vector<int> myvector;

  myvector.push_back(78);
  myvector.pop_back();

  int &a = myvector.front();
  try {
    if (myvector.empty()) {
      throw std::out_of_range("vector::front()");
    }
    std::cout << "myvector.front() is now " << a << '\n';

  } catch (std::out_of_range &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}