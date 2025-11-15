from pymacro import pywinmacro as pw

location = pw.move_mouse((1333, 809))
pw.click(location)
pw.mouse_downscroll(5000)