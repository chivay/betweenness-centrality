#include "brandes.h"

#include <queue>
#include <stack>
#include <algorithm>
#include <thread>

template<typename T>
void Brandes<T>::process(T vertex_id, std::unordered_map<T, fType> *BC_local)
{
    std::stack<T> S;
    std::unordered_map<T, std::vector<T> > P;
    std::unordered_map<T, int> sigma;
    std::unordered_map<T, int> d;
    std::unordered_map<T, fType> delta;

    for (T w : graph_.get_vertex_ids()) {
        P[w] = std::vector<T>();
        sigma[w] = 0;
        d[w] = -1;
        delta[w] = 0;
    }

    sigma[vertex_id] = 1;
    d[vertex_id] = 0;

    std::queue<T> Q;
    Q.push(vertex_id);

    while (!Q.empty()) {
        T v = Q.front();
        Q.pop();
        S.push(v);

        for (auto w : graph_.get_neighbors(v)) {
            if (d[w] < 0) {
                Q.push(w);
                d[w] = d[v] + 1;
            }

            if (d[w] == d[v] + 1) {
                sigma[w] += sigma[v];
                P[w].push_back(v);
            }
        }
    }

    while (!S.empty()) {
        T v = S.top(); S.pop();

        for (T p : P[v]) {
            double result = (fType(sigma[p]) / sigma[v]) * (1.0 + delta[v]);
            delta[p] += result;
        }

        if (v != vertex_id) {
            (*BC_local)[v] += delta[v];
        }
    }

}

template<typename T>
void Brandes<T>::run_worker(const std::vector<T> &jobs, std::atomic<int> *idx) {
    std::unordered_map<T, fType> BC_local;

    for (T w : graph_.get_vertex_ids()) {
        BC_local[w] = 0;
    }

    while(true) {
        int my_index = (*idx)--;

        if (my_index < 0)
            break;

        process(jobs[my_index], &BC_local);
    }

    std::lock_guard<std::mutex> guard(bc_mutex_);
    for (auto it : BC_local) {
        BC_[it.first] += it.second;
    }
}

template<typename T>
void Brandes<T>::run(size_t thread_num) {
    std::vector<std::thread> threads;

    std::vector<T> jobs;
    std::atomic<int> index;

    // add jobs
    for (auto id : graph_.get_vertex_ids())
        jobs.emplace_back(id);

    index.store(jobs.size() - 1);

    // run threads
    for (size_t i = 0; i < thread_num; i++)
        threads.push_back(std::thread( [this, &jobs, &index] { run_worker(jobs, &index); }));

    // wait for them to finish
    for (auto& thread : threads)
        thread.join();
}

template<typename T>
std::vector<std::pair<T, typename Brandes<T>::fType>>
Brandes<T>::get_result_vector() const {
    std::vector<std::pair<T, fType>> results;
    results.reserve(BC_.size());

    for (auto it : BC_) {
        results.push_back( std::make_pair(it.first, it.second));
    }

    sort(begin(results), end(results));
    return results;
}
