#include <iostream>
#include "graph.h"
#include "utils.h"
#include "brandes.h"

int main(int argc, char * argv[]) {

    if (argc != 4) {
        std::cerr << "Niepoprawne argumenty!" << std::endl;
        return -1;
    }
    std::ifstream in_file;
    in_file.open(argv[1]);

    Graph<int> g;
    loadGraph(in_file, g);

    Brandes<int> brandes(g);
    brandes.run(1);
}
