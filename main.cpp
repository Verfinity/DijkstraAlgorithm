#include <iostream>
#include <vector>
#include "graph.h"

int main()
{
    Graph graph;
    
    graph.create_vertex(0);
    graph.create_vertex(1);
    graph.create_vertex(2);
    graph.create_vertex(3);
    graph.create_vertex(4);
    graph.create_vertex(5);

    graph.create_link(5, 0, 1);
    graph.create_link(6, 1, 2);
    graph.create_link(7, 2, 3);
    graph.create_link(8, 3, 4);
    graph.create_link(2, 1, 5);
    graph.create_link(3, 5, 3);

    std::cout << std::endl;

    unsigned int v1_id = 5, v2_id = 2;
    auto vertexes_ids = graph.get_path_vertexes(v1_id, v2_id);
    unsigned int path = graph.get_path_length(v1_id, v2_id);

    std::cout << "Vertexes ids: ";
    for (const auto &id : vertexes_ids) {
        std::cout << id << ' ';
    }
    std::cout << std::endl;

    std::cout << "Path length: " << path << std::endl;

    std::cout << std::endl;

    return 0;
}