from isomorphism import *
from graph_drawing import *
from itertools import combinations
import numpy as np


current_probabilities = []
SKEW = 0.01


def apply_n_random_rules(n, rules, graph):
    global current_probabilities
    current_probabilities = [1 / len(rules)] * len(rules)
    for i in range(n):
        print(i)
        apply_random_rule(rules, graph)


def apply_random_rule(rules, graph):
    rule = random.choice(rules)
    apply_rule(rule, graph)


def apply_rule_with_skewed_probability(rules, graph, probabilities):
    index = np.random.choice(len(rules), p=probabilities)
    rule = rules[index]
    apply_rule(rule, graph)
    return index


def apply_random_rule_isomorphisms(rules, graph):
    amounts = get_amount_of_isomorphisms(rules, graph)
    total = sum(amounts)
    probabilities = [amount / total for amount in amounts]
    apply_rule_with_skewed_probability(rules, graph, probabilities)


def apply_rule_with_balanced_probabilities(rules, graph):
    global current_probabilities
    index = apply_rule_with_skewed_probability(rules, graph, current_probabilities)
    for i in range(len(current_probabilities)):
        if index == i:
            current_probabilities[i] -= SKEW
        else:
            current_probabilities[i] += SKEW / (len(current_probabilities) - 1)


def apply_rule_with_self_reinforcing_probabilities(rules, graph):
    global current_probabilities
    index = apply_rule_with_skewed_probability(rules, graph, current_probabilities)
    if current_probabilities[index] >= 0.9:
        return
    for i in range(len(current_probabilities)):
        if index == i:
            current_probabilities[i] += SKEW
        else:
            current_probabilities[i] -= SKEW / (len(current_probabilities) - 1)


def apply_rule(rule, graph):
    if rule.is_starter():
        starter_rule(rule, graph)
        return

    if not has_isomorphic_subgraph(graph.graph, rule.lhs.graph):
        print("No subgraph isomorphism found")
        return

    isomorphism_mapping = get_random_sub_isomorphism(graph.graph, rule.lhs.graph)

    graph.create_copy()

    # Delete edges and nodes in between
    anchors_graph = []
    for graph_node, rule_node in isomorphism_mapping.items():
        if rule_node in [lhs for (lhs, _) in rule.connections]:
            anchors_graph.append(graph_node)
            continue
        graph.remove_vertex(graph_node)

    # Remove edges between graph nodes if they exist
    for n1, n2 in combinations(anchors_graph, 2):
        if graph.graph.has_edge(n1, n2):
            graph.remove_edge(n1, n2)

    # Glue in the new stuff

    # Create id_mapping
    id_mapping = {}
    current_id = graph.get_next_vertex_id()
    # First add connections
    for (left_anchor, right_anchor) in rule.connections:
        id_mapping[right_anchor] = [val for val in isomorphism_mapping if isomorphism_mapping[val] == left_anchor][0]
    # Then generate new ids
    for old_id in rule.rhs.graph:
        if old_id in id_mapping:
            continue
        else:
            id_mapping[old_id] = current_id
            current_id += 1

    # Add nodes
    for old_id, new_id in id_mapping.items():
        if old_id in [rhs for (_, rhs) in rule.connections]:
            continue
        graph.add_vertex(new_id)

    # Add edges
    for old_id in id_mapping:
        for (tail, head) in rule.rhs.get_vertex_edges(old_id):
            # Edges get added twice, but should not really matter
            edge = rule.rhs.get_edge(tail, head)
            graph.add_edge(edge['label'], id_mapping[tail], id_mapping[head], edge['angle'])

    # Find graph drawing
    if not find_graph_drawing(graph):
        graph.restore_copy()


def starter_rule(rule, graph):
    graph.create_copy()

    addition = rule.get_starter_graph()

    # Create new node ids
    id_mapping = {}
    current_id = graph.get_next_vertex_id()
    for old_id in addition.graph:
        id_mapping[old_id] = current_id
        current_id += 1

    # Add new nodes
    for new_id in id_mapping.values():
        graph.add_vertex(new_id)

    # Add new edges
    for old_id in id_mapping:
        for (tail, head) in addition.get_vertex_edges(old_id):
            # Edges get added twice, but should not really matter
            edge = addition.get_edge(tail, head)
            graph.add_edge(edge['label'], id_mapping[tail], id_mapping[head], edge['angle'])

    # find graph drawing
    if not find_graph_drawing(graph):
        graph.restore_copy()
