#include "brandes.h"


template<typename T>
void Brandes<T>::process(T vertex_id)
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
            BC_local[v] += delta[v];
        }
    }

    std::lock_guard<std::mutex> guard(bc_mutex);
    for (auto it : BC_local) {
        BC[it.first] += it.second;
    }
}

