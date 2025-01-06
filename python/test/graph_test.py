from graph import *
from input import create_square
from point import Point


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


def example_graph_short_initialisation():
    g = Graph()
    vertices = [
        (0, {'pos': Point(-1, -1)}),
        (1, {'pos': Point(-1, 1)}),
        (2, {'pos': Point(1, 1)}),
        (3, {'pos': Point(1, -1)}),
    ]
    g.add_vertices(vertices)

    edges = [
        ("a", 0, 1),
        ("a", 3, 2),
        ("b", 1, 2),
        ("b", 0, 3),
    ]
    g.add_edges(edges)
    print(g)


# some_basic_graph_access()
# print_graph()
# print_graph_shorthand()
# example_graph_short_initialisation()
