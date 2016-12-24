#include <iostream>
#include "graph.h"
#include "utils.h"

int main(int argc, char * argv[]) {

    if (argc < 3) {
        std::cerr << "Za mało argumentów!" << std::endl;
        return -1;
    }
    std::ifstream in_file;
    in_file.open(argv[1]);

    Graph<int> g;
    loadGraph(in_file, g);
}
