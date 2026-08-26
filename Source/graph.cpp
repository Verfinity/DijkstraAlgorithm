#include "../Headers/graph.h"

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
    return std::erase_if(vertexes, [id] (std::shared_ptr<Vertex> vertex) {
        return vertex->get_id() == id;
    });
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
