#include "vertex.h"

Vertex::Vertex(unsigned int id) : id(id) { }

Vertex::~Vertex() {
    std::shared_ptr<Vertex> linked_vertex;
    for (auto &lnk : links) {
        if (linked_vertex = lnk->get_linked_vertex(this))
            linked_vertex->remove_link(lnk.get());
    }
}

bool Vertex::add_link(std::shared_ptr<Link> link) {
    std::shared_ptr<Vertex> linked_vertex = link->get_linked_vertex(this);
    if (!linked_vertex)
        return false;

    for (auto &lnk : links)
        if (lnk->get_linked_vertex(this)->get_id() == linked_vertex->get_id())
            return false;
    
    links.push_back(link);
    return true;
}

bool Vertex::remove_link(const Link *link) {
    return std::erase_if(links, [&link] (std::shared_ptr<Link> lnk) {
        return lnk.get() == link;
    });
}

bool Vertex::has_link_to(const Vertex *vertex) {
    std::shared_ptr<Vertex> linked_vertex;
    for (auto &lnk : links) {
        if ((linked_vertex = lnk->get_linked_vertex(this)) &&
            linked_vertex.get() == vertex)
            return true;
    }
    return false;
}

std::vector<std::shared_ptr<Vertex>> Vertex::get_linked_vertexes() {
    std::vector<std::shared_ptr<Vertex>> vertexes;
    std::shared_ptr<Vertex> linked_vertex;
    for (auto &lnk : links) {
        if (linked_vertex = lnk->get_linked_vertex(this)) {
            vertexes.push_back(linked_vertex);
        }
    }
    return vertexes;
}

unsigned int Vertex::get_id() { return this->id; }

unsigned int Vertex::get_path_length() { return this->path_length; }

void Vertex::set_path_length(unsigned int path_length) { this->path_length=path_length; }
