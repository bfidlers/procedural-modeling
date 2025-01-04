from pyglet.gl import *
import networkx as nx


class Graph:
    def __init__(self):
        self.graph = nx.Graph()

    def vertex_size(self):
        return self.graph.order()

    def edge_size(self):
        return self.graph.size()

    def add_vertex(self, id, point=None):
        if id in self.graph:
            return
        self.graph.add_node(id, pos=point)

    def add_edge(self, label, tail, head):
        self.graph.add_edge(tail, head, label=label, angle=0)

    def remove_vertex(self, id):
        self.graph.remove_node(id)

    def remove_edge(self, tail, head):
        self.graph.remove_edge(tail, head)

    def get_vertex_edges(self, vertex):
        return self.graph.edges(vertex)

    def draw(self):
        seen = set()
        for (tail, head) in self.graph.edges:
            if (head, tail) in seen:
                continue
            seen.add((tail, head))

            pos1 = self.graph.nodes[tail]["pos"]
            pos2 = self.graph.nodes[head]["pos"]

            glBegin(GL_LINES)
            glVertex3f(pos1.x, pos1.y, pos1.z)
            glVertex3f(pos2.x, pos2.y, pos2.z)
            glEnd()

    def vertex_string(self, id):
        return f"Vertex {id}: {self.graph.nodes[id]['pos']}"

    def edge_string(self, tail, head):
        edge = self.graph[tail][head]
        print(edge)
        return f"Edge: {edge['label']}: {tail} -> {head}, {edge['angle']}°"

    def edge_shorthand(self, tail, head):
        edge = self.graph[tail][head]
        return f"{tail} -> {head} {edge['angle']}°"

    def shorthand(self):
        output = "g: "
        seen = set()
        for (tail, head) in self.graph.edges:
            if (head, tail) in seen:
                continue
            seen.add((tail, head))
            output += self.edge_shorthand(tail, head) + ", "
        return output

    def __str__(self):
        output = "Graph containing the following:\n"
        for vertex in self.graph:
            output += self.vertex_string(vertex)
            output += ", with edges: \n"
            print(vertex)
            print(self.get_vertex_edges(vertex))
            for (tail, head) in self.get_vertex_edges(vertex):
                print(tail, head)
                output += self.edge_string(tail, head) + "\n"
        return output
