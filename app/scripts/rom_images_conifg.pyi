import sys
import os
import struct

#include "stm32_mem.h"

FLASH_MEM_ADDR = MEMLAYOUT_FLASH_MEM_ADDR
FLASH_MEM_SIZE = MEMLAYOUT_FLASH_MEM_SIZE
FLASH_MEM_END  = MEMLAYOUT_FLASH_MEM_END

IBOOT_MEM_ADDR = MEMLAYOUT_IBOOT_MEM_ADDR
IBOOT_MEM_SIZE = MEMLAYOUT_IBOOT_MEM_SIZE
IBOOT_MEM_END  = MEMLAYOUT_IBOOT_MEM_END

ROM_INFO_MEM_ADDR = MEMLAYOUT_ROM_INFO_MEM_ADDR
ROM_INFO_MEM_SIZE = MEMLAYOUT_ROM_INFO_MEM_SIZE
ROM_INFO_MEM_END  = MEMLAYOUT_ROM_INFO_MEM_END

XBOOT_MEM_ADDR = MEMLAYOUT_XBOOT_MEM_ADDR
XBOOT_MEM_SIZE = MEMLAYOUT_XBOOT_MEM_SIZE
XBOOT_MEM_END  = MEMLAYOUT_XBOOT_MEM_END

UBOOT_MEM_ADDR = MEMLAYOUT_UBOOT_MEM_ADDR
UBOOT_MEM_SIZE = MEMLAYOUT_UBOOT_MEM_SIZE
UBOOT_MEM_END  = MEMLAYOUT_UBOOT_MEM_END

APP_MEM_ADDR = MEMLAYOUT_APP_MEM_ADDR
APP_MEM_SIZE = MEMLAYOUT_APP_MEM_SIZE
APP_MEM_END  = MEMLAYOUT_APP_MEM_END

FS_MEM_ADDR = MEMLAYOUT_FS_MEM_ADDR
FS_MEM_END  = MEMLAYOUT_FS_MEM_END
FS_MEM_SIZE = FS_MEM_END - FS_MEM_ADDR

rom_type = {
    "fireware"	: [ 0, 1024],
    "image" 	: [STM32_IMAGE_HEAD_SIZE, 1024],
    "fs_image"  : [ 0,   32],
}

partition_entry_index = {
    "iboot"      : 0,
    "rom_info"   : 1,
    "xboot"      : 2,
    "uboot"      : 3,
    "app"        : 4,
    "fs_image"   : 5,
}

rom_info = [
    {"name": "iboot", 		"type":"fireware",	"address":IBOOT_MEM_ADDR,		"max size":IBOOT_MEM_SIZE	},
    {"name": "rom_info",	"type":"fireware",	"address":ROM_INFO_MEM_ADDR,	"max size":ROM_INFO_MEM_SIZE},
    {"name": "xboot", 		"type":"image",		"address":XBOOT_MEM_ADDR,		"max size":XBOOT_MEM_SIZE	},
    {"name": "uboot", 		"type":"image",		"address":UBOOT_MEM_ADDR,		"max size":UBOOT_MEM_SIZE	},
    {"name": "app",   		"type":"image",		"address":APP_MEM_ADDR,			"max size":APP_MEM_SIZE		},
    {"name": "fs_image",  	"type":"fs_image", 	"address":FS_MEM_ADDR,			"max size":FS_MEM_SIZE		},
]

def rom_partition_info(name):
	return rom_info[partition_entry_index[name]]

def rom_partition_info_format(name, size):
	partition_address = rom_partition_info(name)["address"]
	partition_max_size = rom_partition_info(name)["max size"]
	structdata =  struct.pack("<III", partition_address, size, partition_max_size)
	return b"".join(structdata)

def update_rom_partition_info(iboot_size = 0, xboot_size = 0, uboot_size = 0, app_size = 0, fs_image_size = 0):
	buff  = rom_partition_info_format("iboot", iboot_size)
	buff += rom_partition_info_format("xboot", xboot_size)
	buff += rom_partition_info_format("uboot", uboot_size)
	buff += rom_partition_info_format("app", app_size)
	buff += rom_partition_info_format("fs_image", fs_image_size)
	return buff

def show_mem_usage(name_index, buff_size):
	index = partition_entry_index[name_index]
	name = rom_info[partition_entry_index[name_index]]["name"]
	address_in_rom = rom_info[partition_entry_index[name_index]]["address"]
	usage = (buff_size * 100)/rom_info[partition_entry_index[name_index]]["max size"]
	print "[{0}][{1:>9}] address: 0x{02:>08X},size: {3:>7d}({4:>4d}KB)/{5}% ".format(index, name, address_in_rom, buff_size, buff_size >> 10, usage)

def show_rom_info(iboot_size = 0, rom_info_size = 0, xboot_size = 0, uboot_size = 0, app_size = 0, fs_image_size = 0):
	print "----------------------------------------------------------------"
	print "[RomBin Packer]"
	show_mem_usage("iboot", iboot_size)
	show_mem_usage("rom_info", rom_info_size)
	show_mem_usage("xboot", xboot_size)
	show_mem_usage("uboot", uboot_size)
	show_mem_usage("app", app_size)
	show_mem_usage("fs_image", fs_image_size)
	print "----------------------------------------------------------------"

