class Rule:
    def __init__(self, lhs, rhs, connections):
        self.lhs = lhs
        self.rhs = rhs
        self.connections = connections

    def is_starter(self):
        return self.lhs.is_empty() or self.rhs.is_empty()

    def get_starter_graph(self):
        # Expects the rule to be a starter rule
        if self.lhs.is_empty():
            return self.rhs
        if self.rhs.is_empty():
            return self.lhs
        return None

    def long_string(self):
        output = f"LHS: {str(self.lhs)} \n to: {str(self.rhs)} with connections:\n"
        for (p1, p2) in self.connections:
            output += f"{str(p1)} -> {str(p2)}, "
        return output

    def __str__(self):
        output = f"{self.lhs.shorthand()} to: {self.rhs.shorthand()} with connections:"
        for (p1, p2) in self.connections:
            output += f"{str(p1)} -> {str(p2)}, "
        return output
