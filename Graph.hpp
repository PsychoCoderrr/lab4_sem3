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
        return (int) graph.get_size();
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
};
    




#endif //LAB4_GRAPH
