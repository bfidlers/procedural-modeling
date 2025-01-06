import pyglet
import datetime
from pyglet.window import key, mouse
from pyglet.gl import *
import numpy as np


from camera import Camera
from input import *
from graph_transform import apply_random_rule
from test.rules_test import compute_rules

window_w = 1000
window_h = 1000
FOV_Y = 60.0
NEAR_CLIP = 0.1
FAR_CLIP = 100.0


window = pyglet.window.Window(width=window_w, height=window_h, caption="Procedural Modelling Demo", resizable=True)
camera = Camera(np.array([0.0, 0.0, 0.0]), 10.0)

g = create_empty_graph()
# g = create_square()
# g = create_cube()
# g = create_triangle()
# g = create_letter_h()
# rules = compute_rules("square")
# rules = compute_rules("rectangle")
# rules = compute_rules("triangle")
# rules = compute_rules("letter_h")
rules = compute_rules("letter_h_no_loops")


@window.event
def on_key_press(symbol, modifiers):
    if symbol == key.N:
        print('The key "N" was pressed')
        apply_random_rule(rules, g)
    elif symbol == key.S:
        save_image()
    elif symbol == key.PLUS:
        camera.zoom(-1)
    elif symbol == key.MINUS:
        camera.zoom(1)
    elif symbol == key.UP:
        camera.pan(0, 0.1, 0.0)
    elif symbol == key.DOWN:
        camera.pan(0, -0.1, 0.0)
    elif symbol == key.RIGHT:
        camera.pan(0.1, 0, 0.0)
    elif symbol == key.LEFT:
        camera.pan(-0.1, 0, 0.0)
    else:
        print('Another key, with keycode {} was pressed'.format(symbol))


@window.event
def on_draw():
    window.clear()
    camera.look_at()
    g.draw()


@window.event
def on_mouse_drag(x, y, dx, dy, buttons, modifiers):
    dxn = dx / window_w
    dyn = dy / window_h

    if buttons & mouse.LEFT:
        camera.rotate(dxn, dyn)
    if buttons & mouse.RIGHT:
        camera.pan(-dxn, -dyn, 0.0)


@window.event
def on_mouse_scroll(x, y, scroll_x, scroll_y):
    camera.zoom(scroll_y)


@window.event
def on_resize(width, height):
    global window_w, window_h
    window_w = width
    window_h = height
    glViewport(0, 0, width*2, height*2)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(FOV_Y, width / float(height), NEAR_CLIP, FAR_CLIP)
    glMatrixMode(GL_MODELVIEW)
    return pyglet.event.EVENT_HANDLED


def save_image():
    print('Saving image')
    current_time = datetime.datetime.now().isoformat(timespec="seconds")
    buffer = pyglet.image.get_buffer_manager().get_color_buffer()
    buffer.save('Output/output_{}.png'.format(current_time))


pyglet.app.run()
