rename_tpm_dtb_in_rootfs() {
    dtb_dir="${IMAGE_ROOTFS}/boot"
    src="${dtb_dir}/var-som-am33-tpm.dtb"
    dst="${dtb_dir}/var-som-am33.dtb"

    if [ -e "${dst}" ]; then
        mv "${dst}" "${dtb_dir}/var-som-am33-notpm.dtb"
    fi

    if [ -e "${src}" ]; then
        mv "${src}" "${dst}"
    fi
}

ROOTFS_POSTPROCESS_COMMAND:append:am335x-var-som-tpm = " \
    rename_tpm_dtb_in_rootfs; \
"
