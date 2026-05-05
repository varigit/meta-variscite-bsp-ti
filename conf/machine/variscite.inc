INHERIT += "image-buildinfo"
USE_VT = "0"

# Common override for all Variscite machines
MACHINEOVERRIDES =. "var-som:"

# Variscite BSP default providers
PREFERRED_PROVIDER_virtual/kernel:var-som = "linux-variscite"
PREFERRED_RPROVIDER_u-boot-default-env:var-som = "u-boot-variscite"
PREFERRED_PROVIDER_virtual/bootloader:var-som = "u-boot-variscite"
PREFERRED_PROVIDER_u-boot:var-som = "u-boot-variscite"

ASSUME_PROVIDED:remove += "nativesdk-perl"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " \
	gptfdisk \
	hostapd \
	hdparm \
	iw \
	kernel-modules \
	kmod \
	networkmanager \
	packagegroup-tools-bluetooth \
	bluealsa \
	pm-utils \
	rng-tools \
	wpa-supplicant \
	wireless-regdb-static \
	u-boot-fw-utils \
	u-boot-default-env \
"

KERNEL_IMAGETYPES = "Image"
IMAGE_FSTYPES = "wic.bmap wic.zst tar.zst"
IMAGE_FSTYPES:remove = "tar.xz.md5"

# Wayland based distros add systemd to DISTRO_FEATURES
# Remove sysvinit or systemd based on DISTRO_FEATURES to avoid conflicts
DISTRO_FEATURES_BACKFILL_CONSIDERED:append = "${@bb.utils.contains('DISTRO_FEATURES', 'systemd', ' sysvinit', '', d)}"
DISTRO_FEATURES_BACKFILL_CONSIDERED:append = "${@bb.utils.contains('DISTRO_FEATURES', 'sysvinit', ' systemd', '', d)}"
