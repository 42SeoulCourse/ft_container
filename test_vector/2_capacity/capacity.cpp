#include <iostream>
#include <vector>

#include "../all.hpp"

int main() {
  // std size TEST
  std::cout << "<--------------std size TEST-------------->" << std::endl;
  std::cout << std::endl;

  std::vector<int> stdVector;
  std::cout << "stdVector size() : " << stdVector.size() << std::endl;
  std::cout << "stdVector max_size() : " << stdVector.max_size() << std::endl;
  std::cout << "stdVector capacity() : " << stdVector.capacity() << std::endl;
  std::cout << "stdVector contains:";
  for (int i = 0; i < stdVector.size(); i++)
    std::cout << ' ' << stdVector[i];
  std::cout << '\n';

  std::cout << std::endl;
  for (int i = 1; i < 10; i++) stdVector.push_back(i);
  std::cout << "10 elements push_back to stdVector size() : " << stdVector.size() << std::endl;
  std::cout << "stdVector max_size() : " << stdVector.max_size() << std::endl;
  std::cout << "stdVector capacity() : " << stdVector.capacity() << std::endl;
  std::cout << "stdVector contains:";
  for (int i = 0; i < stdVector.size(); i++)
    std::cout << ' ' << stdVector[i];
  std::cout << '\n';

  std::cout << std::endl;
  stdVector.resize(5);
  std::cout << "resize(5) stdVector size() : " << stdVector.size() << std::endl;
  std::cout << "stdVector max_size() : " << stdVector.max_size() << std::endl;
  std::cout << "stdVector capacity() : " << stdVector.capacity() << std::endl;
  std::cout << "stdVector contains:";
  for (int i = 0; i < stdVector.size(); i++)
    std::cout << ' ' << stdVector[i];
  std::cout << '\n';

  std::cout << std::endl;
  stdVector.resize(8, 100);
  std::cout << "resize(8, 100) stdVector size() : " << stdVector.size() << std::endl;
  std::cout << "stdVector max_size() : " << stdVector.max_size() << std::endl;
  std::cout << "stdVector capacity() : " << stdVector.capacity() << std::endl;
  std::cout << "stdVector contains:";
  for (int i = 0; i < stdVector.size(); i++)
    std::cout << ' ' << stdVector[i];
  std::cout << '\n';

  std::cout << std::endl;
  stdVector.resize(12);
  std::cout << "resize(12) stdVector size() : " << stdVector.size() << std::endl;
  std::cout << "stdVector max_size() : " << stdVector.max_size() << std::endl;
  std::cout << "stdVector capacity() : " << stdVector.capacity() << std::endl;
  std::cout << "stdVector contains:";
  for (int i = 0; i < stdVector.size(); i++)
    std::cout << ' ' << stdVector[i];
  std::cout << '\n';

  // ft size TEST
  std::cout << std::endl;
  std::cout << "<--------------ft size TEST-------------->" << std::endl;
  std::cout << std::endl;

  ft::vector<int> ftVector;
  std::cout << "ftVector size() : " << ftVector.size() << std::endl;
  std::cout << "ftVector max_size() : " << ftVector.max_size() << std::endl;
  std::cout << "ftVector capacity() : " << ftVector.capacity() << std::endl;
  std::cout << "ftVector contains:";
  for (int i = 0; i < ftVector.size(); i++)
    std::cout << ' ' << ftVector[i];
  std::cout << '\n';

  std::cout << std::endl;
  for (int i = 1; i < 10; i++) ftVector.push_back(i);
  std::cout << "10 elements push_back to ftVector size() : " << ftVector.size() << std::endl;
  std::cout << "ftVector max_size() : " << ftVector.max_size() << std::endl;
  std::cout << "ftVector capacity() : " << ftVector.capacity() << std::endl;
  std::cout << "ftVector contains:";
  for (int i = 0; i < ftVector.size(); i++)
    std::cout << ' ' << ftVector[i];
  std::cout << '\n';

  std::cout << std::endl;
  ftVector.resize(5);
  std::cout << "resize(5) ftVector size() : " << ftVector.size() << std::endl;
  std::cout << "ftVector max_size() : " << ftVector.max_size() << std::endl;
  std::cout << "ftVector capacity() : " << ftVector.capacity() << std::endl;
  std::cout << "ftVector contains:";
  for (int i = 0; i < ftVector.size(); i++)
    std::cout << ' ' << ftVector[i];
  std::cout << '\n';

  std::cout << std::endl;
  ftVector.resize(8, 100);
  std::cout << "resize(8, 100) ftVector size() : " << ftVector.size() << std::endl;
  std::cout << "ftVector max_size() : " << ftVector.max_size() << std::endl;
  std::cout << "ftVector capacity() : " << ftVector.capacity() << std::endl;
  std::cout << "ftVector contains:";
  for (int i = 0; i < ftVector.size(); i++)
    std::cout << ' ' << ftVector[i];
  std::cout << '\n';

  std::cout << std::endl;
  ftVector.resize(200);
  std::cout << "resize(200) ftVector size() : " << ftVector.size() << std::endl;
  std::cout << "ftVector max_size() : " << ftVector.max_size() << std::endl;
  std::cout << "ftVector capacity() : " << ftVector.capacity() << std::endl;
  std::cout << "ftVector contains:" ;
  for (int i = 0; i < ftVector.size(); i++)
    std::cout << ' ' << ftVector[i];
  std::cout << '\n';

  std::cout << "size changed: " << ftVector.size() << '\n';
  std::cout << "capacity changed: " << ftVector.capacity() << '\n';
  ftVector.resize(300);
  std::cout << "size changed: " << ftVector.size() << '\n';
  std::cout << "capacity changed: " << ftVector.capacity() << '\n';

  return 0;
}