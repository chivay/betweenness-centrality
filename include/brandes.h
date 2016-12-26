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

    void process(T vertex_id)
    {
        std::stack<T> S;
        std::unordered_map<T, std::vector<T> > P;
        std::unordered_map<T, int> sigma;
        std::unordered_map<T, int> d;
        std::unordered_map<T, fType> delta;
        std::unordered_map<T, fType> BC_local;

        for (T w : graph_.get_vertex_ids()) {
            P[w] = std::vector<T>();
            sigma[w] = 0;
            d[w] = -1;
            delta[w] = 0;
            BC_local[w] = 0;
        }

        sigma[vertex_id] = 1;
        d[vertex_id] = 0;

        std::queue<T> Q;
        Q.push(vertex_id);

        while (!Q.empty()) {
            T v = Q.front();
            Q.pop();
            S.push(v);

            for (auto w : graph_.get_neighbors(vertex_id)) {
                if (d[w] < 0) {
                    Q.push(w);
                    d[w] = d[vertex_id] + 1;
                }
                if (d[w] == d[v] + 1) {
                    sigma[w] += sigma[v];
                    P[w].push_back(vertex_id);
                }
            }
        }

        while (!S.empty()) {
            T w = S.top(); S.pop();

            for (T v : P[w]) {
                delta[v] += (sigma[v] / sigma[w]) * (1 + delta[w]);
            }

            if (w != vertex_id)
                BC_local[w] += delta[w];
        }

        std::lock_guard<std::mutex> guard(bc_mutex);
        for (auto it : BC_local) {
            BC[it.first] += it.second;
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

    void run(int thread_num) {
        for (auto v : graph_.get_vertex_ids()) {
            process(v);
        }
    } 
};

#endif
