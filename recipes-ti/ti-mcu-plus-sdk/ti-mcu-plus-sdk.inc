# Copyright (C) 2026 Variscite
DESCRIPTION = "Variscite AM62/AM62P Cortex M4 / Cortex R5F Firmware Demos"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"
SECTION = "BSP"

DEPENDS = "ti-cgt-armllvm openssl-native"

S = "${WORKDIR}/git"

CM_BOARD="INVALID"
CM_BOARD:am62x-var-som="am62x-var-som"
CM_BOARD:am62px-var-som="am62px-var-som"

# Firmware source directories
CM_DEMOS = " \
    drivers/ipc/ipc_rpmsg_echo_linux \
"

# Cortex-M4 / Cortex-R5 CPUs
CM_CPU:am62x-var-som="m4fss0-0"
CM_CPU:am62px-var-som="mcu-r5fss0-0"
CM_DEMO_SYM_LNK:am62x-var-som="am62-mcu-m4f0_0-fw"
CM_DEMO_SYM_LNK:am62px-var-som="am62p-mcu-r5f0_0-fw"

do_compile() {
    # Build all demos in CM_DEMOS
    for CM_DEMO in ${CM_DEMOS}; do
        export PROJDIR="examples/${CM_DEMO}/${MACHINE}/${CM_CPU}_freertos/ti-arm-clang"
        oe_runmake -C ${PROJDIR} clean
        oe_runmake -C ${PROJDIR}
    done
}

do_install() {
    install -d ${D}${nonarch_base_libdir}/firmware/ti-ipc/

    # Install all demos in CM_DEMOS
    for CM_DEMO in ${CM_DEMOS}; do
        DIR_ARMCLANG="${S}/examples/${CM_DEMO}/${MACHINE}/${CM_CPU}_freertos/ti-arm-clang"
        # Install all build targets
        FILE_CM_FW="$(basename ${DIR_ARMCLANG}/*.release.strip.out)"
        install -m 644 ${DIR_ARMCLANG}/${FILE_CM_FW} ${D}${nonarch_base_libdir}/firmware/ti-ipc/${FILE_CM_FW}
    done

    # The first demo in the CM_DEMOS is linked to CM_DEMO_SYM_LNK to be started automatically by remoteproc
    CM_DEMO_AUTO_START=${@d.getVar('CM_DEMOS').split()[0]}
    CM_BIN_AUTO_START="$(basename ${S}/examples/${CM_DEMO_AUTO_START}/${MACHINE}/${CM_CPU}_freertos/ti-arm-clang/*.release.strip.out)"
    ln -sf "${nonarch_base_libdir}/firmware/ti-ipc/${CM_BIN_AUTO_START}" ${D}/${nonarch_base_libdir}/firmware/${CM_DEMO_SYM_LNK}
}

FILES:${PN} = " \
    ${nonarch_base_libdir}/firmware \
"

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

# Firmware files are run on M4
INSANE_SKIP = "arch"
