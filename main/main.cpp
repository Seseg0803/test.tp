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
    static constexpr double EPS = 1e-9; // Погрешность 
public:
   
     // @param n Размерность матрицы (N x N).
    
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

     // @param filename Путь к файлу.
    
    static Matrix loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл: " + filename);
        }

        size_t n;
        if (!(file >> n) || n == 0) {
            throw std::runtime_error("Некорректный размер матрицы в файле.");
        }

        Matrix mat(n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (!(file >> mat.data[i][j])) {
                    throw std::runtime_error("Ошибка считывания элементов матрицы.");
                }
            }
        }

        return mat;
    }

    
     //@brief Вычисление определителя методом Гаусса.
     // @return Значение определителя (double).
     
    double determinant() const {
        std::vector<std::vector<double>> a = data;
        double det = 1.0;

        for (size_t i = 0; i < size; ++i) {
            // Поиск опорного элемента (pivot) по столбцу 
            size_t pivot = i;
            for (size_t j = i + 1; j < size; ++j) {
                if (std::abs(a[j][i]) > std::abs(a[pivot][i])) {
                    pivot = j;
                }
            }

            // Если ведущий элемент равен 0, определитель равен 0
            if (std::abs(a[pivot][i]) < EPS) {
                return 0.0;
            }

            // Перестановка строк, если нужно (меняет знак определителя)
            if (i != pivot) {
                std::swap(a[i], a[pivot]);
                det = -det;
            }

            det *= a[i][i];

            // Прямой ход метода Гаусса
            for (size_t j = i + 1; j < size; ++j) {
                double factor = a[j][i] / a[i][i];
                for (size_t k = i + 1; k < size; ++k) {
                    a[j][k] -= factor * a[i][k];
                }
            }
        }

        return det;
    }
};

/**
 * @brief Модульные тесты проверки вычисления определителя.
 */
void runTests() {
    // Тест 1: Матрица 1x1
    Matrix m1({{5.0}});
    assert(std::abs(m1.determinant() - 5.0) < 1e-6);

    // Тест 2: Матрица 2x2
    Matrix m2({{3.0, 8.0}, {4.0, 6.0}});
    assert(std::abs(m2.determinant() - (-14.0)) < 1e-6);

    // Тест 3: Матрица 3x3
    Matrix m3({{6.0, 1.0, 1.0}, {4.0, -2.0, 5.0}, {2.0, 8.0, 7.0}});
    assert(std::abs(m3.determinant() - (-306.0)) < 1e-6);

    // Тест 4: Вырожденная матрица
    Matrix m4({{1.0, 2.0}, {2.0, 4.0}});
    assert(std::abs(m4.determinant()) < 1e-6);

    std::cout << "Все модульные тесты успешно пройдены.\n";
}

int main(int argc, char* argv[]) {
    // Запуск Unit-тестов перед выполнением программы
    runTests();

    std::string filename = "input.txt";
    if (argc > 1) {
        filename = argv[1];
    }

    try {
        Matrix matrix = Matrix::loadFromFile(filename);
        double det = matrix.determinant();

        std::cout << "Определитель матрицы: " << det << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
