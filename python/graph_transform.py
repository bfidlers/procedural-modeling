from isomorphism import *
from itertools import combinations


# TODO we probably want to make a copy somewhere if the transform does not work ...
def apply_random_rule(rules, graph):
    rule = random.choice(rules)
    apply_rule(rule, graph)


# TODO in theory rules need to be applicable from right to left as well
def apply_rule(rule, graph):
    if not has_isomorphic_subgraph(graph.graph, rule.lhs.graph):
        return

    isomorphism_mapping = get_random_sub_isomorphism(graph.graph, rule.lhs.graph)

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
    current_id = graph.vertex_size()
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
