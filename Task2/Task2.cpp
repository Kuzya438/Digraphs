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

void dfs(int** graph, int N, bool* visited, std::deque<int>& order, int vertex = 0) {
    visited[vertex] = true;

    for (int i{}; i < N; ++i) {
        if (graph[vertex][i] == 1 && visited[i] == false) {
            dfs(graph, N, visited, order, i);
        }
    }

    order.push_front(vertex);
}

int main() {
    setlocale(LC_ALL, "RU");

    int N{};
    int** orgraph{ nullptr };
    std::deque<int> order{};
    bool* visited{ nullptr };

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

    visited = new bool[N];
    for (int i{}; i < N; ++i) {
        visited[i] = false;
    }

    for (int i{}; i < N; ++i) {
        if (!visited[i]) { dfs(orgraph, N, visited, order, i); }
    }

    std::cout << "Топологический порядок вершин: ";
    for (int i{}; i < N; ++i) {
        std::cout << order[i] + 1 << " ";
    }

    for (int i{}; i < N; ++i) {
        delete[] orgraph[i];
    }
    delete[] orgraph;
    delete[] visited;
    orgraph = nullptr;
    visited = nullptr;

    return EXIT_SUCCESS;
}