# /// script
# dependencies = [
#   "pillow",
# ]
# ///

"""
this is a minimal jpg/png->xpm converter
so that you can make your pets with almost
any program and convert it to xpm later
"""

from PIL import Image
from typing import Any
import sys
import os
import re


def symbol_from_output(path: str) -> str:
    base = os.path.splitext(os.path.basename(path))[0]
    # e.g., idle_0 -> xpm_idle_0
    clean = re.sub(r"[^a-zA-Z0-9_]", "_", base)
    if not clean:
        clean = "img"
    return f"xpm_{clean}"


def toxpm(input_path):
    output_path = sys.argv[2] if len(sys.argv) >= 3 else "img.xpm"
    symbol = symbol_from_output(output_path)

    image = Image.open(input_path).convert("RGBA")
    image = image.quantize(256).convert("RGBA")  # xpm needs 256colours
    width = image.size[0]
    height = image.size[1]
    pixels: Any = image.load()

    colors = {}
    next_char = 33  # start printable ascii

    def next_symbol():
        nonlocal next_char
        while True:
            char = chr(next_char)
            next_char += 1
            if char in ['"', "'", "\\"]:
                continue
            break
        return char

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

    with open(output_path, "w") as f:
        # writing c
        f.write("/* xpm */\n")
        f.write(f"static const char* {symbol}[] = {{\n")
        f.write(f'"{width} {height} {len(colors)} 1",\n')

        for rgba, sym in colors.items():
            if rgba[3] == 0:
                f.write(f'"{sym} c None",\n')
            else:
                f.write(f'"{sym} c #{rgba[0]:02x}{rgba[1]:02x}{rgba[2]:02x}",\n')

        for y, row in enumerate(pixmap):
            line_end = "," if y < height - 1 else ""
            f.write(f'"{row}"{line_end}\n')

        f.write("};\n")

    print(f"saved xpm: {output_path} (symbol: {symbol})")


if len(sys.argv) < 2:
    print("usage: toxpm.py <input.(jpg/png)> [output.xpm]")
    sys.exit(1)

toxpm(sys.argv[1])
