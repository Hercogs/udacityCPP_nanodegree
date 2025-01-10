#include <iostream>
#include <thread>
#include <future>
#include <cmath>

void computeSqrt(std::promise<double> &&prms, double input)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // simulate work
    double output = sqrt(input);
    prms.set_value(output);
}

int main()
{
    // define input data
    double inputData = 42.0;

    // create promise and future
    std::promise<double> prms;
    std::future<double> ftr = prms.get_future();

    // start thread and pass promise as argument
    std::thread t(computeSqrt, std::move(prms), inputData);

    // Student task STARTS here
    // std::future_status status = ftr.wait_for(std::chrono::seconds(3));
    std::future_status status = ftr.wait_for(std::chrono::duration<int, std::milli>(3000));
    if(status == std::future_status::ready){
        double result = ftr.get();
        std::cout << "Result: " << result << std::endl;
    } else {
        std::cout << "Timeout" << std::endl;
    }


    // Student task ENDS here    

    // thread barrier
    t.join();

    return 0;
}
