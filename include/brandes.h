#ifndef BRANDES_H
#define BRANDES_H

#include <atomic>
#include <mutex>
#include <vector>

#include "graph.h"

template <typename T>
class Brandes {

public:
    using fType = double;

    Brandes(const Graph<T>& graph)
        : graph_(graph)
    {
        BC_.resize(graph_.get_vertex_num());
        std::fill(begin(BC_), end(BC_), 0.0);
    }

    void run(size_t thread_num);
    const std::vector<std::pair<T, fType>> get_result_vector();

private:
    void process(const size_t &vertex_id, std::vector<fType>* BC_local);
    void run_worker(std::atomic<size_t> *idx);

    std::mutex bc_mutex_;
    const Graph<T> &graph_;
    std::vector<fType> BC_;
};

template class Brandes<int>;
#endif
