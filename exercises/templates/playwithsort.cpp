#include "OrderedVector.hpp"
#include "Complex.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <functional>
#include <cstdlib>

struct ReverseStringLess {
    bool operator() (const std::string &s, const std::string &t) const {
        // TODO: compare reversed strings
        // hint: you can use:
        // - std::views::reverse
        // - std::ranges::lexicographical_compare
        // or, if your compiler does not support those yet,
        // take copies of the strings and reverse them using std::reverse
        return s < t;
    }
};
struct CompareLastBukva {
    bool operator()(const std::string& a, const std::string& b) const {
        if (a.empty() || b.empty()) return a < b;
        return a.back() < b.back();
    }
};
struct CompareWithManhatan {
    bool operator()(const Complex_t<float>& a, const Complex_t<float>& b) const {
        float d_a = std::abs(a.real())+std::abs(a.imaginary()), d_b = std::abs(b.real())+std::abs(b.imaginary());
        return d_a < d_b;
    }
};


int main() {
    std::cout << "Integer\n";
    OrderedVector<int> v(10);
    for (int i = 10; i > 0; i--)
        v.add(i);
    for (int i = 0; i < 10; i++)
        std::cout << v[i] << " ";
    std::cout << "\n\n";

    std::cout << "String\n";
    OrderedVector<std::string,std::greater<>> vs(5);
    vs.add(std::string("one"));
    vs.add(std::string("two"));
    vs.add(std::string("three"));
    vs.add(std::string("four"));
    vs.add(std::string("five"));
    for (int i = 0; i < 5; i++)
        std::cout << vs[i] << " ";
    std::cout << "\n\n";
    // TODO: Demonstrate OrderedVector with Complex as element type similar to above
    // Сделал
    std::cout << "Complex\n";
    OrderedVector<Complex_t<float>> com(5);
    com.add(Complex_t<float>(1.f,1.f));
    com.add(Complex_t<float>(-1.f,0.f));
    com.add(Complex_t<float>(2.f,-1.f));
    com.add(Complex_t<float>(0.1,-0.2));
    com.add(Complex_t<float>(0.3,0.9));
    for (int i = 0; i < 5; i++)
        std::cout << com[i] << " ";
    std::cout<<"\n\n";

    // TODO: Extend OrderedVector to allow to customize the ordering via an additional template paramter.
    //       Then, demonstrate the new functionality by ordering an OrderedVector<std::string>,
    //       where the strings are compared starting at their last letters.
    std::cout << "String last bukva\n";
    OrderedVector<std::string,CompareLastBukva> vs2(5);
    vs2.add(std::string("onef"));
    vs2.add(std::string("twob"));
    vs2.add(std::string("threec"));
    vs2.add(std::string("fourd"));
    vs2.add(std::string("fivea"));
    for (int i = 0; i < 5; i++)
        std::cout << vs2[i] << " ";
    std::cout << "\n\n";


    // TODO: Order an OrderedVector of Complex based on the Manhattan distance
    std::cout << "Complex Manhatan\n";
    OrderedVector<Complex_t<float>, CompareWithManhatan> comm(5);
    comm.add(Complex_t<float>(1.f,1.f));
    comm.add(Complex_t<float>(-1.f,0.f));
    comm.add(Complex_t<float>(2.f,-1.f));
    comm.add(Complex_t<float>(0.1,-0.2));
    comm.add(Complex_t<float>(0.3,0.9));
    for (int i = 0; i < 5; i++)
        std::cout << comm[i] << " ";
    std::cout<<"\n\n";

}
