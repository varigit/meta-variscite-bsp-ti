SUMMARY = "Secure Boot - SIGN_KEYDIR check"
LICENSE = "MIT"

python do_check_sign_keydir() {
    bb.note("Nothing to check. Not running for Secure Boot machine")
}

# check if the variable SIGN_KEYDIR is set. It needs to be set if we build for a machine with secure boot enabled
python do_check_sign_keydir:var-som-secureboot() {
    import os

    sign_keydir = d.getVar('SIGN_KEYDIR')
    if not sign_keydir:
        bb.fatal("SIGN_KEYDIR must be set and point to a directory with keys for signing bootloader and kernel")
        return
    if not os.path.isdir(sign_keydir):
        bb.fatal(f"Cannot find {sign_keydir}. Please make sure that it exists and contains keys for signing bootloader and kernel")
        return
}

addtask do_check_sign_keydir before do_fetch
