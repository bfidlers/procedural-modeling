from itertools import combinations


def cross(a, b):
    return a.x * b.y - a.y * b.x


def orient(a, b, c):
    return cross(b - a, c - a)


def intersects(line1, line2):
    (a, b) = line1
    (c, d) = line2

    if a == c or a == d or b == c or b == d:
        return False

    oa = orient(c, d, a)
    ob = orient(c, d, b)
    oc = orient(a, b, c)
    od = orient(a, b, d)

    return oa * ob < 0 and oc * od < 0


def has_intersections(edges):
    for line1, line2 in combinations(edges, 2):
        if intersects(line1, line2):
            return False
    return True


def check_planarity(graph, points):
    edges = []
    point_dict = dict(points)
    for (head, tail) in graph.graph.edges:
        pos1 = point_dict[head] if head in point_dict else graph.vertex_pos(head)
        pos2 = point_dict[tail] if tail in point_dict else graph.vertex_pos(tail)
        edges.append((pos1, pos2))
    return has_intersections(edges)


def validate_proposal(graph, points):
    is_planar_drawing = check_planarity(graph, points)
    if not is_planar_drawing:
        return False
    return True
