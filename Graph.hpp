#ifndef LAB4_GRAPH
#define LAB4_GRAPH
#include "DynamicArray.hpp"
#include <list>
#include "GraphParts.hpp"
#include <vector>

template<typename T>
class Graph
{
private:
    DynamicArray<Vertex<T>> graph;
public:
    
    Graph() = default;
    
    
    
    void AddVertex(T vertexName)
    {
        if (SearchVertex(vertexName))
        {
            return;
        }
        Vertex<T> vertex;
        vertex.name = vertexName;
        std::list<Edge<T>> list;
        vertex.list = list;
        graph.push_back(vertex);
    }
    
    bool SearchVertex(T vertexName)
    {
        for (auto &i: graph)
        {
            if (i.name == vertexName)
            {
                return true;
            }
        }
        return false;
    }
    
    
    void AddEdge(T vertexName1, T vertexName2, int weight)
    {
        if (SearchEdgeArc(vertexName1, vertexName2))
        {
            return;
        }

        Edge newEdge(vertexName1, vertexName2, weight);
        for (auto &i: graph)
        {
            if (i.name == vertexName1)
            {
                i.list.push_back(newEdge);
            }
        }

        Edge reverseEdge(vertexName2, vertexName1, weight);
        for (auto &i: graph){
            if (i.name == vertexName2)
            {
                i.list.push_back(reverseEdge);
            }
        }
    }
    
    void AddArc(T vertexName1, T vertexName2, int weight)
    {
        if (SearchEdgeArc(vertexName1, vertexName2)) return;
        Edge newEdge(vertexName1, vertexName2, weight);
        for (auto &i: graph)
        {
            if (i.name == vertexName1)
            {
                i.list.push_back(newEdge);
            }
        }
    }
    
    bool SearchEdgeArc(T vertexName1, T vertexName2)
    {
        for (auto &i: graph)
        {
            for (auto &it: i.list)
            {
                if (it.GetFirst() == vertexName1 && it.GetLast() == vertexName2)
                {
                    return true;
                }
            }
        }
        return false;
    }
    
    void RemoveEdge(T vertexName1, T vertexName2)
    {
        for (auto &j: graph)
        {
            for (auto i = j.list.begin(); i != j.list.end();)
            {
                if (((*i).vertex1 == vertexName1 && (*i).vertex2 == vertexName2) ||
                    ((*i).vertex1 == vertexName2 && (*i).vertex2 == vertexName1))
                {
                    i = j.list.erase(i);
                }
                else
                {
                    i++;
                }
            }
        }
    }
    
