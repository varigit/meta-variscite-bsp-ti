SECTION = "kernel"
SUMMARY = "Linux kernel for Variscite devices"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

inherit kernel

DEFCONFIG_BUILDER = "${S}/ti_config_fragments/defconfig_builder.sh"
require recipes-kernel/linux/setup-defconfig.inc

require recipes-kernel/linux/ti-kernel.inc

DEPENDS += "gmp-native libmpc-native"

KERNEL_EXTRA_ARGS += "LOADADDR=${UBOOT_ENTRYPOINT} \
		      ${EXTRA_DTC_ARGS}"

S = "${WORKDIR}/git"

BRANCH = "ti-linux-6.12.y_11.00.09.04_var01"
SRCREV = "c24194956313f0713277bec30d70c395175cc8b1"
PV = "6.12.17+git"
KBUILD_DEFCONFIG = "am62x_var_defconfig"

# Do not put dtb in ti subdir
KERNEL_DTBVENDORED = "0"

KERNEL_GIT_URI = "git://github.com/varigit/ti-linux-kernel"

SRC_URI = " \
    ${KERNEL_GIT_URI};protocol=${KERNEL_GIT_PROTOCOL};${KERNEL_GIT_BRANCH} \
"

FILES_${KERNEL_PACKAGE_NAME}-devicetree += "/${KERNEL_IMAGEDEST}/*.itb"

# Special configuration for remoteproc/rpmsg IPC modules
module_conf_rpmsg_client_sample = "blacklist rpmsg_client_sample"
module_conf_ti_k3_r5_remoteproc = "softdep ti_k3_r5_remoteproc pre: virtio_rpmsg_bus"
module_conf_ti_k3_dsp_remoteproc = "softdep ti_k3_dsp_remoteproc pre: virtio_rpmsg_bus"
KERNEL_MODULE_PROBECONF += "rpmsg_client_sample ti_k3_r5_remoteproc ti_k3_dsp_remoteproc"
KERNEL_MODULE_AUTOLOAD:append:j7 = " rpmsg_kdrv_switch"

# ported from oe-core/meta/classes/kernel-yocto.bbclass
do_configure:prepend() {
	if [ -n "${KBUILD_DEFCONFIG}" ]; then
		if [ -f "${S}/arch/${ARCH}/configs/${KBUILD_DEFCONFIG}" ]; then
			if [ -f "${WORKDIR}/defconfig" ]; then
				# If the two defconfig's are different, warn that we didn't overwrite the
				# one already placed in WORKDIR by the fetcher.
				cmp "${WORKDIR}/defconfig" "${S}/arch/${ARCH}/configs/${KBUILD_DEFCONFIG}"
				if [ $? -ne 0 ]; then
					bbwarn "defconfig detected in WORKDIR. ${KBUILD_DEFCONFIG} skipped"
				else
					cp -f ${S}/arch/${ARCH}/configs/${KBUILD_DEFCONFIG} ${WORKDIR}/defconfig
				fi
			else
				cp -f ${S}/arch/${ARCH}/configs/${KBUILD_DEFCONFIG} ${WORKDIR}/defconfig
			fi
		else
			bbfatal "A KBUILD_DEFCONFIG '${KBUILD_DEFCONFIG}' was specified, but not present in the source tree (${S}/arch/${ARCH}/configs/)"
		fi
	fi
}

COMPATIBLE_MACHINE = "(am62x-var-som|am62px-var-som)"
