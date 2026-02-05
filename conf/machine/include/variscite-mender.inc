# Override default Mender features for Variscite platforms. Leave image
# generation to the machine configuration (explicit WKS) but keep the client,
# systemd units, and update/install bits enabled.
INHERIT += "variscite-mender-explicit-wic"

MENDER_FEATURES_ENABLE = " \
    mender-uboot \
    mender-auth-install \
    mender-update-install \
    mender-systemd \
    mender-growfs-data \
"
MENDER_FEATURES_DISABLE = " mender-image "

# Mender Demo Server
MENDER_DEMO_HOST_IP_ADDRESS = "192.168.0.155"
MENDER_SERVER_URL = "https://${MENDER_DEMO_HOST_IP_ADDRESS}"
VAR_MENDER_SERVER_SKIP_VERIFY = "1"

# Mender Artifact Name
MENDER_ARTIFACT_NAME = "${MACHINE}-release-1"

MENDER_UBOOT_AUTO_CONFIGURE ?= "0"
MENDER_UBOOT_POST_SETUP_COMMANDS="setenv mmcpart \${mender_boot_part}"
