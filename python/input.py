from point import Point
from graph import Graph


def load_graph():
    # return load_triangle()
    return load_square()


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

    g.add_vertex(1, Point(-0.5, -0.5))
    g.add_vertex(2, Point(-0.5, 0.5))
    g.add_vertex(3, Point(0.5, 0.5))
    g.add_vertex(4, Point(0.5, -0.5))

    g.add_edge("a", 1, 2)
    g.add_edge("b", 2, 3)
    g.add_edge("c", 4, 3)
    g.add_edge("d", 1, 4)

    return g

