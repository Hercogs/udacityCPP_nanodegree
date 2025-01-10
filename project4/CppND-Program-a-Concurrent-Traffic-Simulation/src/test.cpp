#include <iostream>
#include <thread>
#include <chrono>


class Test
{
    public:
        Test(){
            t = std::thread(&Test::func, this, 10);
        };
        ~Test()
        {
            printf("Deconstructor!\n");
            t.join();
        };
        void func(int i)
        {
            while(true)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                printf("OK: %d\n", i);
            }
        };

        std::thread t;


};



int main()
{

    Test t;

    while(true)
    {
       std::this_thread::sleep_for(std::chrono::seconds(1)) ;
    }


    return 0;

}


