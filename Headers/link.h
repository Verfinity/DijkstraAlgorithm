#pragma once

#include <memory>

class Vertex;

class Link {
private:
    unsigned int weight;
    std::weak_ptr<Vertex> vertex_1, vertex_2;

public:
    Link(unsigned int weight, std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2);

    ~Link();

    std::shared_ptr<Vertex> get_linked_vertex_from(const Vertex *from_vertex);

    unsigned int get_weight();
};