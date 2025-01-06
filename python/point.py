import math


class Point:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z

    def update_pos(self, other):
        self.x = other.x
        self.y = other.y
        self.z = other.z

    def equal_sign(self, other):
        return self.x * other.x >= 0 and self.y * other.y >= 0 and self.z * other.z >= 0

    def __eq__(self, other):
        if isinstance(other, Point):
            return (math.isclose(self.x, other.x, rel_tol=1e-4) and
                    math.isclose(self.y, other.y, rel_tol=1e-4) and
                    math.isclose(self.z, other.z, rel_tol=1e-4))
        return False

    def __add__(self, o):
        return Point(self.x + o.x, self.y + o.y, self.z + o.z)

    def __sub__(self, o):
        return Point(self.x - o.x, self.y - o.y, self.z - o.z)

    def __str__(self):
        return f"({self.x},{self.y},{self.z})"
