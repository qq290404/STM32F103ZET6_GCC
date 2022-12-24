import time
import binascii
import sys
import elf
import struct
import os

MAGIC = 0x27051956

archs = {'invalid':0, 'ARM':1}

image_types = {'invalid':0, 'xboot':1, 'uboot':2, 'appmain':3}

image_mem_alloc = {'magic':4, 'headcrc':4,'time':20,'arch':4,'type':4,'entry':4,'name':24}


def pack_image_from_buffer(input_buf, entry_point=0, arch_type='invalid', image_type='invalid', name=''):
        curtime = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
        structdata = struct.pack("<II20sIII24s", MAGIC, 0, curtime, archs[arch_type], image_types[image_type], entry_point, name)
        headercrc = binascii.crc32(structdata) & sys.maxint
        structdata =  struct.pack("<II20sIII24s", MAGIC, headercrc, curtime, archs[arch_type], image_types[image_type], entry_point, name)
        structdata += b'\xFF' * (0x200 - len(structdata))
        print "----------------------------------------------------------------"
        print "IMAGE Header:"
        print "Magic:                             " , hex(MAGIC)
        print "CRC:                               " , hex(headercrc)
        print "Time:                              " , curtime
        print "Arch:                              " , arch_type
        print "Type:                              " , image_type
        print "Name:                              " , name
        return b"".join([structdata, b''.join(struct.pack('B', ord(x)) for x in input_buf)])

if __name__ == '__main__':
    print "----------------------------------------------------------------"
    input_elf_name = sys.argv[1]
    input_bin_name = sys.argv[2]
    output_image_name = sys.argv[3]

    file_name, extension = os.path.splitext(os.path.basename(input_bin_name))

    with open(input_elf_name, 'rb') as fp:
        elf_head = elf.ELF_HEAD(fp)
        elf_head.PrintHeader()

    with open(input_bin_name, 'rb') as fp:
        buff = fp.read()

    with open(output_image_name, "wb+") as fp:
        fp.write(pack_image_from_buffer(buff, elf_head.header['e_entry'], elf_head.Get_Machine_Name(), file_name, os.path.basename(input_bin_name)))

    print "----------------------------------------------------------------"

