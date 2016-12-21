#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>

template<typename T>
class Graph {

    struct Vertex {
        T id_;
        std::unordered_set<Vertex*> adjacent_;

        Vertex(T id) {
           id_ = id;
        }

        bool has_neighbor(Vertex *v) {
            return adjacent_.find(v) != adjacent_.end();
        }

        void add_neighbor(Vertex* v) {
            adjacent_.insert(v);
        }
    };

    std::unordered_map<T, Vertex*> vertices_;

    Vertex* get_vertex(T a);

public:
    void connect(T a, T b);
    bool edge_exists(T a, T b);

    ~Graph();
};

template class Graph<int>;

#endif
