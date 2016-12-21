#include "graph.h"

template<typename T>
typename Graph<T>::Vertex* Graph<T>::get_vertex(T a)
{
    auto it = vertices_.find(a);
    if (it == vertices_.end())
        return nullptr;
    else
        return it->second;
}

template<typename T>
bool Graph<T>::edge_exists(T a, T b)
{
    Vertex* a_ptr = get_vertex(a);
    Vertex* b_ptr = get_vertex(b);

    if (a_ptr == nullptr)
        return false;

    return a_ptr->has_neighbor(b_ptr);
}

template<typename T>
void Graph<T>::connect(T a, T b)
{
    Vertex* a_ptr = get_vertex(a);
    Vertex* b_ptr = get_vertex(b);

    if (a_ptr == nullptr) {
        a_ptr = new Vertex(a);
        vertices_.insert({a, a_ptr});
    }

    if (b_ptr == nullptr) {
        b_ptr = new Vertex(b);
        vertices_.insert({b, b_ptr});
    }

    a_ptr->add_neighbor(b_ptr);
}
