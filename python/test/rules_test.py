from graph2 import *
from rule import *


def load_square_rules():
    # For now we only use two rules, because we don't work with directed graphs yet
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
    lhs.add_vertices([0, 1, 2, 3])
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
    lhs.add_vertices([0, 1, 2, 3])
    rhs.add_edge("b", 0, 1, 0)
    rhs.add_edge("a", 1, 2, 90)
    rhs.add_edge("b", 2, 3, 0)

    connections = [(0, 0), (1, 3)]

    return Rule(lhs, rhs, connections)


def load_square_rule3():
    lhs = Graph()

    rhs = Graph()
    lhs.add_vertices([0, 1, 2, 3])
    rhs.add_edge("a", 0, 1, 90)
    rhs.add_edge("a", 3, 2, 90)
    rhs.add_edge("b", 1, 2, 0)
    rhs.add_edge("b", 0, 3, 0)

    connections = []

    return Rule(lhs, rhs, connections)


for rule in load_square_rules():
    print(rule)
