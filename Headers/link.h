#pragma once

#include <memory>
#include "vertex.h"

class Link {
private:
    unsigned int weight;
    std::weak_ptr<Vertex> vertex_1, vertex_2;

public:
    Link(unsigned int weight, std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2);

    std::shared_ptr<Vertex> get_linked_vertex(const Vertex *from_vertex);

    unsigned int get_weight();
};