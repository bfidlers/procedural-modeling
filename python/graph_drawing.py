import numpy as np
from scipy.linalg import lstsq, null_space
from scipy.sparse import coo_matrix
from point import Point
from util import sine, cosine

THRESHOLD = 1e-10

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

        print("loosening graph")
        graph.loosen()
        i += 1


def solve_unset_vertices(graph):
    unset_vertices = graph.get_unset_vertices()

    x_variables = {}
    y_variables = {}
    l_variables = []

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

            if graph.vertex_is_set(head):
                l_variables.append(col_nb)
                # Add x equation
                row.append(row_nb); col.append(x_variables[vertex]); data.append(1)
                row.append(row_nb); col.append(col_nb); data.append(-cosine(edge_data['angle']))
                b.append(graph.vertex_pos(head).x)
                row_nb += 1
                # Add y equation
                row.append(row_nb); col.append(y_variables[vertex]); data.append(1)
                row.append(row_nb); col.append(col_nb); data.append(-sine(edge_data['angle']))
                b.append(graph.vertex_pos(head).y)
                row_nb += 1
                col_nb += 1

            # If head is found in x_variable, that vertex is already processed, and we can use it
            # If not we can just skip it, and it's constraint will be added in the other direction
            elif head in x_variables:
                l_variables.append(col_nb)
                # Add x equation
                row.append(row_nb); col.append(x_variables[vertex]); data.append(1)
                row.append(row_nb); col.append(x_variables[head]); data.append(-1)
                row.append(row_nb); col.append(col_nb); data.append(-cosine(edge_data['angle']))
                b.append(0)
                row_nb += 1
                # Add y equation
                row.append(row_nb); col.append(y_variables[vertex]); data.append(1)
                row.append(row_nb); col.append(y_variables[head]); data.append(-1)
                row.append(row_nb); col.append(col_nb); data.append(-sine(edge_data['angle']))
                b.append(0)
                row_nb += 1
                col_nb += 1

    # create matrix
    A = coo_matrix((np.array(data), (np.array(row), np.array(col))), shape=(row_nb, col_nb)).toarray()
    rankA = np.linalg.matrix_rank(A)
    rankAb = np.linalg.matrix_rank(np.concatenate((A, np.array([b]).T), axis=1))

    if rankA < rankAb:
        # Overconstrained
        print("overconstrained")
        return []

    sol, _, _, _ = lstsq(A, b)
    sol[np.abs(sol) < THRESHOLD] = 0

    if rankA == rankAb == col_nb:
        # Only one result
        print("only one solution")
        return [(v, Point(sol[x_variables[v]][0], sol[y_variables[v]][0])) for v in unset_vertices]

    base_nullspace = null_space(A)
    base_nullspace[np.abs(base_nullspace) < THRESHOLD] = 0
    (_, n) = base_nullspace.shape

    # Create random sample -> This should loop
    z = np.random.rand(n, 1)
    sample = np.array([sol]).T + (base_nullspace @ z)

    contains_length_zero = any(sample[length] == 0 for length in l_variables)
    if contains_length_zero:
        return []
    # TODO check sample
    # repeat if necessary

    # TODO should we round?
    return [(v, Point(sample[x_variables[v]][0], sample[y_variables[v]][0])) for v in unset_vertices]

