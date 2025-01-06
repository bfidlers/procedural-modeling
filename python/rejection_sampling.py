from itertools import combinations


def cross(a, b):
    return a.x * b.y - a.y * b.x


def orient(a, b, c):
    return cross(b - a, c - a)


def segments_overlap(seg1, seg2):
    a, b = seg1
    c, d = seg2
    if a == c:
        return (b - a).equal_sign(d - c)
    if a == d:
        return (b - a).equal_sign(c - d)
    if b == c:
        return (a - b).equal_sign(d - c)
    if b == d:
        return (a - b).equal_sign(c - d)
    return False


def intersects(line1, line2):
    (a, b) = line1
    (c, d) = line2

    oa = orient(c, d, a)
    ob = orient(c, d, b)
    oc = orient(a, b, c)
    od = orient(a, b, d)

    if oa * ob < 0 and oc * od < 0:
        return True

    if oa == 0 and ob == 0 and oc == 0 and od == 0:
        return segments_overlap(line1, line2)

    return False


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
