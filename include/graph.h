#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>

template<typename T>
class Graph {
    
    struct Vertex {
        T id;
        std::unordered_set<Vertex *> adjacent;

        bool has_neighbor(Vertex *v) {
            return adjacent.find(v) != adjacent.end();
        }
    };

    std::unordered_map<T, Vertex*> vertices_;

    Vertex* get_vertex(T a);

public:
    void connect(T a, T b);
    bool edge_exists(T a, T b);
};

template class Graph<int>;

#endif
