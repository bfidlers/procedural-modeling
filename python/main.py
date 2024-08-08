import pyglet
from pyglet.window import key


window = pyglet.window.Window()

label = pyglet.text.Label('Hello, world',
                          font_name='Times New Roman',
                          font_size=36,
                          x=window.width//2, y=window.height//2,
                          anchor_x='center', anchor_y='center')


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
    label.draw()


def save_image():
    print('Saving image')
    buffer = pyglet.image.get_buffer_manager().get_color_buffer()
    buffer.save('Output/test.png')


pyglet.app.run()
