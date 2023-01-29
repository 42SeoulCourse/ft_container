#include <iostream>
#include <vector>

int main()
{
    //  빈 벡터 size 와 capa 비교
    std::vector<int> myvector;
    size_t size =myvector.size();
    size_t capacity = myvector.capacity();

    try
    {
        if (size == capacity)
        {
            throw std::out_of_range("size == capacity");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    //  빈 벡터 end 와 end_capa 비교
    std::vector<int> myvector1;
    std::vector<int>::iterator end =myvector1.end();
    std::vector<int>::iterator end_capa = myvector1.begin() + myvector1.capacity();

    try
    {
        if (end == end_capa)
        {
            throw std::out_of_range("end == capacity");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // std::vector<int> myvector(3, 100);
    // std::vector<int>::iterator it;

    // it = myvector.begin();
    // it = myvector.insert(it, 200);

    // myvector.insert(it, 2, 300);

    // it = myvector.begin();

    // std::vector<int> anothervector(2, 400);
    // myvector.insert(it, anothervector.begin(), anothervector.end());

    // int newarray[] = {500, 600, 700};
    // myvector.insert(myvector.begin(), newarray, newarray + 2);

    // std::cout << "myvector contains:";
    // for (it=myvector.begin(); it != myvector.end(); it++)
    //     std::cout << ' ' << *it;
    // std::cout << '\n';
}