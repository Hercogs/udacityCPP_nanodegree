#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

void modifyValue(int& value) {
    value = 10;
}

void modifyValue1(int& value) {
    value = 10;
}

int main1() {
    int number = 5;

    try {
        std::vector<int> vec(5);
        int value = vec.at(10);
    } catch (const std::exception &e){
        std::cout << "Ex: " << e.what() << std::endl;
    } catch(...) {
        std::cout << "Other" << std::endl;
    }


    modifyValue1(std::ref(number));
    // std::thread t(modifyValue, std::ref(number);
    // t.join();
    std::cout << "Number: " << number << std::endl; // Output: 10
    return 0;
}

int main(){
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7};



    for (int val : vec) { std::cout << val << " "; }
    printf("\n");

    auto it = vec.begin();
    vec.erase(it+2);

    for (int val : vec) { std::cout << val << " "; }
    printf("\n");

    it++;
    vec.erase(it);

    for (int val : vec) { std::cout << val << " "; }
    printf("\n");

    return 0;
}

