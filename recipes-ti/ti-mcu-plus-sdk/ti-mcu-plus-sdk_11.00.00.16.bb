# Copyright (C) 2026 Variscite
include ti-mcu-plus-sdk.inc

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

MCU-PLUS_BRANCH:am62x-var-som = "mcu_plus_sdk_am62x_11_00_00_16_var01"
MCU-PLUS_BRANCH:am62px-var-som = "mcu_plus_sdk_am62px_11_00_00_16_var01"

SRCREV = "6790cf5d3c752afb5e02e88248e74cf09ebd0270"
SRCREV:am62xx = "256ff14e33db6f66b70a9fd1aeca0a5625f4a3a4"
SRCREV:am62pxx = "6790cf5d3c752afb5e02e88248e74cf09ebd0270"
SRC_URI = " \
    git://github.com/varigit/ti-mcu-plus-sdk.git;protocol=https;branch=${MCU-PLUS_BRANCH}; \
"

COMPATIBLE_MACHINE = "(am62x-var-som|am62px-var-som)"
