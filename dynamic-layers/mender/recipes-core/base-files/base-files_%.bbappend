do_install:append() {
    if [ -n "${MENDER_DEMO_HOST_IP_ADDRESS}" ]; then
        if ! grep -q "s3.docker.mender.io" ${D}${sysconfdir}/hosts; then
            echo "${MENDER_DEMO_HOST_IP_ADDRESS} docker.mender.io s3.docker.mender.io" >> ${D}${sysconfdir}/hosts
        fi
    fi
}
