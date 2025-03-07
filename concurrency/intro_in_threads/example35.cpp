#include <iostream>
#include <thread>
#include <memory>
class Vehicle
{
public:
    Vehicle() : _id(0) {}
    void addID(int id) { _id = id; }
    void printID()
    {
        std::cout << "Vehicle ID=" << _id << std::endl;
    }
    // TODO: Modify the Vehicle class as indicated in the instructions on the left.
    void setName(std::string name) { _name=name; }
    void printName() const{ 
        std::cout << "Name om vehicle: " << _name << std::endl;
    }
private:
    int _id;
    std::string _name;
};

int main()
{
    // create thread
    std::shared_ptr<Vehicle> v(new Vehicle);
    std::thread t = std::thread(&Vehicle::addID, v, 1); // call member function on object v
    
    // TODO: Modify the main to start setName as a thread.
    // Also, add code to main to print the name of the vehicle.
    // std::thread t1 = std::thread(&Vehicle::setName, &(*v), "Jēkabs");
    std::thread t1 = std::thread(&Vehicle::setName, v, "Jēkabs");
    
    
    // wait for thread to finish
    t.join();
    t1.join();
    
    // print Vehicle id
    v->printID();
    v->printName();
    
    return 0;
}