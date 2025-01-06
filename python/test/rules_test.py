from graph2 import *
from rule import *


def compute_rules(graph_type):
    if graph_type == "square":
        return load_square_rules()
    if graph_type == "rectangle":
        return load_square_rules()
    if graph_type == "triangle":
        return load_triangle_rules()
    if graph_type == "letter_h":
        return load_letter_h_rules()
    if graph_type == "letter_h_no_loops":
        return load_letter_h_rules_no_loops()


def load_square_rules():
    # For now we only use three rules, because we don't work with directed graphs yet
    rules = [
        load_square_rule1(),
        load_square_rule2(),
        load_square_rule3(),
    ]

    return rules


def load_square_rule1():
    lhs = Graph()
    lhs.add_vertices([0, 1])
    lhs.add_edge("a", 0, 1, 90)

    rhs = Graph()
    rhs.add_vertices([0, 1, 2, 3])
    rhs.add_edge("a", 0, 1, 90)
    rhs.add_edge("b", 1, 2, 0)
    rhs.add_edge("a", 2, 3, 90)

    connections = [(0, 0), (1, 3)]

    return Rule(lhs, rhs, connections)


def load_square_rule2():
    lhs = Graph()
    lhs.add_vertices([0, 1])
    lhs.add_edge("b", 0, 1, 0)

    rhs = Graph()
    rhs.add_vertices([0, 1, 2, 3])
    rhs.add_edge("b", 0, 1, 0)
    rhs.add_edge("a", 1, 2, 90)
    rhs.add_edge("b", 2, 3, 0)

    connections = [(0, 0), (1, 3)]

    return Rule(lhs, rhs, connections)


def load_square_rule3():
    lhs = Graph()

    rhs = Graph()
    rhs.add_vertices([0, 1, 2, 3])
    rhs.add_edge("a", 0, 1, 90)
    rhs.add_edge("a", 3, 2, 90)
    rhs.add_edge("b", 1, 2, 0)
    rhs.add_edge("b", 0, 3, 0)

    connections = []

    return Rule(lhs, rhs, connections)


def load_triangle_rules():
    # Only rule for a triangle is the triangle itself
    lhs = Graph()

    rhs = Graph()
    rhs.add_vertices([0, 1, 2])
    rhs.add_edge("a", 0, 1, 0)
    rhs.add_edge("b", 0, 2, 90)
    rhs.add_edge("c", 1, 2, 135)

    connections = []

    rule1 = Rule(lhs, rhs, connections)

    rules = [
        rule1
    ]

    return rules


def load_letter_h_rules():
    lhs1 = Graph()

    rhs1 = Graph()
    rhs1.add_vertices([0, 1])
    rhs1.add_edge("a", 0, 1, 90)

    c1 = []

    rule1 = Rule(lhs1, rhs1, c1)

    lhs2 = Graph()
    lhs2.add_vertices([0, 1, 2, 3])
    lhs2.add_edge("a", 0, 1, 90)
    lhs2.add_edge("a", 2, 3, 90)

    rhs2 = Graph()
    rhs2.add_vertices([0, 1, 2, 3, 4, 5])
    rhs2.add_edge("a", 0, 1, 90)
    rhs2.add_edge("a", 1, 2, 90)
    rhs2.add_edge("b", 1, 4, 0)
    rhs2.add_edge("a", 3, 4, 90)
    rhs2.add_edge("a", 4, 5, 90)

    c2 = [(0, 0), (1, 2), (2, 3), (3, 5)]

    rule2 = Rule(lhs2, rhs2, c2)

    rules = [
        rule1,
        rule2
    ]

    return rules


def load_letter_h_rules_no_loops():
    lhs1 = Graph()

    rhs1 = Graph()
    rhs1.add_vertices([0, 1])
    rhs1.add_edge("a", 0, 1, 90)

    c1 = []

    rule1 = Rule(lhs1, rhs1, c1)

    lhs2 = Graph()
    lhs2.add_vertices([0, 1])
    lhs2.add_edge("a", 0, 1, 90)

    rhs2 = Graph()
    rhs2.add_vertices([0, 1, 2, 3, 4, 5])
    rhs2.add_edge("a", 0, 1, 90)
    rhs2.add_edge("a", 1, 2, 90)
    rhs2.add_edge("b", 1, 4, 0)
    rhs2.add_edge("a", 3, 4, 90)
    rhs2.add_edge("a", 4, 5, 90)

    c2 = [(0, 0), (1, 2)]

    rule2 = Rule(lhs2, rhs2, c2)

    c3 = [(0, 3), (1, 5)]
    rule3 = Rule(lhs2, rhs2, c3)

    rules = [
        rule1,
        rule2,
        rule3
    ]

    return rules


# for rule in load_square_rules():
#     print(rule)
