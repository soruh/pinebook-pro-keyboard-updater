#!/usr/bin/env python
import sys
import os
from intelhex import IntelHex
import usb1

CTRL_OUT = usb1.ENDPOINT_OUT | usb1.REQUEST_TYPE_CLASS | usb1.RECIPIENT_INTERFACE
MAX_BINLEN = 14*1024

def open_usb(vid, pid, iface):
    with usb1.USBContext() as context:
        print(">>> Trying to open VID:%04x PID:%04x...\n" % vid&0xffff, pid&0xffff);
        devh = context.openByVendorIDAndProductID(0x258a, 0x001e,
                                                  skip_on_error=True)
        if handle is None: raise Exception(">>> Device not found\n")

        if devh.kernelDriverActive(iface):
            printf(">>> Kernel Driver Active\n");
            devh.detachKernelDriver(iface)

        devh.claimInterface(iface):
        # this is wrog b/c context will close libusb prematurely
        return devh

def switch_to_boot_mode():
    print("[*] Opening in user mode...")
    for _ in range(3):
        try:
            devh = open_usb(0x258a, 0x001e, 1)
            #devh = open_usb(0x258a, 0x001f, 1)
            #devh = open_usb(0x258a, 0x000d, 1)
            break
        except Exception as e:
            print(e)
            sleep(0.5)

    if devh is None:
        raise Exception(">>> Failed to open in user mode")

  print("[*] Sending command to switch to boot mode...")

  dataOut = bytearray([0x05, 0x75] + [0x00]*4)
  devh.controlWrite(CTRL_OUT, usb1.REQUEST_SET_CONFIGURATION, 0x0305, 1,
                    dataOut, timeout=1000)

  print("[*] Command send")

def open_boot_mode():
  print("[*] Opening in boot mode\n")
  for _ in range(20):
        try:
            devh = open_usb(0x0603, 0x1020, 0)
            break
        except Exception as e:
            print(e)
            sleep(0.1)

  if devh is None:
      raise Exception(">>> Failed to open in boot mode\n")

  return devh

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
    hex_data = read_hexdata(hex_path)
    switch_to_boot_mode()
    open_boot_mode()

    reportData = bytearray([0x5, 0x45, 0x45, 0x45, 0x45, 0x45])

    print("[*] Erasing flash")
    devh.controlWrite(CTRL_OUT, usb1.REQUEST_SET_CONFIGURATION, 0x0305, 0,
                      reportData, timeout=100)

    sleep(2)

    print("[*] Writing firmware...")
    for _ in range(5):
        try:
            write_bulk(hex_data)
            break
        except Exception as e:
            print(e)
    
    print("[*] Reading back firmware...")
    for _ in range(5):
        try:
            read_hex = read_bulk()
            break
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
    reset_device()

    print("[*] Finished succesfully!")
    close_usb()

def usage():
    print("usage: {} path/to/keyboard/firmware.hex".format(sys.argv[0]))
    sys.exit(1)

if __name__ == '__main__':
    print("DO NOT USE!!! This is an untested work in progress...")
    return

    if len(sys.argv) != 2: usage()
    if not os.path.isfile(sys.argv[1]): usage()
    flash_kb(sys.argv[1])
    
