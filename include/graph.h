#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>

template<typename T>
class Graph {

public:
    void connect(const T &a, const T &b);

    inline const std::vector<size_t>& get_neighbor_aliases(const size_t &vertex_id) const {
        return vertices_[vertex_id].adjacent_;
    }

    size_t get_vertex_num() const {
        return vertices_.size();
    }

    T get_id_from_alias(size_t alias) const {
        return vertices_[alias].id_;
    }

private:
    struct Vertex {
        T id_;
        std::vector<size_t> adjacent_;

        Vertex(const T &id) : id_(id) {}

        void add_neighbor(size_t v) {
            adjacent_.push_back(v);
        }
    };

    std::unordered_map<T, size_t> alias_id_;

    std::vector<Vertex> vertices_;

    size_t get_or_insert(const T &a);
    Vertex& get_vertex_by_alias(const size_t &id);
};

template class Graph<int>;

#endif
