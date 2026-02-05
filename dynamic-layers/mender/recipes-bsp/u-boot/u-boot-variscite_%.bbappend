require recipes-bsp/u-boot/u-boot-mender.inc

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = " \
    file://mender-required-configs.cfg \
"

# Convert zero-filled env to 0xFF so bmaptool copies it.
do_deploy:append:mender-uboot() {
    if [ -f ${DEPLOYDIR}/uboot.env ]; then
        dd if=/dev/zero bs=${MENDER_BOOTENV_TOTAL_ALIGNED_SIZE} count=1 \
          | tr '\000' '\377' > ${WORKDIR}/uboot.env
        install -m 644 ${WORKDIR}/uboot.env ${DEPLOYDIR}/uboot.env
    fi
}
