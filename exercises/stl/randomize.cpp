#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <random>
#include "Complex.hpp" // assumes Complex has operator overloads

template<typename T>
void compute(int len, T initial, T step) {
    std::vector<T> v(len + 1), diffs(len + 1);

    // Fill with arithmetic sequence
    std::generate(v.begin(), v.end(), [n = 0, initial, step]() mutable {
        return initial + step * (n++);
    });

    // Shuffle the sequence
    std::shuffle(v.begin(), v.end(), std::default_random_engine{});

    // Compute adjacent differences
    std::adjacent_difference(v.begin(), v.end(), diffs.begin());

    // Compute sum and sum of squares
    T sum = std::accumulate(diffs.begin() + 1, diffs.end(), T{});
    T sumsq = std::accumulate(diffs.begin() + 1, diffs.end(), T{}, [](T acc, const T& x) {
        return acc + x * x;
    });

    T mean = sum / static_cast<double>(len);  // length is len, not len+1
    T variance = sumsq / static_cast<double>(len) - mean * mean;

    std::cout << "Range = [" << initial << ", " << step * len << "]\n"
              << "Mean = " << mean << '\n'
              << "Variance = " << variance << '\n';
}

int main() {
    compute(1000, 0.0, 7.0);               // for double
    compute(1000, Complex(0.0, 0.0), Complex(1.0, 1.0)); // for Complex
}
