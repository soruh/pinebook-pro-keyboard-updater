#!/usr/bin/env python
import sys
import os
from intelhex import IntelHex

MAX_BINLEN = 14*1024

def read_hexdata(hex_path):
    ih = IntelHex(hex_path)
    ih.padding = 0x00
    print(len(ih), MAX_BINLEN, ih.start_addr, ih.minaddr(), ih.maxaddr())
    print(ih.segments())
    print(ih[0], ih[1], ih[2])
    #print([x for x in ih[0:2]])
            
    if (ih[1] == 0x38 and ih[2] == 0x00):
        print(">>> Fixing hex file")
        ih[0] = ih[0x37FB]
        ih[1] = ih[0x37FC]
        ih[2] = ih[0x37FD]
        ih[0x37FB] = 0x00;
        ih[0x37FC] = 0x00
        ih[0x37FD] = 0x00
    print(ih[0], ih[1], ih[2])
    return ih.tobinarray(size=MAX_BINLEN)

def flash_kb(hex_path):
    hex = read_hexdata(hex_path)
    #switch_to_boot_mode()


def usage():
    print("usage: {} path/to/keyboard/firmware.hex".format(sys.argv[0]))
    sys.exit(1)

if __name__ == '__main__':
    if len(sys.argv) != 2: usage()
    if not os.path.isfile(sys.argv[1]): usage()
    flash_kb(sys.argv[1])
    