    void RemoveVertex(T vertexName)
    {
        for (auto i = graph.begin(); i != graph.end();)
        {
            if ((*i).name == vertexName)
            {
                graph.erase(i);
                break;
            }
            else
            {
                i++;
            }
        }

        for (auto &i: graph)
        {
            for (auto it = i.list.begin(); it != i.list.end();)
            {
                if ((*it).vertex1 == vertexName || (*it).vertex2 == vertexName)
                {
                    it = i.list.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }
    
    int GetSize()
    {
        return static_cast<int>(graph.get_size());
    }
    
    
    void ChangeWeightArc(T vertexName1, T vertexName2, int weight)
    {
        if (!SearchVertex(vertexName1) || !SearchVertex(vertexName2))
        {
            return;
        }
        for (auto &i: graph)
        {
            for (auto &it: i.list)
            {
                if (it.vertex1 == vertexName1 && it.vertex2 == vertexName2)
                {
                    it.weight = weight;
                }
            }
        }
    }
    
    void ChangeWeightEdge(T vertexName1, T vertexName2, int weight)
    {
        if (!SearchVertex(vertexName1) || !SearchVertex(vertexName2))
        {
            return;
        }
        for (auto &i: graph)
        {
            for (auto &it: i.list)
            {
                if ((it.vertex1 == vertexName1 && it.vertex2 == vertexName2) ||
                    (it.vertex1 == vertexName2 && it.vertex2 == vertexName1))
                {
                    it.weight = weight;
                }
            }
        }
    }
    
    void Print()
    {
        for (auto &i: graph)
        {
            std::cout << "VertexName: " << i.name << " { ";
            for (auto &it: i.list)
            {
                std::cout << "[" << it.GetFirst() << "-" << it.GetLast() << ":" << it.GetWeight() << "] ";
            }
            std::cout << "}" << std::endl;
        }
    }
    
    
    std::pair<DynamicArray<int>, DynamicArray<int>> Dijkstra(int startVertexIndex, int endVertexIndex) {
        int numVertices = GetSize();
        DynamicArray<int> dist(numVertices, INT_MAX);
        DynamicArray<int> prev(numVertices, -1);
        DynamicArray<bool> visited(numVertices, false);

        dist[startVertexIndex] = 0;

        for (int i = 0; i < numVertices; ++i) {
            int u = -1;
            for (int j = 0; j < numVertices; ++j) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == INT_MAX) {
                break;
            }
            
            visited[u] = true;

            for (const auto &edge : graph[u].list) {
                int vertEnd = edge.GetLast();
                int weight = edge.GetWeight();

                if (dist[vertEnd] > dist[u] + weight) {
                    dist[vertEnd] = dist[u] + weight;
                    prev[vertEnd] = u;
                }
            }
        }

        DynamicArray<int> path;
        for (int at = endVertexIndex; at != -1; at = prev[at]) {
            path.push_back(at);
        }

        std::reverse(path.begin(), path.end());

        return {dist, path};
    }
    
    DynamicArray<T> DFS(int startVertexIndex, int endVertexIndex)
    {
        DynamicArray<T> path;
        if (!SearchVertex(startVertexIndex) || !SearchVertex(endVertexIndex)) return path;
        DynamicArray<bool> visited(this->GetSize(), false);
        std::stack<int> stack;
        DynamicArray<int> parent(this->GetSize(), -1);

        visited[startVertexIndex] = true;
        stack.push(startVertexIndex);

        while (!stack.empty())
        {
            int currentVertex = stack.top();
            stack.pop();

            if (currentVertex == endVertexIndex)
            {
                int v = endVertexIndex;
                while (v != -1)
                {
                    path.push_back(v);
                    v = parent[v];
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            for (auto i: graph[currentVertex].list)
            {
                if (!visited[i.GetLast()])
                {
                    stack.push(i.GetLast());
                    visited[i.GetLast()] = true;
                    parent[i.GetLast()] = currentVertex;
                }
            }
        }
        return path;
    }
    
    DynamicArray<T> BFS(int startVertexIndex, int endVertexIndex)
    {
        DynamicArray<T> path;
        if (!SearchVertex(startVertexIndex) || !SearchVertex(endVertexIndex))
        {
            return path;
        }
        DynamicArray<bool> visited(this->GetSize(), false);
        std::queue<int> queue;
        DynamicArray<int> parent(this->GetSize(), -1);
        
        visited[startVertexIndex] = true;
        queue.push(startVertexIndex);
        
        while (!queue.empty()) {
            int currentVertex = queue.front();
            queue.pop();
            
            if (currentVertex == endVertexIndex)
            {
                int v = endVertexIndex;
                while (v != -1)
                {
                    path.push_back(v);
                    v = parent[v];
                }
                std::reverse(path.begin(), path.end());
                return path;
            }
            
            for (auto i: graph[currentVertex].list)
            {
                if (!visited[i.GetLast()])
                {
                    queue.push(i.GetLast());
                    visited[i.GetLast()] = true;
                    parent[i.GetLast()] = currentVertex;
                }
            }
        }
        return path;
    }
    
    void topologicalSort(DynamicArray<int> &topologicalSort)
    {
        if (this->hasCycle())
        {
            return;
        }
        std::stack<int> Stack;
        DynamicArray<bool> visited(this->GetSize(), false);

        for (int i = 0; i < graph.get_size(); i++)
            if (!visited[i])
            {
                topologicalSortUtil(i, visited, Stack);
            }

        while (!Stack.empty())
        {
            topologicalSort.push_back(Stack.top());
            Stack.pop();
        }
    }

    bool hasCycle()
    {
        int numVertices = (int) graph.get_size();
        bool *visited = new bool[numVertices];
        bool *recStack = new bool[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = false;
            recStack[i] = false;
        }

        for (int i = 0; i < numVertices; i++)
        {
            if (hasCycleUtil(i, visited, recStack))
            {
                delete[] visited;
                delete[] recStack;
                return true;
            }
        }

        delete[] visited;
        delete[] recStack;

        return false;
    }
    
private:

    void topologicalSortUtil(int vertex, DynamicArray<bool> &visited, std::stack<int> &Stack) {
        visited[vertex] = true;
        for (auto &it: graph[vertex].list)
            if (!visited[it.GetLast()])
                topologicalSortUtil(it.GetLast(), visited, Stack);
        Stack.push(vertex);
    }

    bool hasCycleUtil(int v, bool visited[], bool *recStack) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;

            for (auto &edge: graph[v].list) {
                int neighbor = edge.GetLast();
                if (!visited[neighbor] && hasCycleUtil(neighbor, visited, recStack)) {
                    return true;
                } else if (recStack[neighbor]) {
                    return true;
                }
            }
        }
        recStack[v] = false;
        return false;
    }
};
    




#endif //LAB4_GRAPH
