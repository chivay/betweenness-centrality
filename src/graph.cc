#include "graph.h"

template<typename T>
typename Graph<T>::Vertex* Graph<T>::get_vertex(const T &a) const
{
    auto it = vertices_.find(a);
    if (it == vertices_.end())
        return nullptr;
    else
        return it->second;
}

template<typename T>
typename Graph<T>::Vertex* Graph<T>::get_or_insert(const T &a)
{
    Vertex* a_ptr = get_vertex(a);
    if (a_ptr == nullptr) {
        a_ptr = new Vertex(a);
        vertices_.insert({a, a_ptr});
        vertex_ids.insert(a);
    }

    return a_ptr;
}


template<typename T>
void Graph<T>::connect(const T &a, const T &b)
{
    Vertex* a_ptr = get_or_insert(a);
    Vertex* b_ptr = get_or_insert(b);

    a_ptr->add_neighbor(b_ptr);
}

template<typename T>
inline const std::unordered_set<T>& Graph<T>::get_vertex_ids() const
{
    return vertex_ids;
}
