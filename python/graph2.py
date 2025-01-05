from pyglet.gl import *
import networkx as nx
import math
from collections import deque


class Graph:
    def __init__(self):
        self.graph = nx.Graph()
        self.vertices_to_loosen = deque()

    def clear_vertices_to_loosen(self):
        self.vertices_to_loosen.clear()

    def vertex_size(self):
        return self.graph.order()

    def edge_size(self):
        return self.graph.size()

    def add_vertex(self, id, point=None):
        if id in self.graph:
            return
        self.graph.add_node(id, pos=point)

    def add_vertices(self, vertices):
        if len(vertices) == 0:
            return
        if type(vertices[0]) is tuple:
            self.graph.add_nodes_from(vertices)
        else:
            self.graph.add_nodes_from(vertices, pos=None)

    def vertex_pos(self, vertex):
        return self.graph.nodes()[vertex]['pos']

    def vertex_is_set(self, vertex):
        return self.graph.nodes()[vertex]['pos'] is not None

    def unset_vertex(self, vertex):
        self.graph.nodes()[vertex]['pos'] = None
        self.mark_vertex_neighbours(vertex)

    def set_vertex_position(self, vertex, pos):
        self.graph.nodes()[vertex]['pos'] = pos

    def get_unset_vertices(self):
        return [v for v, data in self.graph.nodes(data=True) if data['pos'] is None]

    def loosen(self):
        if len(self.vertices_to_loosen) == 0:
            unset = self.get_unset_vertices()
            if len(unset) == 0:
                print("WARNING: all vertices are set")
                return
            for vertex in unset:
                self.mark_vertex_neighbours(vertex)

        if len(self.vertices_to_loosen) == 0:
            print("WARNING: No extra vertices to unset")
            return

        vertex_to_loosen = self.vertices_to_loosen.popleft()
        if self.vertex_is_set(vertex_to_loosen):
            self.unset_vertex(vertex_to_loosen)

    def mark_vertex_neighbours(self, vertex):
        # Mark vertex neighbours to be loosened next
        # TODO probably better to use graph.neighbours(vertex)
        for (tail, head) in self.get_vertex_edges(vertex):
            if tail != vertex and self.vertex_is_set(tail):
                self.vertices_to_loosen.append(tail)
            elif head != vertex and self.vertex_is_set(head):
                self.vertices_to_loosen.append(head)

    def add_edge(self, label, tail, head, angle=None):
        if angle is None:
            pos1 = self.graph.nodes[tail]["pos"]
            pos2 = self.graph.nodes[head]["pos"]
            angle = round(math.atan2(pos2.y - pos1.y, pos2.x - pos1.x) * 180 / math.pi)
        # TODO right now we only use positive angles, because the edges don't have a direction
        self.graph.add_edge(tail, head, label=label, angle=abs(angle % 180))

    def add_edges(self, edges):
        # Edges needs to contain tuples with form (label, tail, head)
        parsed_edges = []
        for (label, tail, head) in edges:
            pos1 = self.graph.nodes[tail]["pos"]
            pos2 = self.graph.nodes[head]["pos"]
            angle = round(math.atan2(pos2.y - pos1.y, pos2.x - pos1.x) * 180 / math.pi)
            angle2 = abs(angle % 180)
            parsed_edges.append((tail, head, {'label': label, 'angle': angle2}))
        self.graph.add_edges_from(parsed_edges)

    def add_edges_without_parsing(self, edges):
        self.graph.add_edges_from(edges)

    def remove_vertex(self, id):
        self.graph.remove_node(id)

    def get_edge(self, tail, head):
        return self.graph[tail][head]

    def remove_edge(self, tail, head):
        self.graph.remove_edge(tail, head)

    def get_vertex_edges(self, vertex):
        return self.graph.edges(vertex)

    def get_vertex_edges_with_data(self, vertex):
        return self.graph.edges(vertex).data()

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
            for (tail, head) in self.get_vertex_edges(vertex):
                output += self.edge_string(tail, head) + "\n"
        return output
