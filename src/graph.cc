#include "graph.h"

#ifdef DNDEBUG
const bool debug = false;
#else
const bool debug = true;
#endif

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
typename Graph<T>::Vertex* Graph<T>::get_or_insert(T a)
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
    if(debug)
        std::cerr << "[DEBUG] Connecting " << a << " -> " << b << std::endl;
    Vertex* a_ptr = get_or_insert(a);
    Vertex* b_ptr = get_or_insert(b);

    a_ptr->add_neighbor(b_ptr);
}

template<typename T>
const std::unordered_set<T>& Graph<T>::get_vertex_ids()
{
    return vertex_ids;
}

template<typename T>
Graph<T>::~Graph()
{
    for (auto v : vertices_)
        delete v.second;
}
