#include <iostream>
#include "graph.h"
#include "dijkstra_constants.h"

std::shared_ptr<Vertex> Graph::get_vertex(unsigned int id) {
    for (auto &vert : vertexes)
        if (vert->get_id() == id)
            return vert;
    return std::shared_ptr<Vertex>();
}

bool Graph::create_vertex(unsigned int id) {
    for (auto &vert : vertexes)
        if (vert->get_id() == id)
            return false;
    
    vertexes.push_back(std::make_shared<Vertex>(id));
    return true;
}

bool Graph::remove_vertex(unsigned int id) {
    if (std::shared_ptr<Vertex> vertex = get_vertex(id)) {
        vertex->remove_all_links();
        return std::erase_if(vertexes, [id] (std::shared_ptr<Vertex> vertex) {
            return vertex->get_id() == id;
        });
    }
    else
        return false;
}

bool Graph::create_link(unsigned int weight, unsigned int v1_id, unsigned int v2_id) {
    auto v1 = get_vertex(v1_id);
    auto v2 = get_vertex(v2_id);
    if (!v1 || !v2)
        return false;
    
    std::shared_ptr<Link> link = std::make_shared<Link>(weight, v1, v2);
    v1->add_link(link);
    v2->add_link(link);
    return true;
}

bool Graph::remove_link(unsigned int v1_id, unsigned int v2_id) {
    auto v1 = get_vertex(v1_id);
    auto v2 = get_vertex(v2_id);
    if (!v1 || !v2)
        return false;
    
    auto link = v1->get_link_to(v2.get());
    if (!link)
        return false;
    
    v1->remove_link(link.get());
    v2->remove_link(link.get());
    return true;
}

void Graph::set_vertexes_paths(std::shared_ptr<Vertex> to_vertex) {
    if (to_vertex->get_path_length() == dijkstra_constants::INFINITY_PATH)
        to_vertex->set_path_length(0);

    std::vector<std::shared_ptr<Link>> links = to_vertex->get_links();

    for (auto link : links) {
        std::shared_ptr<Vertex> linked_vertex = link->get_linked_vertex_from(to_vertex.get());
        unsigned int new_path_length = to_vertex->get_path_length() + link->get_weight();
        if (linked_vertex->get_path_length() == dijkstra_constants::INFINITY_PATH ||
        new_path_length < linked_vertex->get_path_length()) {
            linked_vertex->set_path_length(new_path_length);
            linked_vertex->next_vertex = to_vertex;
            set_vertexes_paths(linked_vertex);
        }
    }
}

unsigned int Graph::get_path_length(unsigned int from_vertex_id, unsigned int to_vertex_id) {
    std::shared_ptr<Vertex> from_vertex = get_vertex(from_vertex_id);
    std::shared_ptr<Vertex> to_vertex = get_vertex(to_vertex_id);

    if (!from_vertex || !to_vertex)
        return dijkstra_constants::INFINITY_PATH;
    
    set_vertexes_paths(to_vertex);

    return from_vertex->get_path_length();
}

std::vector<unsigned int> Graph::get_path_vertexes(unsigned int from_vertex_id, unsigned int to_vertex_id) {
    std::shared_ptr<Vertex> from_vertex = get_vertex(from_vertex_id);
    std::shared_ptr<Vertex> to_vertex = get_vertex(to_vertex_id);

    if (!from_vertex || !to_vertex)
        return std::vector<unsigned int>();
    
    set_vertexes_paths(to_vertex);

    if (!from_vertex->next_vertex.lock())
        return std::vector<unsigned int>();
    else {
        std::vector<unsigned int> vertexes_ids;
        std::shared_ptr<Vertex> next_vertex = from_vertex;

        do {
            vertexes_ids.push_back(next_vertex->get_id());
            next_vertex = next_vertex->next_vertex.lock();
        } while(next_vertex.get() != to_vertex.get());
        vertexes_ids.push_back(next_vertex->get_id());

        return vertexes_ids;
    }
}