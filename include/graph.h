#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>

template<typename T>
class Graph {

    struct Vertex {
        T id_;
        std::unordered_set<Vertex*> adjacent_;
        std::unordered_set<T> adjacent_ids_;
        Vertex(T id) {
           id_ = id;
        }

        bool has_neighbor(Vertex *v) {
            return adjacent_.find(v) != adjacent_.end();
        }

        void add_neighbor(Vertex* v) {
            adjacent_.insert(v);
            adjacent_ids_.insert(v->id_);
        }
    };

    std::unordered_map<T, Vertex*> vertices_;
    std::unordered_set<T> vertex_ids;

    Vertex* get_vertex(T a);
    Vertex* get_or_insert(T a);

public:
    void connect(T a, T b);
    bool edge_exists(T a, T b);
    const std::unordered_set<T>& get_vertex_ids() const;

    inline const std::unordered_set<T>& get_neighbors(T vertex_id) {
        return vertices_[vertex_id]->adjacent_ids_;
    }

    ~Graph();
};

template class Graph<int>;

#endif
