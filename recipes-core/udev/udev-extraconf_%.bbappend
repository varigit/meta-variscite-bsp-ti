FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

# for all VAR-SOMs: prevent automatic loading of modules
SRC_URI:append:var-som = " \
	file://variscite-blacklist.conf \
"

# for AM62x only: udev rules
SRC_URI:append:am62x-var-som = " \
    file://38-var-i2c-eeprom.rules \
    file://38-var-ttyBT.rules \
"


do_install:append:var-som() {
	install -m 0755 -d ${D}${sysconfdir}/modprobe.d
	install -m 0644 ${WORKDIR}/variscite-blacklist.conf ${D}${sysconfdir}/modprobe.d
}

do_install:append:am62x-var-som() {
    install -d ${D}${sysconfdir}/udev/rules.d
    install -m 0644 ${WORKDIR}/38-var-i2c-eeprom.rules ${D}${sysconfdir}/udev/rules.d/
    install -m 0644 ${WORKDIR}/38-var-ttyBT.rules ${D}${sysconfdir}/udev/rules.d/
}
