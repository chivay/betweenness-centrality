#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>

template<typename T>
class Graph {
    
    struct Vertex {
        T id;
    };

    std::unordered_map<T, Vertex*> vertices;

public:
    void connect(T a, T b);

};


template class Graph<int>;

#endif
