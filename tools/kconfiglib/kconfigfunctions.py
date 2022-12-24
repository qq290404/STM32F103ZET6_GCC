'''********************************************************
 * Copyright (c) 2019 by Sunplus Technology Co., Ltd.
 *    ____               __
 *   / __/_ _____  ___  / /_ _____
 *  _\ \/ // / _ \/ _ \/ / // (_-<
 * /___/\_,_/_//_/ .__/_/\_,_/___/
 *              /_/
 * Sunplus Technology Co. 19, Innovation First Road,
 * Science-Based Industrial Park, Hsin-Chu, Taiwan, R.O.C.
 * ------------------------------------------------------
 *
 * Description : Preprocessor user functions defined in Python
 * ------------------------------------------------------
 * Rev  Date          Author(s)      Status & Comments
 * ======================================================
 * 0.1  2019/12/22    nz.lu          initial version
'''
import os, sys
from kconfiglib import Choice, MenuNode

SRCTREE = os.environ.get("srctree")
sys.path.insert(0, os.path.join(SRCTREE))

# $(file_selection, "BOOT_LOGO_FILE", "boot/boot_logo/input", "Select boot logo file in boot_logo/input")


# TODO: access kconf class is betteeeeeeer
def file_selection(kconf, _, var_name, input_file_dir, prompt):
    var_name       = var_name.strip()
    input_file_dir = input_file_dir.strip()
    prompt         = prompt.strip()

    file_ls_tmp = os.listdir(os.path.join(SRCTREE, input_file_dir))

    intput_file_list = list()
    if len(file_ls_tmp) > 0:
        intput_file_list += file_ls_tmp
    intput_file_list += ["None"]

    tmplate = 'choice\n    prompt "%s"\n    default %s\n'%(prompt, var_name+"None")
    for file in intput_file_list:
        tmplate += '    config %s\n bool "%s"\n'%(var_name+file.replace(".", "_"), file)
    tmplate += "endchoice\n"
    tmplate += 'config %s\n string\n'%(var_name)
    for file in intput_file_list:
        tmplate += '    default "%s" if %s\n'%(file, var_name+file.replace(".", "_"))

    with open(os.path.join(SRCTREE, var_name + ".Kconfig"), 'w') as fp:
        fp.write(tmplate)

    return ""



functions = {
  "file_selection": (file_selection, 3, 3),
}

