from version import get_branch_commit_num
import os
import glob
import re
import shutil

production = True

if production:
    pcb_versions = ["AVESC23"]
    motor_types = ["AMOTOR", "ASTRO", "VINGA", "AMOTORV3"]
    board_types = ["RV3", "RVS", "VINGA", "RVEXPLORE", "RVULTIMATE"]
    shunt_types = ["SH100", "SH200"]
else:
    pcb_versions = ["AVESC23"]  # ["AVESC23", "AVESC25"]
    motor_types = ["AMOTORV3"]  # ["AMOTOR", "ASTRO", "VINGA", ...]
    board_types = ["RVEXPLORE"]  # ["RV1", "RV3", "RVS", "VINGA", "RVEXPLORE", "RVADVENTURE", "RVULTIMATE"]
    shunt_types = ["SH200", "SH100"]  # ["SH100", "SH200"]

# Define invalid combinations
exclusions = [
    r'.*?_\d{4}_RV1_(?!(ASTRO))',
    r'.*?_\d{4}_RV3_(?!(AMOTOR))',
    r'.*?_\d{4}_RVS_(?!(AMOTOR))',
    r'.*?_\d{4}_RVBRABUS_(?!(AMOTOR))',
    r'.*?_\d{4}_RVADVENTURE_(?!(AMOTOR))',
    r'.*?_\d{4}_RVEXPLORE_(?!(AMOTORV3))',
    r'.*?_\d{4}_RVULTIMATE_(?!(AMOTORV3))',
    r'.*?_\d{4}_VINGA_(?!(VINGA))',
    r'AVESC25_(.*?)_SH100',  # AVESC25 only has SH200 configuration
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
