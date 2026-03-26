SECTION = "kernel"
SUMMARY = "Linux kernel for Variscite devices"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"

inherit kernel

DEFCONFIG_BUILDER = "${S}/ti_config_fragments/defconfig_builder.sh"
require recipes-kernel/linux/setup-defconfig.inc
require recipes-kernel/linux/kernel-rdepends.inc
require recipes-kernel/linux/ti-kernel.inc

DEPENDS += "gmp-native libmpc-native"

# Look in the generic major.minor directory for files
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-5.10:"

KERNEL_EXTRA_ARGS += "LOADADDR=${UBOOT_ENTRYPOINT} \
		      ${EXTRA_DTC_ARGS}"

S = "${WORKDIR}/git"

BRANCH = "ti-linux-5.10.y_var01"
SRCREV = "e6bda17da9476664a46175ae3424d91fac12c8ad"
PV = "5.10.168+git${SRCPV}"
KBUILD_DEFCONFIG = "am62x_var_defconfig"

BRANCH:am335x-var-som = "ti-linux-5.10.y_08.02.00.006_var01"
SRCREV:am335x-var-som = "feef8fc062ae9a5b4614b9ff642168a00fa8ff0e"
PV:am335x-var-som = "5.10.100+git${SRCPV}"
KBUILD_DEFCONFIG:am335x-var-som = "am335x_var_defconfig"

# Append to the MACHINE_KERNEL_PR so that a new SRCREV will cause a rebuild
MACHINE_KERNEL_PR_append = "b"
PR = "${MACHINE_KERNEL_PR}"

KERNEL_GIT_URI = "git://github.com/varigit/ti-linux-kernel"
KERNEL_GIT_PROTOCOL = "https"
SRC_URI += "${KERNEL_GIT_URI};protocol=${KERNEL_GIT_PROTOCOL};branch=${BRANCH}"

FILES_${KERNEL_PACKAGE_NAME}-devicetree += "/${KERNEL_IMAGEDEST}/*.itb"

# Special configuration for remoteproc/rpmsg IPC modules
module_conf_rpmsg_client_sample = "blacklist rpmsg_client_sample"
module_conf_ti_k3_r5_remoteproc = "softdep ti_k3_r5_remoteproc pre: virtio_rpmsg_bus"
module_conf_ti_k3_dsp_remoteproc = "softdep ti_k3_dsp_remoteproc pre: virtio_rpmsg_bus"
KERNEL_MODULE_PROBECONF += "rpmsg_client_sample ti_k3_r5_remoteproc ti_k3_dsp_remoteproc"
KERNEL_MODULE_AUTOLOAD_append_j7 = " rpmsg_kdrv_switch"

# ported from oe-core/meta/classes/kernel-yocto.bbclass
do_configure_prepend() {
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
