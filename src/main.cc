#include <iostream>
#include <string>
#include "graph.h"
#include "utils.h"
#include "brandes.h"

#ifdef DNDEBUG
const bool debug = false;
#else
const bool debug = true;
#endif

int main(int argc, char * argv[]) {

    if (argc != 4) {
        std::cerr << "[ERROR] " << "Invalid parameters!" << std::endl;
        return -1;
    }

    int threads = std::stoi(argv[1]);

    std::ifstream in_file;
    std::ofstream out_file;

    in_file.open(argv[2]);
    out_file.open(argv[3]);

    if (!in_file.good()) {
        std::cerr << "[ERROR] " << "Error while opening input file" << std::endl;
        return -1;
    }

    if (!out_file.good()) {
        std::cerr << "[ERROR] " << "Error while opening output file" << std::endl;
        return -1;
    }

    Graph<int> g;
    loadGraph(in_file, g);

    Brandes<int> brandes(g);
    brandes.run(threads);

    brandes.dump_output();
}
