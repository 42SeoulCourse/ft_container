#include <iostream>
#include <vector>

int main()
{
    std::vector<int> myvector(3, 100);
    std::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert(it, 200);

    myvector.insert(it, 2, 300);

    it = myvector.begin();

    std::vector<int> anothervector(2, 400);
    myvector.insert(it, anothervector.begin(), anothervector.end());

    int newarray[] = {500, 600, 700};
    myvector.insert(myvector.begin(), newarray, newarray + 2);

    std::cout << "myvector contains:";
    for (it=myvector.begin(); it != myvector.end(); it++)
        std::cout << ' ' << *it;
    std::cout << '\n';
}