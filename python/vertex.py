class Vertex:
    def __init__(self, id, pos=None):
        self.id = id
        self.pos = pos
        if pos is not None:
            self.hasPosition = True
        else:
            self.hasPosition = False

    def unset(self):
        self.hasPosition = False

    def set_coordinates(self, new_pos):
        self.hasPosition = True
        self.pos.update_pos(new_pos)

    def __str__(self):
        return f"Vertex {self.id}: {self.pos}"
