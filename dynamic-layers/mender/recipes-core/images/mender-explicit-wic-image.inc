SUMMARY:append = " (Mender explicit WIC layout)"

# Pull in the explicit WIC flow from this layer (keeps boot/rootfs/data alignment
# and uses the fixed WKS file).
inherit variscite-mender-explicit-wic

# Keep rootfs images inside the 2.304GB partition defined in the explicit WKS
# for 8GB eMMC (7456MiB usable). Tighten overhead and cap size explicitly.
IMAGE_OVERHEAD_FACTOR = "1.00"
IMAGE_ROOTFS_EXTRA_SPACE = "0"
# Target ~2.2GB filesystem size (in KB); fits under 2.304GB partition with slack.
IMAGE_ROOTFS_SIZE = "2200000"
# Hard cap so we fail early if it ever grows past the partition.
IMAGE_ROOTFS_MAXSIZE = "2304000"

CORE_IMAGE_EXTRA_INSTALL:append = " \
    mender-configure \
    mender-configure-scripts \
    mender-connect \
    tzdata-core \
    kernel-image \
    kernel-devicetree \
"

ROOTFS_POSTPROCESS_COMMAND:append = " create_mender_data_structure; "

# Keep Mender state on the persistent /data partition across A/B switches.
create_mender_data_structure() {
    install -d ${IMAGE_ROOTFS}/data
    install -d ${IMAGE_ROOTFS}/data/mender
    install -d ${IMAGE_ROOTFS}/data/mender-configure

    # Copy any client-installed state from /var/lib/mender into the persistent store.
    cp -a ${IMAGE_ROOTFS}/var/lib/mender/. ${IMAGE_ROOTFS}/data/mender/ 2>/dev/null || true

    # Ensure all future accesses use the persistent /data/mender across A/B boots.
    rm -rf ${IMAGE_ROOTFS}/var/lib/mender
    ln -s /data/mender ${IMAGE_ROOTFS}/var/lib/mender
}
