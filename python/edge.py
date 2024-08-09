import math


def inverse_edge_id(id):
    if id.endswith("'"):
        return id.substr(0, id.size() - 1)
    else:
        return id + "'"


class Edge:
    def __init__(self, id, tail, head, angle):
        self.id = id
        self.tail = tail
        self.head = head
        self.angle = angle

    @staticmethod
    def create_from_vertices(id, v1, v2):
        angle = round(math.atan2(v2.pos.y - v1.pos.y, v2.pos.x - v1.pos.x) * 180 / math.pi)
        return Edge(id, v1.id, v2.id, angle)

    def __eq__(self, other):
        if isinstance(other, Edge):
            return self.id == other.id
        return False

    def shorthand(self):
        return f"{self.tail} -> {self.head} {self.angle}°"

    def __str__(self):
        return f"Edge: {self.id}: {self.tail} -> {self.head}, {self.angle}°"

    def is_inverse(self):
        return self.id.endswith("'")
