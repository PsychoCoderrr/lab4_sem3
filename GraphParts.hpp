#ifndef LAB4_GRAPH_PARTS
#define LAB4_GRAPH_PARTS
#include <list>


template<typename T>
class Edge
{
private:
    T VertexName1;
    T VertexName2;
    int weight;
public:
    Edge(T vertex1, T vertex2, int weight) : VertexName1(vertex1), VertexName2(vertex2), weight(weight) {}

    Edge(Edge const &edge) : VertexName1(edge.VertexName1), VertexName2(edge.VertexName2), weight(edge.weight) {}
    
    int GetWeight()
    {
        return weight;
    }
    
    T GetFirst()
    {
        return VertexName1;
    }
    
    T GetLast()
    {
        return VertexName2;
    }
    
    void Reverse()
    {
        T tmp = VertexName1;
        VertexName1 = VertexName2;
        VertexName2 = tmp;
    }
};



template<typename T>
struct Vertex
{
    T name;
    std::list<Edge<T>> list;
};

#endif //LAB4_GRAPH_PARTS
