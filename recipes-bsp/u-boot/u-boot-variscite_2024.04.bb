require recipes-bsp/u-boot/u-boot-ti.inc
FILESEXTRAPATHS:prepend:var-som:k3r5 := "${THISDIR}/${PN}/am62px-var-som:"

LIC_FILES_CHKSUM = "file://Licenses/README;md5=2ca5f2c35c8cc335f0a19756634782f1"

UBOOT_INITIAL_ENV = "u-boot-initial-env"
SRC_URI += "file://fw_env.config"

UBOOT_GIT_URI = "git://github.com/varigit/ti-u-boot"

BRANCH = "ti-u-boot-2024.04_10.01.10.04_var01"
SRCREV = "aa1d1e917fa8992fad9f63494b7fefbb27d125e1"

COMPATIBLE_MACHINE = "(am62x-var-som|am62px-var-som)"

do_deploy:append() {
    if [ -L ${DEPLOY_DIR_IMAGE}/fw_env.config ]; then
        rm ${DEPLOY_DIR_IMAGE}/fw_env.config
    fi
}
