#include "Pr.h"
#include <chrono>

using namespace std;

int main()
{
    Pr p;

    auto start_bw = std::chrono::steady_clock::now();

    p.calculate_sad();
    int r = p.find_min_sad();

    auto end_bw = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds_bw = end_bw-start_bw;
    std::cout << "elapsed time: " << elapsed_seconds_bw.count() << "s\n\n";

    cout << "Most similar region: " << r;

    return 0;
}
