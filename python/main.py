import pyglet
import datetime
from pyglet.window import key
from pyglet.gl import *
import numpy as np

from camera import Camera

window_w = 800
window_h = 600
FOV_Y = 60.0
NEAR_CLIP = 0.1
FAR_CLIP = 100.0


window = pyglet.window.Window(width=window_w, height=window_h, caption="Procedural Modelling Demo")
camera = Camera(np.array([0.0, 0.0, 0.0]), 10.0)


vertices = [-1, -1, 0,
            -1, 1, 0,
            1, 1, 0,
            1, -1, 0]


@window.event
def on_key_press(symbol, modifiers):
    if symbol == key.N:
        print('The key "N" was pressed')
    elif symbol == key.S:
        save_image()
    else:
        print('Another key, with keycode {} was pressed'.format(symbol))


@window.event
def on_draw():
    window.clear()
    camera.look_at()
    pyglet.graphics.draw(len(vertices) // 3, GL_POLYGON,
                         ('v3f', vertices)
                         )


@window.event
def on_mouse_drag(x, y, dx, dy, buttons, modifiers):
    dxn = dx / window_w
    dyn = dy / window_h

    camera.rotate(dxn, dyn)


@window.event
def on_resize(width, height):
    global window_w, window_h
    window_w = width
    window_h = height
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(FOV_Y, width / float(height), NEAR_CLIP, FAR_CLIP)
    return pyglet.event.EVENT_HANDLED


def save_image():
    print('Saving image')
    current_time = datetime.datetime.now().isoformat(timespec="seconds")
    buffer = pyglet.image.get_buffer_manager().get_color_buffer()
    buffer.save('Output/output_{}.png'.format(current_time))


pyglet.app.run()
