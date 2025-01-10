#include <iostream>

using namespace std;

// This class for managing a template-based heap ressource implements move semantics
template <class T>
class MyClass
{
    T *data = nullptr;

public:
    MyClass() {
        std::cout << "Regular constructor" << std::endl;
    }

    // move constructor
    MyClass(MyClass &&other)
    {
        std::cout << "Move constructor" << std::endl;
        data = other.data;
        other.data = nullptr;
    }

    // move assignment operator
    MyClass &operator=(MyClass &&other)
    {
        std::cout << "Move assignment" << std::endl;
        if (this != &other)
        {
            if (data)
            {
                delete data;
            }
            data = other.data;
            other.data = nullptr;
        }

        return *this;
    }

    // copy constructor
    MyClass(const MyClass &) = delete;

    // copy assignment operator
    MyClass &operator=(const MyClass &) = delete;

    ~MyClass()
    {
        if (data)
        {
            delete data;
        }
    }
};

int main()
{
    /* EXERCISE 3-1: create an instance h1 of class MyClass with data of type 'double' using the regular constructor */
    // TODO: SOLUTION 3-1
    MyClass<float> h1 = MyClass<float>(); 
    
    // /* EXERCISE 3-2: create an instance h2 of class MyClass using the move constructor (moving from h1) */
    // TODO: SOLUTION 3-2
    MyClass<float> h2 = std::move(h1); 

    /* EXERCISE 3-3: disable copying for class MyClass */
    // TODO: SOLUTION 3-3
    // set visibility of MyClass(const MyClass &) and of MyClass &operator=(const MyClass &) to private
}