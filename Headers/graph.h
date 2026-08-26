#pragma once

#include <vector>
#include <memory>
#include "vertex.h"
#include "link.h"

class Graph {
private:
    std::vector<std::shared_ptr<Vertex>> vertexes;

    std::shared_ptr<Vertex> get_vertex(unsigned int id);

public:
    bool create_vertex(unsigned int id);
    bool remove_vertex(unsigned int id);

    bool create_link(unsigned int weight, unsigned int v1_id, unsigned int v2_id);
    bool remove_link(unsigned int v1_id, unsigned int v2_id);
};