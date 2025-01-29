import networkx as nx

from graph import Graph
from isomorphism import has_isomorphic_subgraph
from rule import Rule

MAX_DEPTH = 10


def construct_grammar(input_graph):
    rules = []

    hierarchy = []

    edges = input_graph.get_distinct_edges()

    hierarchy.append(edges)
    primitives = input_graph.split_in_primitives()
    hierarchy.append(primitives)

    for i in range(2, MAX_DEPTH):
        new_layer = add_layer(primitives, hierarchy)
        filtered_layer = []
        for graph in new_layer:
            match = find_boundary_match(graph.graph_boundary_string, hierarchy)
            if match:
                connections = find_connections(graph, match)
                r = Rule(graph, match, connections)
                rules.append(r)
                continue
            reducible = is_reducible(graph, rules)
            if reducible:
                continue
            filtered_layer.append(graph)
        hierarchy.append(filtered_layer)

    return rules


def add_layer(primitives, hierarchy):
    current_layer = hierarchy[-1]
    new_layer = []
    for graph in current_layer:
        loop_glue_half_edge = can_loop_glue(graph)
        if loop_glue_half_edge:
            new_graph = loop_glue(graph, loop_glue_half_edge)
            new_layer.append(new_graph)
        for p in primitives:
            branch_glue_half_edge = can_branch_glue(graph, p)
            if branch_glue_half_edge:
                new_graph = branch_glue(graph, p, branch_glue_half_edge)
                new_layer.append(new_graph)
    return new_layer


def find_boundary_match(graph_boundary_string, hierarchy):
    for layer in hierarchy:
        for graph in layer:
            if graph.graph_boundary_string == graph_boundary_string:
                return graph
    return find_boundary_matching_group(graph_boundary_string, hierarchy)


def find_boundary_matching_group(graph_boundary_string, hierarchy):
    matches = []
    for layer in hierarchy:
        for graph in layer:
            if graph.graph_boundary_string in graph_boundary_string:
                s = graph_boundary_string.split(graph.graph_boundary_string)
                matches.append(graph)
                for substring in s:
                    match = find_boundary_match(substring, hierarchy)
                    if not match:
                        return False
                    matches.append(match)
    matches_graph = Graph()
    matches_graph.graph = nx.compose_all(matches)
    return matches_graph


def is_reducible(graph, rules):
    for rule in rules:
        # Right hand side of the rule is always simpler, so this guarantees that the graph is reducible
        if has_isomorphic_subgraph(graph.graph, rule.lhs.graph):
            return True
    return False


def can_loop_glue(graph):
    return graph.contains_opposite_half_edges()


def loop_glue(graph, label):
    new_graph = Graph()
    new_graph.graph = graph.get_graph_copy()
    new_graph.glue_half_edge(label)
    return new_graph


def can_branch_glue(g1, g2):
    for x in g1.graph_boundary_string:
        if x == "'" or x == 'v' or x == '^':
            continue
        opposite_half_edge = g2.contains_half_edge(f"{x}'")
        if opposite_half_edge:
            return opposite_half_edge
    return False


def branch_glue(g1, g2, label):
    new_graph = Graph()
    new_graph.graph = nx.compose_all([g1.graph, g2.graph])
    new_graph.glue_half_edge(label)
    return new_graph


def find_connections(g1, g2):
    half_edges1 = g1.get_half_edges()
    half_edges2 = g2.get_half_edges()
    connections = []

    if len(half_edges1) != len(half_edges2):
        raise Exception('The number of halve edges of two sides of a rule should match, which is not the case')

    for (label1, node1) in half_edges1:
        for (label2, node2) in half_edges2:
            if label1 == label2:
                connections.append((node1, node2))
