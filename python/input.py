from graph import *
from point import Point


def create_empty_graph():
    g = Graph()
    return g


def create_square():
    g = Graph()
    add_square(g, 1, 0, 0)
    return g


def create_cube():
    g = Graph()
    add_square(g, 1, 0, 0, 0)
    add_square(g, 1, 0, 0, 1)

    g.add_edge("c", 0, 4)
    g.add_edge("c", 1, 5)
    g.add_edge("c", 2, 6)
    g.add_edge("c", 3, 7)

    return g


def add_square(g, length, x, y, z=0):
    base_x = x - length / 2
    base_y = y - length / 2

    v = g.get_next_vertex_id()

    g.add_vertex(v, Point(base_x, base_y, z))
    g.add_vertex(v + 1, Point(base_x, base_y + length, z))
    g.add_vertex(v + 2, Point(base_x + length, base_y + length, z))
    g.add_vertex(v + 3, Point(base_x + length, base_y, z))

    e = g.edge_size()

    # TODO should ids be generated?
    # We don't really need id's I think, but would be nice if we could generate labels
    # with lookup in dict etc
    g.add_edge("a", v, v + 1)
    g.add_edge("b", v + 1, v + 2)
    g.add_edge("a", v + 2, v + 3)
    g.add_edge("b", v + 3, v)


def create_triangle():
    g = Graph()

    g.add_vertex(0, Point(0, 0))
    g.add_vertex(1, Point(1, 0))
    g.add_vertex(2, Point(0, 1))

    g.add_edge("a", 0, 1)
    g.add_edge("b", 1, 2)
    g.add_edge("c", 2, 0)

    return g


def create_letter_h():
    g = Graph()

    g.add_vertex(0, Point(0, 0))
    g.add_vertex(1, Point(0, 1))
    g.add_vertex(2, Point(0, 2))
    g.add_vertex(3, Point(1, 0))
    g.add_vertex(4, Point(1, 1))
    g.add_vertex(5, Point(1, 2))

    g.add_edge("a", 0, 1)
    g.add_edge("a", 1, 2)
    g.add_edge("b", 1, 4)
    g.add_edge("a", 3, 4)
    g.add_edge("a", 4, 5)

    return g

