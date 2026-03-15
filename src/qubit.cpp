#include "qubit.h"
#include <cmath>
#include <random>

void qubit::normalize() {
    double norm = std::sqrt(std::norm(alpha) + std::norm(beta));
    if (norm > 0) {
        alpha /= norm;
        beta /= norm;
    }
}

qubit::qubit(std::complex<double> alpha, std::complex<double> beta) : alpha(alpha), beta(beta) {
    normalize();
}

int qubit::measure()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dist(0.0, 1.0);

    double p0 = std::norm(alpha);

    double r = dist(gen);

    if(r < p0)
    {
        *this= qubit(1.0, 0.0);
        return 0;
    }
    else
    {
        *this = qubit(0.0, 1.0);
        return 1;
    }
}
