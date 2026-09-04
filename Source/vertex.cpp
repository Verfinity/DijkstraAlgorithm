#include <iostream>
#include <algorithm>
#include "vertex.h"
#include "link.h"

Vertex::Vertex(unsigned int id) : id(id) {
    std::cout << "Created vertex with id: " << id << std::endl;
}

Vertex::~Vertex() {
    std::cout << "Destroyed vertex with id: " << id << std::endl;
}

bool Vertex::add_link(std::shared_ptr<Link> link) {
    std::shared_ptr<Vertex> linked_vertex = link->get_linked_vertex_from(this);
    if (!linked_vertex)
        return false;

    for (auto &lnk : links)
        if (lnk->get_linked_vertex_from(this)->get_id() == linked_vertex->get_id())
            return false;
    
    links.push_back(link);
    return true;
}

bool Vertex::remove_link(const Link *link) {
    return std::erase_if(links, [&link] (std::shared_ptr<Link> lnk) {
        return lnk.get() == link;
    });
}

void Vertex::remove_all_links() {
    std::shared_ptr<Vertex> linked_vertex;
    for (auto &lnk : links)
        if (linked_vertex = lnk->get_linked_vertex_from(this))
            linked_vertex->remove_link(lnk.get());
    links.clear();
}

bool Vertex::has_link_to(const Vertex *vertex) {
    std::shared_ptr<Vertex> linked_vertex;
    for (auto &lnk : links) {
        if ((linked_vertex = lnk->get_linked_vertex_from(this)) &&
            linked_vertex.get() == vertex)
            return true;
    }
    return false;
}

std::shared_ptr<Link> Vertex::get_link_to(const Vertex *vertex) {
    std::shared_ptr<Vertex> linked_vertex;
    for (auto &lnk : links) {
        if ((linked_vertex = lnk->get_linked_vertex_from(this)) &&
            linked_vertex.get() == vertex)
            return lnk;
    }
    return std::shared_ptr<Link>();
}

std::vector<std::shared_ptr<Link>> Vertex::get_links() {
    return links;
}

std::vector<std::shared_ptr<Vertex>> Vertex::get_linked_vertexes() {
    std::vector<std::shared_ptr<Vertex>> vertexes;
    std::shared_ptr<Vertex> linked_vertex;
    for (auto &lnk : links) {
        if (linked_vertex = lnk->get_linked_vertex_from(this)) {
            vertexes.push_back(linked_vertex);
        }
    }
    return vertexes;
}

unsigned int Vertex::get_id() { return this->id; }

unsigned int Vertex::get_path_length() { return this->path_length; }

void Vertex::set_path_length(unsigned int path_length) { this->path_length=path_length; }
