import pyglet
import datetime
from pyglet.window import key
from pyglet.gl import *


window = pyglet.window.Window()

vertices = [200, 200, 0,
            100, 200, 0,
            100, 100, 0,
            200, 100, 0]


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
    pyglet.graphics.draw(len(vertices) // 3, GL_POLYGON,
                         ('v3f', vertices)
                         )


def save_image():
    print('Saving image')
    current_time = datetime.datetime.now().isoformat(timespec="seconds")
    buffer = pyglet.image.get_buffer_manager().get_color_buffer()
    buffer.save('Output/output_{}.png'.format(current_time))


pyglet.app.run()
