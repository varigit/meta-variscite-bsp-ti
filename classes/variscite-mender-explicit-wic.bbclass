# https://hub.mender.io/t/explicit-wks-partitioning-for-mender-a-b-updates/8162
# Inherit essential Mender functionality but NOT image generation classes
inherit mender-setup mender-systemd mender-uboot

# Guard against enabling mender-image with this explicit WIC flow.
python() {
    if bb.utils.contains('MENDER_FEATURES', 'mender-image', True, False, d):
        bb.fatal("variscite-mender-explicit-wic requires mender-image to stay disabled.")
}

# Keep Mender persistent data on the shared data partition even without mender-image
_MENDER_PERSISTENT_DIR = "/data/mender"

# Use the explicit mender layout when Mender is enabled.
WKS_FILE = "mender-explicit-${MACHINE}.wks"

IMAGE_FSTYPES:append = " wic wic.bz2 mender"

IMAGE_CMD:mender() {
    if [ -z "${MENDER_ARTIFACT_NAME}" ]; then
        bbfatal "MENDER_ARTIFACT_NAME not set."
    fi

    ROOTFS_IMG="${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.${ARTIFACTIMG_FSTYPE}"
    MENDER_ARTIFACT="${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.mender"

    DEVICE_TYPE_ARGS=""
    for DEVICE_TYPE in ${MENDER_DEVICE_TYPES_COMPATIBLE}; do
        DEVICE_TYPE_ARGS="${DEVICE_TYPE_ARGS} -t ${DEVICE_TYPE}"
    done

    mender-artifact write rootfs-image \
        --artifact-name ${MENDER_ARTIFACT_NAME} \
        ${DEVICE_TYPE_ARGS} \
        --file ${ROOTFS_IMG} \
        --output-path ${MENDER_ARTIFACT}
}

do_image_mender[depends] += " \
    mender-artifact-native:do_populate_sysroot \
    ${PN}:do_image_${ARTIFACTIMG_FSTYPE} \
"

# ${sysconfdir}/mender/scripts/version is normally created by mender-setup-image.inc.
# With mender-image disabled, create it below.
ROOTFS_POSTPROCESS_COMMAND:append = " variscite_mender_create_scripts_version_file; "
variscite_mender_create_scripts_version_file() {
    install -d -m 755 ${IMAGE_ROOTFS}${sysconfdir}/mender/scripts/
    echo -n "${MENDER_STATE_SCRIPTS_VERSION}" > ${IMAGE_ROOTFS}${sysconfdir}/mender/scripts/version
}
