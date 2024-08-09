from point import Point
from graph import Graph


def load_graph():
    # return load_triangle()
    # return load_square()
    return load_cube()


def load_triangle():
    g = Graph()

    g.add_vertex(1, Point(0, 0))
    g.add_vertex(2, Point(1, 0))
    g.add_vertex(3, Point(0, 1))

    g.add_edge("a", 1, 2)
    g.add_edge("b", 2, 3)
    g.add_edge("c", 3, 1)

    return g


def load_square():
    g = Graph()
    add_square(g, 1, 0, 0)
    return g


def load_cube():
    g = Graph()
    add_square(g,1, 0, 0, -0.5)
    add_square(g,1, 0, 0, 0.5)

    e = g.edge_size()

    g.add_edge(str(e), 0, 4)
    g.add_edge(str(e + 1), 1, 5)
    g.add_edge(str(e + 2), 2, 6)
    g.add_edge(str(e + 3), 3, 7)

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
    g.add_edge(str(e), v, v + 1)
    g.add_edge(str(e + 1), v + 1, v + 2)
    g.add_edge(str(e + 2), v + 2, v + 3)
    g.add_edge(str(e + 3), v + 3, v)
