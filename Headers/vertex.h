#pragma once

#include <vector>
#include <memory>
#include "dijkstra_constants.h"

class Link;

class Vertex {
public:
    std::weak_ptr<Vertex> next_vertex; // dijstrka

private:
    unsigned int id;
    unsigned int path_length = dijkstra_constants::INFINITY_PATH; // dijkstra
    std::vector<std::shared_ptr<Link>> links;

public:
    Vertex(unsigned int id);

    ~Vertex();

    bool add_link(std::shared_ptr<Link> link);
    bool remove_link(const Link *link);
    void remove_all_links();
    bool has_link_to(const Vertex *vertex);
    std::shared_ptr<Link> get_link_to(const Vertex *vertex);

    std::vector<std::shared_ptr<Vertex>> get_linked_vertexes();
    std::vector<std::shared_ptr<Link>> get_links();

    unsigned int get_id();

    unsigned int get_path_length();
    void set_path_length(unsigned int path_length);
};