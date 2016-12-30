#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>

template<typename T>
class Graph {

public:
    void connect(const T &a, const T &b);
    const std::unordered_set<T>& get_vertex_ids() const;

    inline const std::unordered_set<T>& get_neighbors(const T &vertex_id) const {
        return vertices_.at(vertex_id)->adjacent_ids_;
    }

    ~Graph();

private:
    struct Vertex {
        T id_;
        std::unordered_set<Vertex*> adjacent_;
        std::unordered_set<T> adjacent_ids_;

        Vertex(const T &id) : id_(id) {}

        bool has_neighbor(Vertex *v) const {
            return adjacent_.find(v) != adjacent_.end();
        }

        void add_neighbor(Vertex* v) {
            adjacent_.insert(v);
            adjacent_ids_.insert(v->id_);
        }
    };

    std::unordered_map<T, Vertex*> vertices_;
    std::unordered_set<T> vertex_ids;

    Vertex* get_vertex(const T &a) const;
    Vertex* get_or_insert(const T &a);
};

template class Graph<int>;

#endif
