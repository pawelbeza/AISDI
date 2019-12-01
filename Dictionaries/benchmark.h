#include <iostream>
#include <chrono>

/*!
 *  Tool for benchmarking dictionary
 *
 *  Examples of usage:
 *
 *  {
 *    Benchmark<std::chrono::nanoseconds> b;
 *    // code to examine
 *    size_t elapsed = b.elapsed();
 *  }
 *
 *  OR
 *
 *  {
 *    Benchmark<std::chrono::milliseconds> b(true);
 *    // code to examine
 *  } // object will display execution time of code on stderr
 */
template<typename D = std::chrono::microseconds>
class Benchmark {
public:
    Benchmark(bool printOnExit = false) : m_print(printOnExit) {
        start = std::chrono::high_resolution_clock::now();
    }
    typename D::rep elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        auto result = std::chrono::duration_cast<D>(end-start);
        return result.count();
    }
    ~Benchmark() {
        auto result = elapsed();
        if (m_print)
        {
            std::cerr << "Time: " << result << "\n";
        }
    }
private:
    std::chrono::high_resolution_clock::time_point start;
    bool m_print = false;
};