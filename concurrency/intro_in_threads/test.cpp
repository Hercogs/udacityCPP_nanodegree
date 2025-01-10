#include <iostream>
#include <vector>
#include <numeric>

class DataProcessor {
public:
    DataProcessor(const std::vector<int>& data) : data(data), cachedSum(0), isCached(false) {}
    

    int getSum() const {
        // Check if the sum is cached
        if (!isCached) {
            // Compute the sum and cache it
            cachedSum = std::accumulate(data.begin(), data.end(), 0);
            isCached = true;
        }
        return cachedSum;
    }

private:
    std::vector<int> data;
    mutable int cachedSum;       // mutable allows modification in a const method
    mutable bool isCached;       // mutable allows modification in a const method
};

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    DataProcessor processor(numbers);

    std::cout << "Sum: " << processor.getSum() << std::endl; // Computes and caches the sum
    std::cout << "Sum: " << processor.getSum() << std::endl; // Uses the cached sum

    return 0;
}
