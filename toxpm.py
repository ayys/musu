"""
this is a minimal jpg/png->xpm converter
so that you can make your pets with almost
any program and convert it to xpm later
"""

from PIL import Image
from typing import Any
import sys
import os

def toxpm(input_path, output_path=None):
    if output_path == None:
        output_path = input_path + ".xpm"

    image = Image.open(input_path).convert("RGBA")
    image = image.quantize(256).convert("RGBA") # xpm needs 256-colours
    width = image.size[0]
    height = image.size[1]
    pixels: Any = image.load() # type to remove error below

    # unique colours
    colors = {}
    # symbols = []
    next_char = 33  # start printable ascii

    def next_symbol():
        nonlocal next_char
        char = chr(next_char)
        next_char += 1
        if next_char == 92:  # skip \
            next_char += 1
        return char

    # build pixmap and colour table
    pixmap = []
    for y in range(height):
        row = []
        for x in range(width):
            rgba = pixels[x, y]
            if rgba[3] < 128:
                rgba = (0, 0, 0, 0)
            if rgba not in colors:
                colors[rgba] = next_symbol()
            row.append(colors[rgba])
        pixmap.append("".join(row))

    # write xpm to output_path
    with open(output_path, "w") as f:
        f.write("/* XPM */\n")
        f.write("static char *img[] = {\n")
        f.write(f"\"{width} {height} {len(colors)} 1\",\n")

        for rgba, sym in colors.items():
            if rgba[3] == 0:
                f.write(f"\"{sym} c None\",\n")
            else:
                f.write(f"\"{sym} c #{rgba[0]:02x}{rgba[1]:02x}{rgba[2]:02x}\",\n")

        for y, row in enumerate(pixmap):
            line_end = "," if y < height - 1 else ""
            f.write(f"\"{row}\"{line_end}\n")

        f.write("};\n")

    print(f"saved xpm: {output_path}")

# entry
if len(sys.argv) < 2:
    print("usage: toxpm.py <input.(jpg/png)> output.xpm")
    sys.exit(1)

output_path = None
if len(sys.argv) > 2:
    output_path = sys.argv[2]

toxpm(sys.argv[1], output_path)
