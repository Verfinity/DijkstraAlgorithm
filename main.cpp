#include <iostream>
#include "graph.h"

int main()
{
    Graph graph;
    
    graph.create_vertex(0);
    graph.create_vertex(1);
    graph.create_vertex(2);

    graph.create_link(1, 0, 1);
    graph.create_link(2, 0, 2);
    graph.create_link(12, 1, 2);

    graph.remove_vertex(1);

    std::cout << std::endl;

    return 0;
}