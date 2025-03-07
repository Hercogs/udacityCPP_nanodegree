#include <iostream>
#include <random>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 

    std::unique_lock<std::mutex> lock(_mutex);
    _condition.wait(lock, [this](){return !_queue.empty();});

    T t = std::move(_queue.front());
    _queue.pop_front();
    return t;
}


template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push_back(std::move(msg));

    _condition.notify_one();

}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
    while(true)
    {
        if (_msg_queue.receive() == TrafficLightPhase::green) return;
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}


void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 

    using ms = std::chrono::milliseconds;

    ms current_time = std::chrono::duration_cast<ms>(
        std::chrono::system_clock::now().time_since_epoch());
    ms start_time = current_time;

    double timeout {0.0};

    std::default_random_engine generator(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> distribution(4, 6);

    while(true)
    {
        timeout = distribution(generator);

        while ((current_time - start_time) < ms(static_cast<int>(round(timeout*1000)))) {

            current_time = std::chrono::duration_cast<ms>(
                std::chrono::system_clock::now().time_since_epoch());

            std::this_thread::sleep_for(ms(1));
        }

        // Inverse traffic light
        switch (_currentPhase)
        {
            case TrafficLightPhase::green:
                _currentPhase = TrafficLightPhase::red;
                break;
            case TrafficLightPhase::red:
                _currentPhase = TrafficLightPhase::green;
                break;
            default:
                break;
        }
        _msg_queue.send(std::move(_currentPhase));

        // Reset clock
        start_time = current_time;
    }
}
