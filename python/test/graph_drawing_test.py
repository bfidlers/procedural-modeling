from graph_drawing import find_graph_drawing
from graph_test import create_square
from point import Point

import numpy as np
from numpy.linalg import matrix_rank
from scipy.linalg import lstsq, null_space, solve


def set_unset_vertices():
    g = create_square()
    print(g)
    g.unset_vertex(1)
    g.unset_vertex(2)
    print(g)

    print(g.get_unset_vertices())
    print(g.vertices_to_loosen)

    g.loosen()
    print(g.get_unset_vertices())
    print(g.vertices_to_loosen)
    print(g)

    g.set_vertex_position(1, Point(1, 2, 3))
    print(g.get_unset_vertices())
    print(g)


def print_some_matrix_stuff(A, b):
    print("Rank A:", matrix_rank(A))
    print("Rank A|b:", matrix_rank(np.concatenate((A, b.T), axis=1)))
    sol, res, rnk, s = lstsq(A, b.T)
    print(sol.T, res, rnk, s)
    base_nullspace = null_space(A)
    print(base_nullspace)
    print(base_nullspace.shape)


def test_matrix_with_one_solution():
    A = np.array([[1, 1, -1], [0, 1, -5], [0, 0, 1]])
    b = np.array([[5, 8, -1]])
    print("Matrix with one solution")
    print_some_matrix_stuff(A, b)


def test_matrix_with_no_solution():
    A = np.array([[1, 1, 1], [0, 1, -3], [2, 1, 5]])
    b = np.array([[2, 1, 0]])
    # x = solve(A, b)
    print("Matrix with no solution")
    print_some_matrix_stuff(A, b)


def test_matrix_with_infinite_solution():
    A = np.array([[-3, -5, 36], [-1, 0, 7], [1, 1, -10]])
    b = np.array([[10, 5, -4]])
    print("Matrix with infinite solutions")
    print_some_matrix_stuff(A, b)


def random():
    A1 = np.array([[1, 1, -1], [0, 1, -5], [0, 0, 1]])
    b1 = np.array([5, 8, -1])
    result = solve(A1, b1)
    print(result)
    print(result[1])

    A2 = np.array([[-3, -5, 36], [-1, 0, 7], [1, 1, -10]])
    b2 = np.array([10, 5, -4])
    sol, _, _, _ = lstsq(A2, b2)
    print(sol)
    print(sol[1])


def find_missing_vertex_square():
    g = create_square()
    g.unset_vertex(0)
    # g.unset_vertex(3)

    print(g)

    find_graph_drawing(g)
    print(g)


def find_two_missing_vertices_square():
    g = create_square()
    g.unset_vertex(2)
    g.unset_vertex(3)

    print(g)

    find_graph_drawing(g)
    print(g)


def find_positions_square():
    g = create_square()
    g.unset_vertex(0)
    g.unset_vertex(1)
    g.unset_vertex(2)
    g.unset_vertex(3)

    print(g)

    find_graph_drawing(g)
    print(g)


# set_unset_vertices()
# test_matrix_with_one_solution()
# test_matrix_with_no_solution()
# test_matrix_with_infinite_solution()
# random()
# find_missing_vertex_square()
# find_two_missing_vertices_square()
find_positions_square()
