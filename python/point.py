class Point:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z

    def update_pos(self, other):
        self.x = other.x
        self.y = other.y
        self.z = other.z

    def __eq__(self, other):
        if isinstance(other, Point):
            return self.x == other.x and self.y == other.y and self.z == other.z
        return False

    def __add__(self, o):
        return Point(self.x + o.x, self.y + o.y, self.z + o.z)

    def __sub__(self, o):
        return Point(self.x - o.x, self.y - o.y, self.z - o.z)

    def __str__(self):
        return f"({self.x},{self.y},{self.z})"
