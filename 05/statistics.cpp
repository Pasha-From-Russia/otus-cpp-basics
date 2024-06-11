#include <iostream>
#include <limits>
#include <vector>

#include "statistics.hpp"

int main() {

    std::vector<IStatistics *> statistics;
    statistics.push_back(new Min{});
    statistics.push_back(new Max{});
    statistics.push_back(new Avg{});
    statistics.push_back(new StDev{});

    double val = 0;
    while (std::cin >> val) {
        for (auto & st : statistics) {
            st->update(val);
        }
    }

    // Handle invalid input data
    if (!std::cin.eof() && !std::cin.good()) {
        std::cerr << "Invalid input data\n";
        return 1;
    }

    // Print results if any
    for (const auto & st : statistics) {
        std::cout << st->name() << " = " << st->eval() << std::endl;
    }

    // Clear memory - delete all objects created by new
    for (auto & st : statistics) {
        delete st;
    }

    return 0;
}