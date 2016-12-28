#ifndef BRANDES_H
#define BRANDES_H

#include "graph.h"
#include <atomic>
#include <queue>
#include <stack>
#include <vector>
#include <mutex>
#include <utility>
#include <algorithm>
#include <thread>

template <typename T> class Brandes {

    using fType = double;

    std::mutex bc_mutex;
    Graph<T> &graph_;
    std::unordered_map<T, fType> BC;

    void process(T vertex_id);

    void run_worker(std::vector<T> &jobs, std::atomic<int> &idx) {
        while(true) {
            int my_index = idx--;

            if (my_index < 0)
                break;

            process(jobs[my_index]);
        }
    }

public:
    Brandes(Graph<T>& graph)
        : graph_(graph)
    {
        for (auto v : graph_.get_vertex_ids()) {
            BC[v] = 0;
        }
    }



    void run(size_t thread_num) {
        std::vector<std::thread> threads;

        std::vector<T> jobs;
        std::atomic<int> index;

        // add jobs
        for (auto id : graph_.get_vertex_ids())
            jobs.emplace_back(id);

        index.store(jobs.size() - 1);

        // run threads
        for (size_t i = 0; i < thread_num; i++)
            threads.push_back(std::thread( [this, &jobs, &index] { run_worker(jobs, index); }));

        // wait for them to finish
        for (auto& thread : threads)
            thread.join();
    }

    void dump_output() {
        for (auto t : BC) {
            std::cout << "BC[" << t.first << "] = " << t.second << std::endl;
        }
    }

    std::vector< std::pair<T, fType> > get_result_vector() {
        std::vector< std::pair<T, fType> > results;
        results.reserve(BC.size());

        for (auto it : BC) {
            results.push_back( std::make_pair(it.first, it.second));
        }

        sort(begin(results), end(results));
        return results;
    }
};

template class Brandes<int>;
#endif
