import networkx as nx
from networkx.algorithms import isomorphism


def get_base_square():
    G = nx.Graph()
    G.add_nodes_from([1, 2, 3, 4])
    G.add_edges_from([(1, 2, {"label": "a"}), (2, 3, {"label": "b"}), (3, 4, {"label": "a"}), (4, 1, {"label": "b"})])
    return G


def simple_square_isomorphism():
    # Check isomorphism two squares without the categorical check
    G1 = get_base_square()

    G2 = nx.Graph()
    G2.add_nodes_from([4, 2, 1, 3])
    G2.add_edges_from([(4, 2, {"label": "a"}), (2, 1, {"label": "b"}), (1, 3, {"label": "a"}), (3, 4, {"label": "b"})])

    GM = isomorphism.GraphMatcher(G1, G2)
    print("Testing simple square isomorphism")
    print("GM is isomorphic", GM.is_isomorphic())
    print("GM subgraph is isomorphic", GM.subgraph_is_isomorphic())


def simple_line_isomorphism():
    # Check isomorphism line and square without the categorical check
    G1 = get_base_square()

    G2 = nx.Graph()
    G2.add_nodes_from([5, 6])
    G2.add_edges_from([(5, 6, {"label": "a"})])

    GM1 = isomorphism.GraphMatcher(G1, G2)
    GM2 = isomorphism.GraphMatcher(G2, G1)
    print("Testing simple line isomorphism")
    print("GM1 is isomorphic", GM1.is_isomorphic())
    print("GM1 subgraph is isomorphic", GM1.subgraph_is_isomorphic())
    print("GM2 is isomorphic", GM2.is_isomorphic())
    print("GM2 subgraph is isomorphic", GM2.subgraph_is_isomorphic())


def simple_corner_isomorphism():
    # Check isomorphism line and square without the categorical check
    G1 = get_base_square()

    G2 = nx.Graph()
    G2.add_nodes_from([5, 6, 7])
    G2.add_edges_from([(5, 6, {"label": "a"}), (6, 7, {"label": "b"})])

    GM1 = isomorphism.GraphMatcher(G1, G2)
    GM2 = isomorphism.GraphMatcher(G2, G1)
    print("Testing simple corner isomorphism")
    print("GM1 is isomorphic", GM1.is_isomorphic())
    print("GM1 subgraph is isomorphic", GM1.subgraph_is_isomorphic())
    print("GM2 is isomorphic", GM2.is_isomorphic())
    # Be aware subgraph of first graph is isomorphic to the second graph!
    print("GM2 subgraph is isomorphic", GM2.subgraph_is_isomorphic())
    for subgraph in GM1.subgraph_isomorphisms_iter():
        print("subgraph of GM1", subgraph)


def square_isomorphism_with_labels():
    # Matching with custom conditions
    # 1 They do have the same edge labels - check isomorphism

    G1 = get_base_square()
    G2 = nx.Graph()
    G2.add_nodes_from([4, 2, 1, 3])
    G2.add_edges_from([(4, 2, {"label": "a"}), (2, 1, {"label": "b"}), (1, 3, {"label": "a"}), (3, 4, {"label": "b"})])

    GM1 = isomorphism.GraphMatcher(G1, G2, edge_match=isomorphism.categorical_edge_match('label', None))
    print("Testing square isomorphism with matching labels")
    print("GM1 is isomorphic, with edge labels", GM1.is_isomorphic())
    print(list(GM1.subgraph_isomorphisms_iter()))
    # WARNING the matching can't be directional if we just use edge labels, we might need to use a directional graph with
    #  half-edges instead 2 They don't have the same edge labels - check isomorphism

    G3 = nx.Graph()
    G3.add_nodes_from([4, 2, 1, 3])
    G3.add_edges_from([(4, 2, {"label": "c"}), (2, 1, {"label": "b"}), (1, 3, {"label": "c"}), (3, 4, {"label": "b"})])

    # 2 They don't have the same edge labels - check isomorphism
    GM2 = isomorphism.GraphMatcher(G1, G3, edge_match=isomorphism.categorical_edge_match('label', None))
    print("Testing square isomorphism without matching labels")
    print("GM2 is isomorphic, with edge labels", GM2.is_isomorphic())


