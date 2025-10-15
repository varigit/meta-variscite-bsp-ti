
FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append:am62x-var-som = " \
    file://38-var-i2c-eeprom.rules \
    file://38-var-ttyBT.rules \
"

FILES:${PN}:append:am62x-var-som = " \
    ${sysconfdir}/udev/rules.d \
"

do_install:append:am62x-var-som() {
    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0644 ${WORKDIR}/38-var-i2c-eeprom.rules ${D}${sysconfdir}/udev/rules.d/
    install -m 0644 ${WORKDIR}/38-var-ttyBT.rules ${D}${sysconfdir}/udev/rules.d/
}
