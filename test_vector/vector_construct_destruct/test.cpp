#include <iostream>

class test
{
    private:
    public:
        test(void);
        test(const test& src);
        virtual ~test(void);
        test& operator=(test const& rhs);
};

test::test(void)
{ 
    std::cout << "test created. Default." << std::endl; 
}

test::test(const test & src)
{ 
    std::cout << "Copy constructor called. " << std::endl; 
     *this = src; 
}

test::~test(void)
{ 
    std::cout << "test destroyed." << std::endl; 
}

test & test::operator=(const test & rhs)
{
    std::cout << "Assignation operator called" << std::endl;
    if (this != &rhs)
    {
    }
    return *this;
}

int main () {
    test t1;
    test t2(t1);
    std::cout << "??" << std::endl;
    test t3;
    t3 = t2;
    return 0;
}