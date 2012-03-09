import sys
import struct


#with open(r'C:\Users\ksmyth\git\GMESRC\GME\Gme\res\GME.ico', 'rb') as input:
with open(sys.argv[1], 'rb') as input:
    input.read(4)
    n = struct.unpack('<h', input.read(2))[0]
    data = []
    for i in range(n):
        datum = {}
        datum['width'] = struct.unpack('<B', input.read(1))[0]
        datum['height'] = struct.unpack('<B', input.read(1))[0]
        datum['colors'] = struct.unpack('<B', input.read(1))[0]
        input.read(1)
        datum['planes'] = struct.unpack('<h', input.read(2))[0]
        datum['bpp'] = struct.unpack('<h', input.read(2))[0]
        datum['size'] = struct.unpack('<l', input.read(4))[0]
        datum['offset'] = struct.unpack('<l', input.read(4))[0]
        print datum['size'],datum['offset']
        print datum
        data.append(type('Data', (object,), datum))

    for datum in data:
        input.seek(datum.offset)
        imagedata = input.read(datum.size)
        info = str(datum.offset) + "_" + str(datum.width) + "x" + str(datum.height) + "_" + str(datum.bpp) + "bpp"
#        with open('output_' + info, 'wb') as output:
#            output.write(imagedata)
        if imagedata[1:4] == 'PNG':
            with open('output_' + info + ".png", 'wb') as output:
                output.write(imagedata)
        else:
            with open('output_' + info + ".bmp", 'wb') as output:
#typedef struct tagBITMAPFILEHEADER {
#  WORD bfType; 
                output.write('BM')
#  DWORD bfSize; 
                output.write(struct.pack('<L', len(imagedata) + 14))
#  WORD bfReserved1; 
                output.write(struct.pack('<H', 0))
#  WORD bfReserved2; 
                output.write(struct.pack('<H', 0))
#  DWORD bfOffBits; 
#} BITMAPFILEHEADER; 
                #output.write(struct.pack('<L', 140))
                output.write(struct.pack('<L', 54))
#  LONG  biHeight;
#} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
                output.write(imagedata)
                # AND/XOR transparency business (this kills the alpha mask)
                output.seek(0x16) # sizeof(BITMAPFILEHEADER) + offsetof(BITMAPINFOHEADER, biHeight)
                output.write(struct.pack('<L', datum.height))

            with open('output_' + info + "_mask.bmp", 'wb') as output:
#typedef struct tagBITMAPFILEHEADER {
#  WORD bfType; 
                output.write('BM')
#  DWORD bfSize; 
                output.write(struct.pack('<L', 14 + 40 + 8 + datum.width*datum.height/8 + datum.height*2))
#  WORD bfReserved1; 
                output.write(struct.pack('<H', 0))
#  WORD bfReserved2; 
                output.write(struct.pack('<H', 0))
#  DWORD bfOffBits; 
#} BITMAPFILEHEADER; 
                #output.write(struct.pack('<L', 140))
                output.write(struct.pack('<L', 54))
                #output.write(struct.pack('<L', 62))
#  LONG  biHeight;
#} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
#typedef struct tagBITMAPINFOHEADER {
#  DWORD biSize;
                output.write(struct.pack('<L', 40))
#  LONG  biWidth;
                output.write(struct.pack('<L', datum.width))
#  LONG  biHeight;
                output.write(struct.pack('<L', datum.height))
#  WORD  biPlanes;
                output.write(struct.pack('<H', 1))
#  WORD  biBitCount;
                output.write(struct.pack('<H', 1))
#  DWORD biCompression;
                output.write(struct.pack('<L', 0))
#  DWORD biSizeImage;
                output.write(struct.pack('<L', 0))
#  LONG  biXPelsPerMeter;
                output.write(struct.pack('<L', 0))
#  LONG  biYPelsPerMeter;
                output.write(struct.pack('<L', 0))
#  DWORD biClrUsed;
                output.write(struct.pack('<L', 2))
#  DWORD biClrImportant;
                output.write(struct.pack('<L', 2))
#} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
                output.write(struct.pack('<L', 0x00000000))
                output.write(struct.pack('<L', 0x00FFFFFF))
                #output.write(imagedata[-(datum.width*datum.height/8):])
                #output.write(imagedata[-(datum.width*datum.height/8):])
                for i in range(datum.height, 0, -1):
                    pad = 0
                    #  The bits in the array are packed together, but each scan line must be padded with zeros to end on a LONG data-type boundary
                    if datum.width % 32 != 0: pad = 16
                    start, end = -((datum.width+pad)*i/8), -((datum.width+pad)*(i-1)/8)
                    if end == 0: end = len(imagedata)
                    print "%d %d %d" % (datum.width, start, end)
                    output.write(imagedata[start:end])
                    #if datum.width % 32 != 0:
                    #    output.write(struct.pack('H', 0))
                # AND/XOR transparency business (this kills the alpha mask)
                #output.seek(0x16) # sizeof(BITMAPFILEHEADER) + offsetof(BITMAPINFOHEADER, biHeight)
                #output.write(struct.pack('<L', datum.height))



