import math
import sys
from itertools import combinations

from point import Point

_huge = sys.float_info.max
_tiny = sys.float_info.min


def cross(a, b):
    return round(a.x * b.y - a.y * b.x, 4)


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


def is_in_boundary_box(point):
    left_x = -8
    right_x = 8
    lower_y = -4
    upper_y = 4
    if point.x < left_x or point.x > right_x:
        return False
    if point.y < lower_y or point.y > upper_y:
        return False


def is_in_boundary_circle(point):
    r = 4
    c_x = 0
    c_y = 0
    return math.sqrt((point.x - c_x)**2 + (point.y - c_y)**2) <= r


def is_in_boundary_donut(point):
    r_1 = 4
    r_2 = 8
    c_x = 0
    c_y = 0
    if math.sqrt((point.x - c_x)**2 + (point.y - c_y)**2) < r_1:
        return False
    if math.sqrt((point.x - c_x)**2 + (point.y - c_y)**2) > r_2:
        return False
    return True


def ray_intersects_segment(p, segment):
    (A, B) = segment
    if A.y > B.y:
        A, B = B, A
    if p.y == A.y or p.y == B.y:
        p.y = p.y + 1e-4

    if p.y > B.y or p.y < A.y or p.x > max(A.x, B.x):
        return False

    if p.x < min(A.x, B.x):
        return True

    if abs(A.x - B.x) > _tiny:
        m_red = (B.y - A.y) / float(B.x - A.x)
    else:
        m_red = _huge
    if abs(A.x - p.x) > _tiny:
        m_blue = (p.y - A.y) / float(p.x - A.x)
    else:
        m_blue = _huge
    return m_blue >= m_red


def is_in_boundary_polygon(point):
    # polygon = [Point(-3, -3), Point(-3, 3), Point(3, 3), Point(3, -3)]
    polygon = [Point(-1, -3), Point(-1, 1), Point(-3, 1), Point(-3, 3), Point(3, 3), Point(3, 1), Point(1, 1), Point(1, -3)]
    polygon = [Point(-1, -3), Point(-1, 1), Point(-3, 1), Point(-3, 3), Point(3, 3), Point(3, 1), Point(1, 1), Point(1, -3)]
    count = 0
    for i in range(len(polygon) - 1):
        count += ray_intersects_segment(point, (polygon[i], polygon[i + 1]))
    count += ray_intersects_segment(point, (polygon[-1], polygon[0]))
    if count % 2 == 0:
        return False
    return True


def point_in_boundary_region(point):
    # return is_in_boundary_box(point)
    # return is_in_boundary_circle(point)
    return is_in_boundary_donut(point)
    # return is_in_boundary_polygon(point)


def points_in_boundary_region(points):
    for (_, point) in points:
        if not point_in_boundary_region(point):
            return False
    return True


def validate_proposal(graph, points):
    if not points_in_boundary_region(points):
        return False
    is_planar_drawing = check_planarity(graph, points)
    if not is_planar_drawing:
        return False
    return True
