import random
from networkx.algorithms import isomorphism


def has_isomorphic_subgraph(graph1, graph2):
    # Returns true if the first graph has a subgraph that is isomorphic to the second graph
    GM = isomorphism.GraphMatcher(graph1, graph2, edge_match=isomorphism.categorical_edge_match('label', None))
    return GM.subgraph_is_isomorphic()


def get_all_sub_isomorphisms(graph1, graph2):
    # Returns a list of mappings of subgraphs of the first graph that are isomorphic to the second graph
    GM = isomorphism.GraphMatcher(graph1, graph2, edge_match=isomorphism.categorical_edge_match('label', None))
    return list(GM.subgraph_isomorphisms_iter())


def get_amount_of_isomorphisms(rules, graph):
    # Returns a list of amount of isomorphisms per rule
    amount = []
    for rule in rules:
        GM = isomorphism.GraphMatcher(graph.graph, rule.lhs.graph, edge_match=isomorphism.categorical_edge_match('label', None))
        amount.append(len(list(GM.subgraph_isomorphisms_iter())))
    return amount


def get_random_sub_isomorphism(graph1, graph2):
    # Returns random mapping of a subgraph of the first graph that is isomorphic to the second graph
    GM = isomorphism.GraphMatcher(graph1, graph2, edge_match=isomorphism.categorical_edge_match('label', None))
    isomorphisms = list(GM.subgraph_isomorphisms_iter())
    return random.choice(isomorphisms)
