#include "graph.h"

template<typename T>
size_t Graph<T>::get_or_insert(const T &a)
{
    // if no such key
    if (alias_id_.find(a) == alias_id_.end()) {
        // inswet new node with this id
        vertices_.emplace_back(Vertex(a));

        // mark last index as new mapping
        alias_id_[a] = vertices_.size() - 1;
    }

    return alias_id_[a];
}

template<typename T>
typename Graph<T>::Vertex& Graph<T>::get_vertex_by_alias(const size_t &id) {
    return vertices_[id];
}

template<typename T>
void Graph<T>::connect(const T &a, const T &b)
{
    size_t a_alias = get_or_insert(a);
    size_t b_alias = get_or_insert(b);

    Vertex& a_ptr = vertices_[a_alias];

    a_ptr.add_neighbor(b_alias);
}
