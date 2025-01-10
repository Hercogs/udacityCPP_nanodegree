#include <iostream>
#include <thread>

void threadFunctionEven()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
    std::cout << "Even thread\n";
}

/* Student Task START */
void threadFunctionOdd()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work
    std::cout << "Odd thread\n";
}
/* Student Task END */

int main()
{
    /* Student Task START */
    for (size_t i=0; i < 6; i++)
    {
        printf("i: %ld --->", i);
        if (i % 2 == 1){
            printf("odd\n");
            std::thread t(threadFunctionOdd);
            t.detach();
        } else {
            printf("even\n");
            std::thread t(threadFunctionEven);
            t.detach();
        }

    }


    /* Student Task END */

    // ensure that main does not return before the threads are finished
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate work

    std::cout << "End of main is reached" << std::endl;
    return 0;
}
