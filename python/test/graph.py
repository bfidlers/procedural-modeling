from graph2 import *
from point import Point


def create_square():
    g = Graph()
    add_square(g, 1, 0, 0)
    return g


def add_square(g, length, x, y, z=0):
    base_x = x - length / 2
    base_y = y - length / 2

    v = g.vertex_size()

    g.add_vertex(v, Point(base_x, base_y, z))
    g.add_vertex(v + 1, Point(base_x + length, base_y, z))
    g.add_vertex(v + 2, Point(base_x + length, base_y + length, z))
    g.add_vertex(v + 3, Point(base_x, base_y + length, z))

    e = g.edge_size()

    # TODO should ids be generated?
    # We don't really need id's I think, but would be nice if we could generate labels
    # with lookup in dict etc
    g.add_edge(str(e), v, v + 1)
    g.add_edge(str(e + 1), v + 1, v + 2)
    g.add_edge(str(e + 2), v + 2, v + 3)
    g.add_edge(str(e + 3), v + 3, v)


def some_basic_graph_access():
    g = create_square()
    print("Vertex size", g.vertex_size())
    print("Edge size", g.edge_size())
    print(g.graph[1])
    print(g.graph[1][2])
    print(g.graph.adj[1])
    print(g.graph.edges(1))
    print(g.graph.edges())
    print(g.graph.nodes[1])
    print([n for n in g.graph])
    print(g.graph.nodes[1]["pos"])


def print_graph():
    g = create_square()
    print(g)


def print_graph_shorthand():
    g = create_square()
    print(g.shorthand())


# some_basic_graph_access()
# print_graph()
print_graph_shorthand()

