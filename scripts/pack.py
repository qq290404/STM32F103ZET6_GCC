import os
import sys
import argparse

rom_images_conifg_path = ''.join([os.path.dirname(os.path.dirname(os.path.abspath(__file__))), '/app/bin'])
rom_images_conifg_path = rom_images_conifg_path.replace('\\', '/')
sys.path.append(rom_images_conifg_path) 
import rom_images_conifg

arg_list = ['iboot', 'xboot', 'uboot', 'appmain', 'fs_images', 'output']

def read_fireware_buff(bin_name, tag):
    with open(bin_name, 'rb') as fp:
        buff = fp.read()
        size = len(buff)
        max_size = rom_images_conifg.rom_partition_info(tag)["max size"]
        buff += b'\xFF' * (max_size - size)
        return buff, size

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    for arg in arg_list:
        parser.add_argument("-%s"%arg)
    args = vars(parser.parse_args())
    iboot_bin = args['iboot']
    xboot_img = args['xboot']
    uboot_img = args['uboot']
    appmain_img = args['appmain']
    fs_img = args['fs_images']
    output_bin = args['output']

    if os.path.exists(output_bin) == True:
        os.remove(output_bin)
    
    iboot_buff, iboot_size = read_fireware_buff(iboot_bin, "iboot")
    xboot_buff, xboot_size = read_fireware_buff(xboot_img, "xboot")
    uboot_buff, uboot_size = read_fireware_buff(uboot_img, "uboot")
    app_buff, app_size = read_fireware_buff(appmain_img, "app")

    fs_image_buff = 0
    fs_image_size = 0

    rom_info_buff = rom_images_conifg.update_rom_partition_info(iboot_size, xboot_size, uboot_size, app_size, fs_image_size)
    rom_info_size = len(rom_info_buff)
    rom_info_max_size = rom_images_conifg.rom_partition_info("rom_info")["max size"]
    rom_info_buff += b'\xFF' * (rom_info_max_size - rom_info_size)

    rom_images_conifg.show_rom_info(iboot_size, rom_info_size, xboot_size, uboot_size, app_size, fs_image_size)

    with open(output_bin, 'wb+') as fp:
        fp.write(iboot_buff)
        fp.write(rom_info_buff)
        fp.write(xboot_buff)
        fp.write(uboot_buff)
        fp.write(app_buff)
        if fs_image_size != 0:
            fp.write(fs_image_buff)
