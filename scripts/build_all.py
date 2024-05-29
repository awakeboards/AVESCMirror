from version import get_branch_commit_num
import os
import glob
import re
import shutil

production = True

if production:
    pcb_versions = ["AVESC23"]
    motor_types = ["AMOTOR", "ASTRO", "VINGA"]
    board_types = ["RV1", "RV3", "RVS", "VINGA", "RVBRABUS"]
    shunt_types = ["SH100", "SH200"]
else:
    pcb_versions = ["AVESC23"]  # ["AVESC23", "AVESC25"]
    motor_types = ["D85L190"]  # ["AMOTOR", "ASTRO", "VINGA", ...]
    board_types = ["GOAT"]  # ["RV1", "RV3", "RVS", "VINGA", "GOAT"]
    shunt_types = ["SH100", "SH200"]  # ["SH100", "SH200"]

# Define invalid combinations
exclusions = [
    r'.*?_\d{4}_RV1_(?!(ASTRO))',
    r'.*?_\d{4}_RV3_(?!(AMOTOR))',
    r'.*?_\d{4}_RVS_(?!(AMOTOR|ASTRO))',
    r'.*?_\d{4}_GOAT_(?!(D85L190))',
    r'.*?_\d{4}_RVBRABUS_(?!(AMOTOR))',
    r'.*?_\d{4}_VINGA_(?!(VINGA))',
]

fw_version = str(get_branch_commit_num())

# clear old files
shutil.rmtree('./build/', ignore_errors=True)


def clean_build_files():
    shutil.rmtree('./build/obj/', ignore_errors=True)
    shutil.rmtree('./build/lst/', ignore_errors=True)
    files = glob.glob('./build/*_ChibiOS.*')
    for f in files:
        os.remove(f)


for pcb_version in pcb_versions:
    for motor_type in motor_types:
        for board_type in board_types:
            for shunt_type in shunt_types:

                # remove build files
                clean_build_files()

                # version name
                version_name = pcb_version + "_" + fw_version + "_" + board_type + "_" + motor_type + "_" + shunt_type

                # check for exclusions
                should_skip = False

                for exclusion in exclusions:
                    pattern = re.compile(exclusion)
                    if pattern.search(version_name):
                        should_skip = True

                if should_skip:
                    continue

                print("Building firmware: " + version_name)

                # start build
                os.system("make -j MTYPE=%s STYPE=%s BTYPE=%s PTYPE=%s VTYPE=%s" % (
                    motor_type, shunt_type, board_type, pcb_version, fw_version))

                # rename binary
                binary = glob.glob('./build/*_ChibiOS.bin')[0]
                os.rename(binary, "./build/VESC_" + version_name + ".bin")

# final build files cleanup
clean_build_files()
