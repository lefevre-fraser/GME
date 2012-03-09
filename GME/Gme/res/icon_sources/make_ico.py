# python make_ico.py  GME_icon.png  output_10198  output_17534  output_20774

import struct
import os
import sys

class Out(object):
    def __init__(self, output):
        self.output = output
        self.count = 0
    
    def write1(self, v):
        output.write(struct.pack('<B', v))

    def write2(self, v):
        output.write(struct.pack('<H', v))

    def write4(self, v):
        output.write(struct.pack('<L', v))

    def write(self, v):
        output.write(v)

#sizes = ( (0,0), (48,48), (32,32), (16,16) )
sizes = ( (48,48), (32,32), (16,16) )
palettesize = ( 0, 0, 0, 0 )
bpp = ( 32, 32, 32, 24)

def roundup(x):
    import math
    return int(math.ceil(x / 32.0) * 32)

files = []
for (i, f) in enumerate(sys.argv[1:]):
    with open(f, 'rb') as datafile:
        data = datafile.read()
        if data[0:2] == 'BM': # magic number for BMP
            data = data[14:] # sizeof(BITMAPFILEHEADER)
            # TODO: read mask bmp
            # TODO: fix size
            data += struct.pack('b', 0) * roundup(sizes[i][0]) * sizes[i][1]
            data = list(data)
            data[8:12] = struct.pack('<L', struct.unpack('<L', ''.join(data[8:12]))[0] * 2) # offsetof(BITMAPINFOHEADER, biHeight) == 8
            print struct.unpack('<L', ''.join(data[8:12]))
            data = ''.join(data)
        files.append(data)

with open('output.ico', 'wb') as output:
    out = Out(output)
    out.write2(0)
    out.write2(1)
    out.write2(len(files))
    for i in range(len(files)):
        out.write1(sizes[i][0])
        out.write1(sizes[i][1])
        print 'height ' + str(sizes[i][1])
        out.write1(palettesize[i])
        out.write1(0)
        out.write2(1) # FIXME: what is color plane?
        out.write2(bpp[i])
        out.write4(len(files[i]))
        print(len(files[i]))
        print sum((len(file) for file in files[:i]))
        out.write4(6 + 16 * len(files) + sum((len(file) for file in files[:i])))
        
    for file in files:
        out.write(file)


