#include <iostream>
#include <fstream>
#include <string>
#include "brandes.h"
#include "graph.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Invalid parameters!" << std::endl
                  << "Usage: " << argv[0] << " [number of threads] [input file] [output file]" << std::endl;

        return -1;
    }

    int threads = std::stoi(argv[1]);

    if (threads <= 0) {
        std::cerr << "Number of threads must be more than 0" << std::endl;
        return -1;
    }

    std::ifstream in_file;
    std::ofstream out_file;

    in_file.open(argv[2]);
    out_file.open(argv[3]);

    if (!in_file.good()) {
        std::cerr << "[ERROR] "
                  << "Error while opening input file" << std::endl;
        return -1;
    }

    if (!out_file.good()) {
        std::cerr << "[ERROR] "
                  << "Error while opening output file" << std::endl;
        return -1;
    }

    Graph<int> g;
    loadGraph(in_file, g);
    in_file.close();

    Brandes<int> brandes(g);
    brandes.run(threads);

    for (auto p : brandes.get_result_vector()) {
        out_file << p.first << " " << p.second << std::endl;
    }
    out_file.close();
}
