class Rule:
    def __init__(self, lhs, rhs, connections):
        self.lhs = lhs
        self.rhs = rhs
        self.connections = connections

    def __str__(self):
        output = f"{self.lhs.shorthand()} to: {self.rhs.shorthand()} with connections:"
        for (p1, p2) in self.connections:
            output += f"{str(p1)} -> {str(p2)}"
        return output
