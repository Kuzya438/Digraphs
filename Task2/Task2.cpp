#include <iostream>
#include <deque>
#include <cstdlib>
#include <fstream>

int** create_two_dim_array(int N) {
    int** ptrArray{ new int* [N] {} };
    for (int row{}; row < N; ++row) {
        ptrArray[row] = new int[N] {};
    }
    return ptrArray;
}

void dfs(int** graph, int N, int* visited, std::deque<int>& order, int vertex = 0) {
    visited[vertex] = 1;

    for (int i{}; i < N; ++i) {
        if (graph[vertex][i] == 1) {
            if (visited[i] == 0) { dfs(graph, N, visited, order, i); }
            else if (visited[i] == 1) { return; }
        }
    }
    visited[vertex] = 2;

    order.push_front(vertex);
}

int main() {
    setlocale(LC_ALL, "RU");

    int N{};
    int** orgraph{ nullptr };
    std::deque<int> order{};
    int* visited{ nullptr };

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

    visited = new int[N] {};
    for (int i{}; i < N; ++i) {
        if (visited[i] == 0) { dfs(orgraph, N, visited, order, i); }
    }

    std::cout << "Топологический порядок вершин: ";
    for (int i{}; i < N; ++i) {
        std::cout << order[i] + 1 << " ";
    }
    std::cout << std::endl;

    for (int i{}; i < N; ++i) {
        delete[] orgraph[i];
    }
    delete[] orgraph;
    delete[] visited;
    orgraph = nullptr;
    visited = nullptr;

    return EXIT_SUCCESS;
}