def subgraph_isomorphism_with_labels():
    # They do have the same edge labels - check subgraph isomorphism
    G1 = get_base_square()

    G2 = nx.Graph()
    G2.add_nodes_from([5, 6, 7])
    G2.add_edges_from([(5, 6, {"label": "a"}), (6, 7, {"label": "b"})])

    GM = isomorphism.GraphMatcher(G1, G2, edge_match=isomorphism.categorical_edge_match('label', None))
    print("Testing subgraph isomorphism with matching labels")
    print("GM is isomorphic, with edge labels", GM.is_isomorphic())
    print("GM is subgraph isomorphic, with edge labels", GM.subgraph_is_isomorphic())
    print(list(GM.subgraph_isomorphisms_iter()))
    # This gives three results while we actually only need 1, might not be an issue since there is a lot of symmetry,
    # but we will need to look into this


def multiple_edges_with_same_label():
    # Check what happens when we have multiple edges with the same label in a graph, will it match both?
    G1 = nx.Graph()
    G1.add_nodes_from([1, 2, 3, 4, 5, 6])
    G1.add_edges_from([
        (1, 2, {"label": "a"}),
        (6, 3, {"label": "a"}),
        (5, 4, {"label": "a"}),
        (2, 3, {"label": "b"}),
        (3, 4, {"label": "b"}),
        (1, 6, {"label": "b"}),
        (6, 5, {"label": "b"})
    ])

    G2 = nx.Graph()
    G2.add_nodes_from([1, 2, 3, 4])
    G2.add_edges_from([
        (1, 2, {"label": "a"}),
        (4, 3, {"label": "a"}),
        (2, 3, {"label": "b"}),
        (1, 4, {"label": "b"})
    ])

    G3 = nx.Graph()
    G3.add_nodes_from([7, 8, 9, 10])
    G3.add_edges_from([
        (8, 7, {"label": "b"}),
        (7, 10, {"label": "b"}),
        (7, 9, {"label": "a"}),
    ])

    GM1 = isomorphism.GraphMatcher(G1, G3, edge_match=isomorphism.categorical_edge_match('label', None))
    print("Testing subgraph isomorphism with vertex with multiple edges with same label vs valid graph")
    print("GM is isomorphic, with edge labels", GM1.is_isomorphic())
    print("GM is subgraph isomorphic, with edge labels", GM1.subgraph_is_isomorphic())
    print(list(GM1.subgraph_isomorphisms_iter()))

    GM2 = isomorphism.GraphMatcher(G2, G3, edge_match=isomorphism.categorical_edge_match('label', None))
    print("Testing subgraph isomorphism with vertex with multiple edges with same label vs square")
    print("GM is isomorphic, with edge labels", GM2.is_isomorphic())
    print("GM is subgraph isomorphic, with edge labels", GM2.subgraph_is_isomorphic())
    print(list(GM2.subgraph_isomorphisms_iter()))
    # Okay nice this works as we want it to


def poc_directed_graph():
    # Proof of concept of directed graph where labels are different depending on direction
    G1 = nx.DiGraph()
    G1.add_nodes_from([1, 2, 3, 4])
    G1.add_edges_from([
        (1, 2, {"label": "+a"}),
        (2, 1, {"label": "-a"}),
        (4, 3, {"label": "+a"}),
        (3, 4, {"label": "-a"}),
        (2, 3, {"label": "+b"}),
        (3, 2, {"label": "-b"}),
        (1, 4, {"label": "+b"}),
        (4, 1, {"label": "-b"})
    ])

    # Would be nice if the inverse were not needed, but without this is no complete isomorphism I guess
    G2 = nx.DiGraph()
    G2.add_nodes_from([5, 6, 7])
    G2.add_edges_from([
        (6, 5, {"label": "-a"}),
        (6, 7, {"label": "+b"}),
        (5, 6, {"label": "+a"}),
        (7, 6, {"label": "-b"})
    ])

    GM = isomorphism.GraphMatcher(G1, G2, edge_match=isomorphism.categorical_edge_match('label', None))
    print("Testing subgraph isomorphism with matching directional labels")
    print("GM is isomorphic, with directional edge labels", GM.is_isomorphic())
    print("GM is subgraph isomorphic, with directional edge labels", GM.subgraph_is_isomorphic())
    print(list(GM.subgraph_isomorphisms_iter()))
    # This gives us the one result we are looking for, but seems a hassle, so we'll first try without it


# simple_line_isomorphism()
# simple_corner_isomorphism()
# simple_square_isomorphism()
# square_isomorphism_with_labels()
# subgraph_isomorphism_with_labels()
# multiple_edges_with_same_label()
poc_directed_graph()
