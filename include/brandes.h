#ifndef BRANDES_H
#define BRANDES_H

#include "graph.h"
#include <atomic>
#include <queue>
#include <stack>
#include <vector>
#include <mutex>

template <typename T> class Brandes {

    using fType = double;

    std::mutex bc_mutex;
    Graph<T> graph_;
    std::unordered_map<T, fType> BC;

    void process(T vertex_id);

public:
    Brandes(Graph<T>& graph)
        : graph_(graph)
    {
        for (auto v : graph_.get_vertex_ids()) {
            BC[v] = 0;
        }
    }

    void run(int thread_num) {
        for (auto v : graph_.get_vertex_ids()) {
            process(v);
        }
    }

    void dump_output() {
        for (auto t : BC) {
            std::cout << "BC[" << t.first << "] = " << t.second << std::endl;
        }
    }
};

#endif
