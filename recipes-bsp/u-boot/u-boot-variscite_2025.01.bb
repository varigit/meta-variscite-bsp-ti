require recipes-bsp/u-boot/u-boot-ti.inc
FILESEXTRAPATHS:prepend:var-som:k3r5 := "${THISDIR}/${PN}/am62x-var-som: ${THISDIR}/${PN}/am62px-var-som:"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=2ca5f2c35c8cc335f0a19756634782f1"

UBOOT_INITIAL_ENV = "u-boot-initial-env"
SRC_URI += "file://fw_env.config"

UBOOT_GIT_URI = "git://github.com/varigit/ti-u-boot"
BRANCH = "ti-u-boot-2025.01_11.02.08.02_var01"

SRCREV = "265ddb3845079d4a50514890ec0e1d9e9cb3623c"

COMPATIBLE_MACHINE = "(am62x-var-som|am62px-var-som)"

inherit var-check-keydir

do_deploy:append() {
    if [ -L ${DEPLOY_DIR_IMAGE}/fw_env.config ]; then
        rm ${DEPLOY_DIR_IMAGE}/fw_env.config
    fi
}

python do_patch:append:var-som-secureboot() {
    # This needs to be a Python function and not a bash function because we
    # want to execute it for both Cortex A53 and Cortex R5 (multiconfig, mc).
    # For the mc execution, we do not get full visibility of Yocto environment, e.g.
    # cannot detect SIGN_KEYDIR. For Python functions, this is provided properly.

    import os
    import shutil
    import glob

    src_key_dir = d.getVar('SIGN_KEYDIR')

    # cp ${SIGN_KEYDIR}/* ${S}/board/variscite/keys
    dst_key_dir = os.path.join(d.getVar('S'), "arch", "arm", "mach-k3", "keys")
    for file_path in glob.glob(os.path.join(src_key_dir, "*")):
        if os.path.isfile(file_path):
            shutil.copy(file_path, dst_key_dir)
}
