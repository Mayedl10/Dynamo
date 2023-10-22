#include "dynamo.hpp"

int Random::randint(int x, int y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(x, y);
    return distribution(gen);
}

double Random::random() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0, 1);
    return distribution(gen);
}