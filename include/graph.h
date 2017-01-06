#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>

template<typename T>
class Graph {

public:
    void connect(const T &a, const T &b);
    const std::unordered_set<T>& get_vertex_ids() const;

    inline const std::vector<size_t>& get_neighbors(const size_t &vertex_id) const {
        return vertices_[vertex_id].adjacent_;
    }


private:
    struct Vertex {
        T id_;
        std::vector<size_t> adjacent_;

        Vertex(const T &id) : id_(id) {}

        void add_neighbor(Vertex* v) {
            adjacent_.insert(v);
            adjacent_ids_.insert(v->id_);
        }
    };

    std::unordered_map<T, size_t> alias_id_;

    std::vector<Vector> vertices_;

    Vertex* get_vertex(const T &a) const;
    Vertex* get_or_insert(const T &a);
};

template class Graph<int>;

#endif
