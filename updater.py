#!/usr/bin/env python
import sys
import os
from collections import namedtuple
from intelhex import IntelHex
import usb1

CTRL_OUT = usb1.ENDPOINT_OUT | usb1.REQUEST_TYPE_CLASS | usb1.RECIPIENT_INTERFACE
CTRL_IN = usb1.ENDPOINT_IN | usb1.REQUEST_TYPE_CLASS | usb1.RECIPIENT_INTERFACE
MAX_BINLEN = 14*1024
BLOCK_SIZE = 2048
USB_MODE_CONFIG = namedtuple('USB_MODE_CONFIG', ['vid', 'pid', 'iface'])
USER_MODE_CONFIG = USB_MODE_CONFIG(vid=0x258a, pid=0x001e, iface=1)
# may also need to try product IDs 0x001f and 0x000d
BOOT_MODE_CONFIG = USB_MODE_CONFIG(vid=0x0603, pid=0x1020, iface=0)
 
class DeviceNotFoundError(Exception):
    pass

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

def write_block_start(devh, length):
  print(">>> USB: write_block_start (length={})".format(length))

  transfer = bytearray([
      0x05, # report id
      0x57,
      0x00,
      0x00,
      length & 0xFF,
      (length >> 8) & 0xFF])

  devh.controlWrite(CTRL_OUT, usb1.REQUEST_SET_CONFIGURATION, 0x0305, 0,
                    transfer, timeout=100)

def write_block(devh, data, offset, length):
  print(">>> USB: write_block (offset={}, length={})".format(offset, length))

  transfer = bytearray([
      0x06, #report id
      0x77]) + data[offset:offset+length]

  devh.controlWrite(CTRL_OUT, usb1.REQUEST_SET_CONFIGURATION, 0x0306, 0,
                    transfer, timeout=2000)

def write_bulk(devh, data):
    write_block_start(devh, len(length))

    # HACK: overwrite first byte (as in original sources)
    first_byte = data[0]
    data[0] = 0

    for offset in range(0, len(data), BLOCK_SIZE):
        write_block(devh, data, offset, BLOCK_SIZE)
        sleep(0.01)

    data[0] = first_byte

    # retry write of first block
    write_block_start(devh, length);
    write_block(devh, data, 0, BLOCK_SIZE);

def read_bulk(devh, length):
    #read_block_start(devh, length);
    print(">>> USB: read_block_start (length={})".format(length))

    transfer = bytearray([
        0x05, # report id
        0x52,
        0x00,
        0x00,
        length & 0xFF,
        (length >> 8) & 0xFF])

    devh.controlWrite(CTRL_OUT, usb1.REQUEST_SET_CONFIGURATION, 0x0305, 0,
                      transfer, timeout=100)

    data = bytearray()

    block_size = 2048
    for offset in range(0, len(data), block_size):
        #read_block(devh, data, offset, block_size);
        print(">>> USB: read_block (offset={}, length={})".format(offset, length))
        data += devh.controlRead(CTRL_IN, usb1.REQUEST_CLEAR_FEATURE, 0x0306, 0,
                                 length, timeout=2000)
        sleep(0.01)

def open_usb(context, vid, pid, iface, attempts=1):
    for _ in range(attempts):
        print(">>> Trying to open VID:0x{:04x} PID:0x{:04x}...".format(
            vid & 0xffff, pid & 0xffff))
        devh = context.openByVendorIDAndProductID(vid, pid, skip_on_error=True)
        sleep(0.5)

        if devh is not None: break

    if devh is None:
            raise DeviceNotFoundError

    if devh.kernelDriverActive(iface):
        print(">>> Kernel Driver Active\n");
        devh.detachKernelDriver(iface)

    devh.claimInterface(iface):
    return devh

def switch_to_boot_mode(context):
    print("[*] Opening in user mode...")
    devh = open_usb(context, USER_MODE_CONFIG.vid, USER_MODE_CONFIG.pid,
                    USER_MODE_CONFIG.iface, attempts=3)

    print("[*] Sending command to switch to boot mode...")
    dataOut = bytearray([0x05, 0x75] + [0x00]*4)
    devh.controlWrite(CTRL_OUT, usb1.REQUEST_SET_CONFIGURATION, 0x0305, 1,
                      dataOut, timeout=1000)
    print("[*] Command send")
    close_usb(devh, USER_MODE_CONFIG.iface)

    print("[*] Opening in boot mode\n")
    devh = open_usb(context, BOOT_MODE_CONFIG.vid, BOOT_MODE_CONFIG.pid,
                    BOOT_MODE_CONFIG.iface, attempts=20)
    return devh

def reset_device(devh):
    data = bytearray([0x05, 0x55, 0x55, 0x55, 0x55, 0x55])
    devh.controlWrite(CTRL_OUT, usb1.REQUEST_SET_CONFIGURATION, 0x0305, 0,
                      data, timeout=100)
    devh.resetDevice()

def close_usb(devh, iface):
    print(">>> release interface")
    devh.releaseInterface(devh, devintf)
    devh.close()

def flash_kb(context, hex_path):
    hex_data = read_hexdata(hex_path)
    devh = switch_to_boot_mode(context)

    reportData = bytearray([0x05, 0x45, 0x45, 0x45, 0x45, 0x45])

    print("[*] Erasing flash")
    devh.controlWrite(CTRL_OUT, usb1.REQUEST_SET_CONFIGURATION, 0x0305, 0,
                      reportData, timeout=100)

    sleep(2)

    print("[*] Writing firmware...")
    for _ in range(5):
        try:
            write_bulk(devh, hex_data)
            break
        except Exception as e:
            print(e)
    
    print("[*] Reading back firmware...")
    for _ in range(5):
        try:
            read_hex = read_bulk(devh, len(hex_data))
            break
        except Exception as e:
            print(e)
    if read_hex is None:
        raise Exception("too many tries")


    print("[*] Comparing firmwares...")
    if hex_data[:0x37fb] != read_hex[0x37fb]:
        print("FATAL ERROR FW does differ")
        for i in range(len(hex_data)):
            if hex_data[i] != read_hex[i]:
                print(">>> 0x{:04x}] {:02x} != {:02x}".format(
                    i, hex_data[i], read_hex[i]))
        raise Exception("FATAL ERROR FW does differ")

    print("[*] Reseting device?")
    reset_device(devh)

    print("[*] Finished succesfully!")
    close_usb(devh, BOOT_MODE_CONFIG.iface)

def usage():
    print("usage: {} path/to/keyboard/firmware.hex".format(sys.argv[0]))
    sys.exit(1)

if __name__ == '__main__':
    print("DO NOT USE!!! This is an untested work in progress...")
    return

    if len(sys.argv) != 2: usage()
    if not os.path.isfile(sys.argv[1]): usage()
    with usb1.USBContext() as context:
        flash_kb(context, sys.argv[1])
    
