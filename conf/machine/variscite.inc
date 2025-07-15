INHERIT += "image-buildinfo"
USE_VT = "0"

# Common override for all Variscite machines
MACHINEOVERRIDES =. "var-som:"

# Variscite BSP default providers
PREFERRED_PROVIDER_virtual/kernel:var-som = "linux-variscite"
PREFERRED_RPROVIDER_u-boot-default-env:var-som = "u-boot-variscite"
PREFERRED_PROVIDER_virtual/bootloader:var-som = "u-boot-variscite"
PREFERRED_PROVIDER_u-boot:var-som = "u-boot-variscite"

ASSUME_PROVIDED:remove = "nativesdk-perl"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " \
	gptfdisk \
	hostapd \
	hdparm \
	iw \
	kernel-modules \
	kmod \
	packagegroup-tools-bluetooth \
	bluealsa \
	pm-utils \
	rng-tools \
	wpa-supplicant \
	wireless-regdb-static \
	u-boot-fw-utils \
	u-boot-default-env \
	${@bb.utils.contains('MACHINE_FEATURES', 'bootloader-splash', \
		'u-boot-splash','', d)} \
"

MACHINE_FIRMWARE:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'nxpiw612-sdio', 'firmware-nxp-wifi-nxpiw612-sdio', '', d)}"
MACHINE_EXTRA_RRECOMMENDS:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'nxpiw612-sdio', 'kernel-module-nxp-wlan', '', d)}"
MACHINE_EXTRA_RRECOMMENDS:append = "${MACHINE_FIRMWARE}"
PREFERRED_RPROVIDER_linux-firmware-nxpiw612-sdio = "firmware-nxp-wifi"

MACHINE_EXTRA_RDEPENDS += " \
    ${@bb.utils.contains('MACHINE_FEATURES', 'nxpiw612-sdio', 'iw612-utils', '', d)} \
"

KERNEL_IMAGETYPES = "Image"
IMAGE_FSTYPES = "wic.bmap wic.zst tar.zst"
IMAGE_FSTYPES:remove = "tar.xz.md5"

# Wayland based distros add systemd to DISTRO_FEATURES
# Remove sysvinit or systemd based on DISTRO_FEATURES to avoid conflicts
DISTRO_FEATURES_BACKFILL_CONSIDERED:append = "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', ' sysvinit', '', d)}"
DISTRO_FEATURES_BACKFILL_CONSIDERED:append = "${@bb.utils.contains('DISTRO_FEATURES', 'sysvinit', ' systemd', '', d)}"

NETMAN_PACKAGES = "\
    networkmanager \
    networkmanager-nmcli \
"

# Wayland distros should default to systemd-networkd
PREFERRED_CONNECTIVITY_MANAGER = "systemd-networkd"
PREFERRED_CONNECTIVITY_MANAGER_PACKAGES	?= " \
    ${@bb.utils.contains('PREFERRED_CONNECTIVITY_MANAGER', 'networkmanager', \
        '${NETMAN_PACKAGES}','', d)} \
"

CORE_IMAGE_EXTRA_INSTALL += " \
    packagegroup-variscite-devel \
    ${PREFERRED_CONNECTIVITY_MANAGER_PACKAGES} \
"

BBMASK += "meta-tisdk/meta-ti-foundational/recipes-tisdk/tisdk-uenv/tisdk-uenv.bbappend"
