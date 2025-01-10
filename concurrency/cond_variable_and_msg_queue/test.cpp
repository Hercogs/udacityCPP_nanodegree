#include <iostream>

int main() {
    int value = 42;

    // Define a lambda that captures `value` by copy and is mutable
    auto mutableLambda = [&value]() {
        value += 10; // Modify the captured variable
        std::cout << "Inside lambda, value: " << value << std::endl;
    };

    // Call the lambda
    mutableLambda();

    // The original value remains unchanged
    std::cout << "Outside lambda, value: " << value << std::endl;

    return 0;
}
