

def find_graph_drawing(graph):
    i = 0
    max_iterations = 20

    while True:
        # TODO Do something if it does not work
        if i > max_iterations:
            break

        points = solve_unset_vertices(graph)
        if len(points) != 0:
            for (vertex, pos) in points:
                graph.set_vertex_position(vertex, pos)
            break

        graph.loosen()
        i += 1


def solve_unset_vertices(graph):
    # TODO add linear algebra logic
    # get unset vertices

    # create equations

    # create equations

    # create matrix

    # generate sample -> this should loop
    # get a matrix solution
    # if over constrained
    return []
    # get base of nullspace of matrix
    # get random sample
    # check sample
    # repeat if necessary

    # return vertex position mapping

