# Copyright (C) 2024 Variscite
DESCRIPTION = "Variscite AM62 Cortex M4 Firmware Demos"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"
SECTION = "BSP"

DEPENDS = "ti-cgt-armllvm sysconfig openssl-native"

S = "${WORKDIR}/git"

MCORE_TYPE  ?= "m4"

CM_BOARD="INVALID"
CM_BOARD:am62x-var-som="am62x-var-som"

# Firmware source directories
CM_DEMOS = " \
    drivers/ipc/ipc_rpmsg_echo_linux \
"

do_compile() {
    TI_CLANG_PATH_TO_BE_REPLACED="CGT_TI_ARM_CLANG_PATH=\$(TOOLS_PATH)/ti-cgt-armllvm_\$(CGT_ARMLLVM_VERSION)"
    TI_CLANG_PATH="CGT_TI_ARM_CLANG_PATH=${STAGING_DIR_NATIVE}${bindir}/arm32-oe-linux/ti-cgt-armllvm_\$(CGT_ARMLLVM_VERSION)"
    SYSCONFIG_PATH_TO_BE_REPLACED="SYSCFG_PATH ?= \$(TOOLS_PATH)/sysconfig_\$(SYSCONFIG_VERSION)"
    SYSCONFIG_PATH="SYSCFG_PATH = ${STAGING_DIR_NATIVE}${bindir}/arm32-oe-linux/sysconfig"

    # Search for strings to be replaced in imports.mak to make sure they exist
    set -- "$TI_CLANG_PATH_TO_BE_REPLACED" "$SYSCONFIG_PATH_TO_BE_REPLACED"
    for PATH_TO_BE_REPLACED in "$@"; do
        grep -nrwq "${PATH_TO_BE_REPLACED}" ${S} --include "imports.mak"
        ret=$?
        if [ $ret -ne 0 ]; then
                bbfatal "The string <<<${PATH_TO_BE_REPLACED}>>> cannot be replaced because not found in the files ${S}/imports.mak"
        fi
    done

    # Update TI_ARM_CLANG and Sysconfig paths in imports.mak
    sed -i "s|$TI_CLANG_PATH_TO_BE_REPLACED|$TI_CLANG_PATH|g" ${S}/imports.mak
    sed -i "s|$SYSCONFIG_PATH_TO_BE_REPLACED|$SYSCONFIG_PATH|g" ${S}/imports.mak

    # Build all demos in CM_DEMOS
    for CM_DEMO in ${CM_DEMOS}; do
        cd ${S}
        export PROJDIR="examples/${CM_DEMO}/am62x-var-som/m4fss0-0_freertos/ti-arm-clang"
	make -s -C ${PROJDIR} clean
	make -s -C ${PROJDIR}
    done
}

do_install() {
    install -d ${D}${nonarch_base_libdir}/firmware/ti-ipc/am62xx/

    # Install all demos in CM_DEMOS
    for CM_DEMO in ${CM_DEMOS}; do
        DIR_ARMCLANG="${S}/examples/${CM_DEMO}/am62x-var-som/m4fss0-0_freertos/ti-arm-clang"
        # Install all build targets
        FILE_CM_FW="$(basename ${DIR_ARMCLANG}/*.release.strip.out)"
        install -m 644 ${DIR_ARMCLANG}/${FILE_CM_FW} ${D}${nonarch_base_libdir}/firmware/ti-ipc/am62xx/${FILE_CM_FW}
        ln -sf "${nonarch_base_libdir}/firmware/ti-ipc/am62xx/${FILE_CM_FW}" ${D}/${nonarch_base_libdir}/firmware/am62-mcu-m4f0_0-fw
    done
}

FILES:${PN} = " \
    ${nonarch_base_libdir}/firmware \
"

INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

# Firmware files are run on M4
INSANE_SKIP = "arch"
