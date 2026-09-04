#pragma once

#include <vector>
#include <memory>
#include "vertex.h"
#include "link.h"

class Graph {
private:
    std::vector<std::shared_ptr<Vertex>> vertexes;

    std::shared_ptr<Vertex> get_vertex(unsigned int id);

    void set_vertexes_paths(std::shared_ptr<Vertex> to_vertex);

public:
    bool create_vertex(unsigned int id);
    bool remove_vertex(unsigned int id);

    bool create_link(unsigned int weight, unsigned int v1_id, unsigned int v2_id);
    bool remove_link(unsigned int v1_id, unsigned int v2_id);

    unsigned int get_path_length(unsigned int from_vertex_id, unsigned int to_vertex_id);
    std::vector<unsigned int> get_path_vertexes(unsigned int from_vertex_id, unsigned int to_vertex_id);
};