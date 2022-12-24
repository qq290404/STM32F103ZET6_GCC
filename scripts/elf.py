import os
import sys
import struct

def print_string_hex(data):
    print(" ".join(['%02X' % ord(i) for i in data]))

def to_string_hex(data):
    return b' '.join(['%02X' % ord(i) for i in data])


class ELF_HEAD:
    __EI_MAG = 0
    __EI_CLASS = 4
    __EI_DATA = 5
    __EI_VERSION = 6
    __EI_OSABI  = 7
    __EI_ABIVERSION = 8
    __EI_PAD = 9
    __EI_NIDENT = 16

    __ET_NONE = 0
    __ET_REL = 1
    __ET_EXEC = 2
    __ET_DYN = 3
    __ET_CORE = 4

    __EM_NONE = 0
    __EM_M32 = 1
    __EM_SPARC = 2
    __EM_386 = 3
    __EM_68K = 4
    __EM_88K = 5
    __EM_486 = 6 # Perhaps disused
    __EM_860 = 7
    __EM_MIPS = 8 # MIPS R3000 (officially, big-endian only)
    __EM_MIPS_RS3_LE = 10 # MIPS R3000 little-endian
    __EM_MIPS_RS4_BE = 10 # MIPS R4000 big-endian
    __EM_PARISC = 15 # HPPA
    __EM_SPARC32PLUS = 18 # Sun's "v8plus"
    __EM_PPC = 20 # PowerPC
    __EM_PPC64 = 21 # PowerPC64
    __EM_SPU = 23	# Cell BE SPU
    __EM_ARM = 40	# ARM 32 bit
    __EM_SH = 42	# SuperH */
    __EM_SPARCV9 = 43 # SPARC v9 64-bit
    __EM_H8_300 = 46 # Renesas H8/300
    __EM_IA_64 = 50 # HP/Intel IA-64
    __EM_X86_64 = 62 # AMD x86-64
    __EM_S390 = 22	# IBM S/390
    __EM_CRIS = 76	# Axis Communications 32-bit embedded processor
    __EM_M32R  = 88	# Renesas M32R
    __EM_MN10300 = 89 # Panasonic/MEI MN10300, AM33
    __EM_OPENRISC = 92 # OpenRISC 32-bit embedded processor
    __EM_BLACKFIN = 106 # ADI Blackfin Processor
    __EM_ALTERA_NIOS2 = 113	# Altera Nios II soft-core processor
    __EM_TI_C6000 = 140	# TI C6X DSPs
    __EM_AARCH64 = 183 # ARM 64 bit
    __EM_TILEPRO = 188 # Tilera TILEPro
    __EM_MICROBLAZE = 189 # Xilinx MicroBlaze
    __EM_TILEGX = 191 # Tilera TILE-Gx
    __EM_BPF = 247 # Linux BPF - in-kernel virtual machine
    __EM_FRV = 0x5441 # Fujitsu FR-V
    __EM_AVR32 = 0x18ad # Atmel AVR32
    __EM_ALPHA = 0x9026
    __EM_CYGNUS_M32R = 0x9041
    __EM_S390_OLD = 0xA390
    __EM_CYGNUS_MN10300 = 0xBEEF

    def __init__(self, fp):
        self.fp = fp
        self.header = self.__parse_header()

    def __parse_header(self):
        hdr = {}
        hdr['e_ident'] = b''.join(struct.unpack('4sccccc6sc', self.fp.read(16)))
        if self.__parse_head_ident(hdr['e_ident'], self.__EI_MAG) == False:
            print "your input file not a elf file"
            return {}
        hdr['e_type'], hdr['e_machine'] = struct.unpack('<hh', self.fp.read(4))
        hdr['e_version'], = struct.unpack('<I', self.fp.read(4))
        hdr['e_entry'], = struct.unpack('<I', self.fp.read(4))
        hdr['e_phoff'], hdr['e_shoff'] = struct.unpack('<II', self.fp.read(8))
        hdr['e_flags'], hdr['e_ehsize'] = struct.unpack('<Ih', self.fp.read(6))
        hdr['e_phentsize'], hdr['e_phnum'] = struct.unpack('<hh', self.fp.read(4))
        hdr['e_shentsize'], hdr['e_shnum'] = struct.unpack('<hh', self.fp.read(4))
        hdr['e_shtrndx'], = struct.unpack('<h', self.fp.read(2))
        return hdr

    def __check_elf_head_magic(self, head):
        if (head[0] != b'\x7f' or head[1] != b'\x45' or head[2] != b'\x4c' or head[3] != b'\x46'):
            return False
        return True

    def __check_elf_head_class(self, head):
        if head[4] == b'\x01':
            return 'ELF32'
        return 'ELF64'

    def __check_elf_head_data(self, head):
        if head[5] == b'\x01':
            return "2's complement,little endian"
        return "2's complement,big endian"

    def __check_elf_head_version(self, head):
        return ''.join(['%d' % ord(head[6]), '(current)'])

    def __check_elf_head_osabi(self, head):
        if head[7] == b'\x00':
            return "UNIX - System V"
        elif head[7] == b'\x01':
            return "HP-Ux operating system"
        elif head[7] == b'\xff':
            return "Standalone (embedded) application"
        return "unkonw OSABI"

    def __check_elf_head_abi_version(self, head):
         return ''.join(['%d' % ord(head[8])])

    def __parse_head_ident(self, head, name):
        if name == self.__EI_MAG:
            return self.__check_elf_head_magic(head)
        elif name == self.__EI_CLASS:
            return self.__check_elf_head_class(head)
        elif name == self.__EI_DATA:
            return self.__check_elf_head_data(head)
        elif name == self.__EI_VERSION:
            return self.__check_elf_head_version(head)
        elif name == self.__EI_OSABI:
            return self.__check_elf_head_osabi(head)
        elif name == self.__EI_ABIVERSION:
            return self.__check_elf_head_abi_version(head)
        '''
        elif name == self.__EI_PAD:
        elif name == self.__EI_NIDENT:
        '''
        return "unkonw ident"

    def __parse_head_type(self, name):
        if name == self.__ET_NONE:
            return "No file type"
        elif name == self.__ET_REL:
            return "Relocatable object file"
        elif name == self.__ET_EXEC:
            return "EXEC (Executable file)"
        elif name == self.__ET_DYN:
            return "Shared object file"
        elif name == self.__ET_CORE:
            return "Core file"
        return "unkonw type"

    def __parse_head_machine(self, name):
        if name == self.__EM_ARM:
            return "ARM"
        elif name == self.__EM_X86_64:
            return "AMD X86-64 arrchitecture"
        return "unkonw machine"

    def __parse_head_version(self, head):
        return ''.join(['0x%X' % head])

    def __parse_head_entry(self, head):
        return ''.join(['0x%X' % head])

    def __parse_head_program_offset(self, head):
        return ''.join(['%d (bytes into file)' % head])

    def __parse_head_section_offset(self, head):
        return ''.join(['%d (bytes into file)' % head])

    def __parse_head_flags(self, head):
        return ''.join(['0x%X' % head])

    def __parse_head_size(self, head):
        return ''.join(['%d (bytes)' % head])

    def __parse_head_program_size(self, head):
        return ''.join(['%d (bytes)' % head])

    def __parse_head_program_number(self, head):
        return ''.join(['%d' % head])

    def __parse_head_section_size(self, head):
        return ''.join(['%d (bytes)' % head])

    def __parse_head_section_number(self, head):
        return ''.join(['%d' % head])

    def __parse_head_section_table_index(self, head):
        return ''.join(['%d' % head])

    def Get_Machine_Name(self):
        return self.__parse_head_machine(self.header['e_machine'])

    def PrintHeader(self):
        print "ELF Header:"
        print "Magic:   " + to_string_hex(self.header['e_ident'])
        print "Class:                             " + self.__parse_head_ident(self.header['e_ident'], self.__EI_CLASS)
        print "Data:                              " + self.__parse_head_ident(self.header['e_ident'], self.__EI_DATA)
        print "Version:                           " + self.__parse_head_ident(self.header['e_ident'], self.__EI_VERSION)
        print "OS/ABI:                            " + self.__parse_head_ident(self.header['e_ident'], self.__EI_OSABI)
        print "ABI Version:                       " + self.__parse_head_ident(self.header['e_ident'], self.__EI_ABIVERSION)
        print "Type:                              " + self.__parse_head_type(self.header['e_type'])
        print "Mchine:                            " + self.__parse_head_machine(self.header['e_machine'])
        print "Version:                           " + self.__parse_head_version(self.header['e_version'])
        print "Entry point address:               " + self.__parse_head_entry(self.header['e_entry'])
        print "Start of program headers:          " + self.__parse_head_program_offset(self.header['e_phoff'])
        print "Start of section headers:          " + self.__parse_head_section_offset(self.header['e_shoff'])
        print "Flags:                             " + self.__parse_head_flags(self.header['e_flags'])
        print "Size of this header:               " + self.__parse_head_size(self.header['e_ehsize'])
        print "Size of program headers:           " + self.__parse_head_program_size(self.header['e_phentsize'])
        print "Number of program headers:         " + self.__parse_head_program_number(self.header['e_phnum'])
        print "Size of section headers:           " + self.__parse_head_section_size(self.header['e_shentsize'])
        print "Number of section headers:         " + self.__parse_head_section_number(self.header['e_shnum'])
        print "Section header string table index: " + self.__parse_head_section_table_index(self.header['e_shtrndx'])
        '''
        print "ELF Header:"
        print "Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00"
        print "Class:                             ELF32"
        print "Data:                              2's complement, little endian"
        print "Version:                           1 (current)"
        print "OS/ABI:                            UNIX - System V"
        print "ABI Version:                       0"
        print "Type: a                             EXEC (Executable file)"
        print "Mchine:                           ARM"
        print "Version:                           0x1"
        print "Entry point address:               0x8001079"
        print "Start of program headers:          52 (bytes into file)"
        print "Start of section headers:          416500 (bytes into file)"
        print "Flags:                             0x5000200, Version5 EABI, soft-float ABI"
        print "Size of this header:               52 (bytes)"
        print "Size of program headers:           32 (bytes)"
        print "Number of program headers:         3"
        print "Size of section headers:           40 (bytes)"
        print "Number of section headers:         22"
        print "Section header string table index: 21"
        '''
if __name__ == '__main__':
    file = "F:/code/stm32/STM32F103ZET6/out/iboot/iboot.elf"
    with open(file, 'rb') as fp:
        elf_head = ELF_HEAD(fp)
        elf_head.PrintHeader()
