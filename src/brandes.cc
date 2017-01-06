#include "brandes.h"

#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <thread>
#include <vector>

template<typename T>
void Brandes<T>::process(const size_t &vertex_id, std::vector<fType> *BC_local)
{
    size_t vec_size = BC_local->size();
    std::stack<size_t> S;
    std::vector<std::vector<size_t>> P(vec_size);
    std::vector<int> sigma(vec_size);
    std::vector<int> d(vec_size);
    std::vector<fType> delta(vec_size);

    for (size_t w = 0; w < graph_.get_vertex_num(); w++) {
        sigma[w] = 0;
        d[w] = -1;
        delta[w] = 0;
    }

    sigma[vertex_id] = 1;
    d[vertex_id] = 0;

    std::queue<size_t> Q;
    Q.push(vertex_id);

    while (!Q.empty()) {
        size_t v = Q.front();
        Q.pop();
        S.push(v);

        for (const auto &w : graph_.get_neighbor_aliases(v)) {
            if (d[w] < 0) {
                Q.push(w);
                d[w] = d[v] + 1;
            }

            if (d[w] == d[v] + 1) {
                sigma[w] += sigma[v];
                P[w].emplace_back(v);
            }
        }
    }

    while (!S.empty()) {
        size_t v = S.top(); S.pop();

        for (size_t p : P[v]) {
            double result = (fType(sigma[p]) / sigma[v]) * (1.0 + delta[v]);
            delta[p] += result;
        }

        if (v != vertex_id) {
            (*BC_local)[v] += delta[v];
        }
    }

}

template<typename T>
void Brandes<T>::run_worker(std::atomic<size_t> *idx) {
    std::vector<fType> BC_local(graph_.get_vertex_num());

    std::fill(begin(BC_local), end(BC_local), 0.0);

    while(true) {
        int my_index = (*idx)--;

        if (my_index < 0)
            break;

        process(my_index, &BC_local);
    }

    // Synchronized section
    {
        std::cerr << "Scalam.." << std::endl;
        std::lock_guard<std::mutex> guard(bc_mutex_);
        for (int i = 0; i < BC_local.size(); i++) {
            BC_[i] += BC_local[i];
        }
    }
}

template<typename T>
void Brandes<T>::run(const size_t thread_num) {
    std::vector<std::thread> threads;

    std::atomic<size_t> index;

    index.store(graph_.get_vertex_num() - 1);

    // run threads
    for (size_t i = 0; i < thread_num-1; i++)
        threads.emplace_back(std::thread( [this, &index] { run_worker(&index); }));

    // start working
    run_worker(&index);

    // wait for others to finish
    for (auto& thread : threads)
        thread.join();
}

template<typename T>
const std::vector<std::pair<T, typename Brandes<T>::fType>>
Brandes<T>::get_result_vector() {
    std::vector<std::pair<T, fType>> results;
    results.reserve(BC_.size());

    for (size_t i = 0; i < BC_.size(); i++) {
        if(graph_.get_neighbor_aliases(i).size() > 0)
            results.emplace_back(std::make_pair(graph_.get_id_from_alias(i), BC_[i]));
    }

    sort(begin(results), end(results));
    return results;
}
