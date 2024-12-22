#include <iostream>
#include "GraphParts.hpp"
#include "Graph.hpp"
#include "DynamicArray.hpp"


int main(int argc, const char * argv[]) {
    // Создаем граф
    Graph<int> graph;

    // Добавляем вершины
    for (int i = 0; i < 6; ++i) {
        graph.AddVertex(i);
    }

    // Добавляем дуги (ориентированный граф)
    graph.AddArc(0, 1, 1);
    graph.AddArc(0, 2, 1);
    graph.AddArc(1, 3, 1);
    graph.AddArc(2, 3, 1);
    graph.AddArc(3, 4, 1);
graph.AddArc(4, 5, 1);

    // Проверяем наличие цикла
    if (graph.hasCycle()) {
        std::cout << "The graph contains a cycle." << std::endl;
    } else {
        std::cout << "The graph does not contain a cycle." << std::endl;

        // Если цикла нет, выполняем топологическую сортировку
        DynamicArray<int> sortedVertices;
        graph.topologicalSort(sortedVertices);

        std::cout << "Topological Sort Order: ";
        for (const auto &vertex : sortedVertices) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    // Добавляем цикл для проверки
    graph.AddArc(4, 0, 1);

    if (graph.hasCycle()) {
        std::cout << "The graph now contains a cycle after adding edge 4 -> 0." << std::endl;
    } else {
        std::cout << "The graph does not contain a cycle." << std::endl;
    }

    return 0;
    return 0;
}
