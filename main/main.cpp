#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <cassert>

 // @class Matrix
 // @brief Класс для работы с квадратной матрицей и вычисления ее определителя.
class Matrix {
private:
    size_t size;
    std::vector<std::vector<double>> data;
    static constexpr double EPS = 1e-9;

public:
    explicit Matrix(size_t n) : size(n), data(n, std::vector<double>(n, 0.0)) {}

    explicit Matrix(const std::vector<std::vector<double>>& grid) {
        size = grid.size();
        for (const auto& row : grid) {
            if (row.size() != size) {
                throw std::invalid_argument("Матрица должна быть квадратной.");
            }
        }
        data = grid;
    }
};

int main() {
    return 0;
}
