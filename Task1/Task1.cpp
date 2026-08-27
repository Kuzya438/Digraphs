#include <iostream>
#include <cstdlib>
#include <fstream>

int** create_two_dim_array(int N) {
    int** ptrArray{ new int* [N] {} };
    for (int row{}; row < N; ++row) {
        ptrArray[row] = new int[N] {};
    }
    return ptrArray;
}

int main() {
    setlocale(LC_ALL, "RU");

    int N{};
    int** orgraph{ nullptr };

    std::ifstream data("input.txt");
    if (!data.is_open()) {
        std::cout << "Не удалось открыть файл input.txt" << std::endl;
        return 1;
    }

    data >> N;
    orgraph = create_two_dim_array(N);
    for (int i{}; i < N; ++i) {
        for (int j{}; j < N; ++j) {
            data >> orgraph[i][j];
        }
    }

    data.close();

    std::cout << "Текстовый вид орграфа:" << std::endl;
    for (int i{}; i < N; ++i) {
        bool hasArc{ false };

        std::cout << i + 1 << ": ";
        for (int j{}; j < N; ++j) {
            if (orgraph[i][j] == 1) {
                std::cout << j + 1 << " ";
                hasArc = true;
            }
        }
        if (!hasArc) { std::cout << "нет"; }

        std::cout << std::endl;
    }

    for (int i{}; i < N; ++i) {
        delete[] orgraph[i];
    }
    delete[] orgraph;
    orgraph = nullptr;

    return EXIT_SUCCESS;
}