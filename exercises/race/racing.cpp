
#include <iostream>
#include <thread>
#include <vector>

/*
 * This program tries to increment an integer `nInc` times in `nThread` threads.
 * If the result comes out at `nInc*nThread`, it stays silent, but it will print
 * an error if a race condition is detected.
 * If you don't see it racing, try ./run ./racing, which keeps invoking the
 * executable until a race condition is detected.
 */

constexpr std::size_t nThread = 10;
constexpr std::size_t nInc = 1000;
constexpr std::size_t nRepeat = 1000;

int main() {
  int nError = 0;

  for (std::size_t j = 0; j < nRepeat; j++) {
    int a = 0;

    // Increment the variable a 100 times:
    auto increment = [&a](){
      for (std::size_t i = 0; i < nInc; ++i) {
        a++;
      }
    };

    // Start up all threads
    std::vector<std::thread> threads;
    for (std::size_t i = 0; i < nThread; ++i) threads.emplace_back(increment);
    for (auto & thread : threads) thread.join();

    // Check
    if (a != nThread * nInc) {
      std::cerr << "Race detected! Result: " << a << '\n';
      nError++;
    }
  }

  return nError;
}
