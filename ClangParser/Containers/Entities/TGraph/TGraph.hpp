#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>
struct custom_node {
    custom_node(std::string name, int capacity = -1)
        : name(std::move(name)), capacity(capacity) {}

    std::string name = "uninitialized";
    int capacity = -1;

    friend std::ostream& operator<<(std::ostream& os, custom_node const& cn) {
        return os << "{" << cn.name << ", " << cn.capacity << "}";
    }
    void operator=(custom_node const& n) {
        name = n.name;
        capacity = n.capacity;
    }
};

struct VertexProperties {
    int id{};
    std::optional<custom_node> node;

    friend std::ostream& operator<<(std::ostream& os, VertexProperties const& vp) {
        os << vp.id;
        if (vp.node) os << ", " << *vp.node;
        return os;
    }
    void operator=(VertexProperties const& vp) {
        id = vp.id;
        node = vp.node;
    }
};

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperties>;
using custom_vertex = Graph::vertex_descriptor;
using custom_edge = Graph::edge_descriptor;
