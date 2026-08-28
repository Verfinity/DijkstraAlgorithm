#include <iostream>
#include "link.h"

Link::Link(unsigned int weight, std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2)
    : weight(weight), vertex_1(v1), vertex_2(v2) {
        std::cout << "Created link with weight: " << weight << std::endl;
    }

Link::~Link() {
    std::cout << "Destroyed link with weight: " << weight << std::endl;
}

std::shared_ptr<Vertex> Link::get_linked_vertex_from(const Vertex *from_vertex) {
    if (vertex_1.lock().get() == from_vertex)
        return vertex_2.lock();
    else if (vertex_2.lock().get() == from_vertex)
        return vertex_1.lock();
    
    return std::shared_ptr<Vertex>();
}

unsigned int Link::get_weight() { return this->weight; }
