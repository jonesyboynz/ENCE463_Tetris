#A simple python script that generates a blank image of a given size
#By Simon Jones
#Usage: python3 generate_blank_images.py <width> <height>

import sys

if len(sys.argv) == 3:
	width = int(sys.argv[1])
	height = int(sys.argv[2])
else:
	width = 128
	height = 96

assert(width % 2 == 0)

width = width // 2

print("{", end = '')
for i in range(0, height):
	for j in range(0, width):
		if j != width - 1 or i != height - 1:
			print("0x00, ", end = '')
		else:
			print("0x00", end = '')
	if i != height - 1:
		print("\n", end = '')
print("};", end = '')