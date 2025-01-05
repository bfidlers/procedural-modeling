from graph_test import create_square
from point import Point


def set_unset_vertices():
    g = create_square()
    print(g)
    g.unset_vertex(1)
    g.unset_vertex(2)
    print(g)

    print(g.get_unset_vertices())
    print(g.vertices_to_loosen)

    g.loosen()
    print(g.get_unset_vertices())
    print(g.vertices_to_loosen)
    print(g)

    g.set_vertex_position(1, Point(1, 2, 3))
    print(g.get_unset_vertices())
    print(g)


set_unset_vertices()
