#include <iostream>
#include "GraphParts.hpp"
#include "Graph.hpp"
#include "DynamicArray.hpp"


int main(int argc, const char * argv[]) {
    Graph<int> graph;
    graph.AddVertex(1);
    graph.AddVertex(2);
    graph.AddVertex(3);
    graph.AddEdge(1, 2, 5);
    graph.AddEdge(2, 3, 10);
    return 0;
}
