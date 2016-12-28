#ifndef BRANDES_H
#define BRANDES_H

#include <vector>
#include <mutex>
#include <atomic>

#include "graph.h"

template <typename T>
class Brandes {
public:
    using fType = double;

    Brandes(Graph<T>& graph)
        : graph_(graph)
    {
        for (auto v : graph_.get_vertex_ids()) {
            BC_[v] = 0;
        }
    }

    void run(size_t thread_num);

    void dump_output() {
        for (auto t : BC_) {
            std::cout << "BC[" << t.first << "] = " << t.second << std::endl;
        }
    }
    std::vector< std::pair<T, fType> > get_result_vector();

private:
    void process(T vertex_id);
    void run_worker(std::vector<T> &jobs, std::atomic<int> &idx);

    std::mutex bc_mutex_;
    Graph<T> &graph_;
    std::unordered_map<T, fType> BC_;
};

template class Brandes<int>;
#endif
