#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Finished work in thread!\n";
}

void threadFunction1(int i)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Finished work in thread:!" << i << "\n";
}

int main()
{
    // create thread
    std::thread t(threadFunction1, 5);

    // do somethig in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work in main!\n";

    // wait for thread to finish
    t.join();

    return 0;
}