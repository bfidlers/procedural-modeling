from vertex import Vertex
from edge import Edge, inverse_edge_id
from pyglet.gl import *


class Graph:
    def __init__(self):
        # TODO Find decent queue to use in python
        # self.verticesToLoosen
        self.vertices = {}
        self.edges = {}
        self.adjList = {}

    def vertex_size(self):
        return len(self.vertices)

    def edge_size(self):
        return len(self.edges) / 2

    def add_vertex(self, id, point=None):
        if id in self.vertices:
            return
        self.vertices[id] = Vertex(id, point)
        self.adjList[id] = []

    def add_edge(self, id, tail, head):
        if tail not in self.vertices:
            return
        if head not in self.vertices:
            return

        # TODO check this id, confusion between edge id and edge label
        inverse = id + "'"
        e1 = Edge.create_from_vertices(id, self.vertices[tail], self.vertices[head])
        e2 = Edge.create_from_vertices(inverse, self.vertices[head], self.vertices[tail])

        self.edges[id] = e1
        self.edges[inverse] = e2

        self.adjList[tail].append(id)
        self.adjList[head].append(inverse)

    def add_single_edge(self, id, tail, head, angle):
        if tail not in self.vertices:
            return
        if head not in self.vertices:
            return

        edge = Edge(id, tail, head, angle)
        self.edges[id] = edge
        self.adjList[tail].append(id)

    def remove_vertex(self, id):
        edges = self.adjList[id]
        for edge in edges:
            # Remove inverse edges
            self.remove_single_edge(inverse_edge_id(edge))

        self.vertices.pop(id)
        self.adjList.pop(id)

    def remove_single_edge(self, id):
        edge = self.edges[id]
        self.adjList[edge.tail].remove(id)

    def remove_edge(self, id):
        self.remove_single_edge(id)
        self.remove_single_edge(inverse_edge_id(id))

    def get_vertex_edge_ids(self, vertex):
        return self.adjList[vertex]

    def get_vertex_edges(self, vertex):
        edges = []
        for edge in self.adjList[vertex]:
            edges.append(self.edges[edge])
        return edges

    def draw(self):
        for edges in self.adjList.values():
            for i in edges:
                edge = self.edges[i]
                if edge.is_inverse():
                    continue
                first = self.vertices[edge.tail]
                second = self.vertices[edge.head]

                glBegin(GL_LINES)
                glVertex3f(first.pos.x, first.pos.y, first.pos.z)
                glVertex3f(second.pos.x, second.pos.y, second.pos.z)
                glEnd()

    def shorthand(self):
        output = "g: "
        for edges in self.adjList.values():
            for i in edges:
                edge = self.edges[i]
                if edge.is_inverse():
                    continue
                output += edge.shorthand() + ", "

    def __str__(self):
        output = "Graph containing the following:\n"
        for vertex_id, edges in self.adjList.items():
            output += str(self.vertices.get(vertex_id))
            output += ", with edges: \n"
            for edge in edges:
                output += str(self.edges[edge]) + "\n"
        return output
