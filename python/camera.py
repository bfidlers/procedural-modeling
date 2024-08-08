import math
import numpy as np
from pyglet.gl import *


PI_2 = 0.5 * math.pi

DEFAULT_EULER_YAW = 0
DEFAULT_EULER_PITCH = PI_2 - 0.001


class Camera:
    def __init__(self, center, r0):
        self.center = center
        self.r0 = r0
        self.r = self.r0
        self.yaw = DEFAULT_EULER_YAW
        self.pitch = DEFAULT_EULER_PITCH
        self.zoom_value = 0

        self.front = np.empty(3, dtype=float)
        self.left = np.empty(3, dtype=float)
        self.up = np.empty(3, dtype=float)
        self.position = np.empty(3, dtype=float)

    def look_at(self):
        unit_x = np.array([1.0, 0.0, 0.0])
        unit_y = np.array([0.0, 1.0, 0.0])
        unit_z = np.array([0.0, 0.0, 1.0])

        # Calculate the front vector
        self.front = - (np.cos(self.pitch) * np.cos(self.yaw) * unit_x +
                        np.cos(self.pitch) * np.sin(self.yaw) * unit_y +
                        np.sin(self.pitch) * unit_z)
        self.front /= np.linalg.norm(self.front)

        # Calculate the left vector
        self.left = np.cross(unit_z, self.front)
        self.left /= np.linalg.norm(self.left)

        # Calculate the up vector
        self.up = np.cross(self.front, self.left)
        self.up /= np.linalg.norm(self.up)

        # Calculate the camera position
        self.position = self.center - self.r * self.front

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        gluLookAt(self.position[0], self.position[1], self.position[2],
                  self.center[0], self.center[1], self.center[2],
                  0.0, 0.0, 1.0)

    def rotate(self, right_input, up_input):
        self.yaw += PI_2 * right_input
        self.pitch += PI_2 * up_input

        # Normalize yaw to [-pi, pi[
        # self.yaw = normalizeAngleMinusPiPi(yaw_);

        # Clamp pitch to ]-pi/2, pi/2[
        PITCH_MIN = -PI_2 + 0.001
        PITCH_MAX = PI_2 - 0.001
        self.pitch = min(max(self.pitch, PITCH_MIN), PITCH_MAX)
        self.look_at()

    def pan(self, right_input, up_input, front_input):
        self.center += (
                -right_input * self.r * self.left +
                up_input * self.r * self.up +
                front_input * self.r * self.front
        )
        self.look_at()

    def zoom(self, zoom_input):
        self.zoom_value += zoom_input
        self.r = self.r0 * 1.1 ** self.zoom_value
        self.look_at()

