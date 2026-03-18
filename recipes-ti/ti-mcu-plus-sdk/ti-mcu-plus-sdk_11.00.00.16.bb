# Copyright (C) 2026 Variscite
include ti-mcu-plus-sdk.inc

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

MCU-PLUS_BRANCH = "mcu_plus_sdk_am62px_11_00_00_16_var01"

SRCREV = "419c3a43a7cc2003345475aa9586bb79daa69a90"
SRC_URI = " \
    git://github.com/varigit/ti-mcu-plus-sdk.git;protocol=https;branch=${MCU-PLUS_BRANCH}; \
"

COMPATIBLE_MACHINE = "(am62px-var-som)"
