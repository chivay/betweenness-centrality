#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include "graph.h"


template<typename T>
void loadGraph(std::ifstream &file, Graph<T> &graph) {
    T a;
    T b;

    while(file >> a >> b) {
        graph.connect(a,b);
    }
}

#endif 
