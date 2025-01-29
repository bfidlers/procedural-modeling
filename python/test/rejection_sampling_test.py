from point import Point
from rejection_sampling import *


def test_intersection():
    a = Point(-1, 0)
    b = Point(0, 1)
    c = Point(0, 0)
    d = Point(0, 0)
    e = Point(0, -1)
    f = Point(1, 0)

    print("Intersects: ", intersects((a, f), (b, e)))
    print("Corner touch: ", intersects((a, c), (b, d)))
    print("Extends: ", intersects((a, c), (d, f)))
    print("Overlaps: ", intersects((a, f), (c, f)))


test_intersection()