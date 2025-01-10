#include <iostream>

// using namespace std;
using std::cout;

int main()
{
    int* p = nullptr;

    int x = 3;
    int &y = x;

    p = &y;


    cout << "Pointer: " << &x << " " << &y << " " << *p << '\n';

    return 0;
}