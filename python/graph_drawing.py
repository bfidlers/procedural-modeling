import numpy as np
from scipy.linalg import lstsq, null_space
from scipy.sparse import coo_matrix
from point import Point
from util import sine, cosine


def find_graph_drawing(graph):
    i = 0
    max_iterations = 20

    while True:
        if i > max_iterations:
            # TODO Do something if it does not work
            break

        points = solve_unset_vertices(graph)
        if len(points) != 0:
            for (vertex, pos) in points:
                graph.set_vertex_position(vertex, pos)
            graph.clear_vertices_to_loosen()
            break

        graph.loosen()
        i += 1


def solve_unset_vertices(graph):
    unset_vertices = graph.get_unset_vertices()

    x_variables = {}
    y_variables = {}

    row = []
    col = []
    data = []
    b = []

    row_nb = 0
    col_nb = 0

    for vertex in unset_vertices:
        x_variables[vertex] = col_nb
        col_nb += 1
        y_variables[vertex] = col_nb
        col_nb += 1
        for head, edge_data in graph.graph.adj[vertex].items():

            col_l = col_nb
            col_nb += 1

            if graph.vertex_is_set(head):
                # Add x equation
                row.append(row_nb); col.append(x_variables[vertex]); data.append(1)
                row.append(row_nb); col.append(col_l); data.append(-cosine(edge_data['angle']))
                b.append(graph.vertex_pos(head).x)
                row_nb += 1
                # Add y equation
                row.append(row_nb); col.append(y_variables[vertex]); data.append(1)
                row.append(row_nb); col.append(col_l); data.append(-sine(edge_data['angle']))
                b.append(graph.vertex_pos(head).y)
                row_nb += 1

            # If head is found in x_variable, that vertex is already processed, and we can use it
            # If not we can just skip it, and it's constraint will be added in the other direction
            elif head in x_variables:
                # Add x equation
                row.append(row_nb); col.append(x_variables[vertex]); data.append(1)
                row.append(row_nb); col.append(x_variables[head]); data.append(-1)
                row.append(row_nb); col.append(col_l); data.append(-cosine(edge_data['angle']))
                b.append(0)
                row_nb += 1
                # Add y equation
                row.append(row_nb); col.append(y_variables[vertex]); data.append(1)
                row.append(row_nb); col.append(y_variables[head]); data.append(-1)
                row.append(row_nb); col.append(col_l); data.append(-sine(edge_data['angle']))
                b.append(0)
                row_nb += 1

    # create matrix
    A = coo_matrix((np.array(data), (np.array(row), np.array(col))), shape=(row_nb, col_nb)).toarray()
    rankA = np.linalg.matrix_rank(A)
    rankAb = np.linalg.matrix_rank(np.concatenate((A, np.array([b]).T), axis=1))

    if rankA < rankAb:
        # Overconstrained
        print("overconstrained")
        return []

    sol, _, _, _ = lstsq(A, b)

    if rankA == rankAb == col_nb:
        # Only one result
        print("only one solution")
        return [(v, Point(sol[x_variables[v]], sol[y_variables[v]])) for v in unset_vertices]

    base_nullspace = null_space(A)
    (_, n) = base_nullspace.shape

    # Create random sample -> This should loop
    z = np.random.rand(n, 1)
    sample = np.array([sol]).T + (base_nullspace @ z)

    # TODO check sample
    # repeat if necessary

    # TODO should we round?
    return [(v, Point(sample[x_variables[v]], sample[y_variables[v]])) for v in unset_vertices]

