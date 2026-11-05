# Use a PREMIRROR for TI repositories.
# TI already provides a MIRROR, but in this MIRROR, the tar archive of that package is outdated
PREMIRRORS:prepend = " \
    git://git.ti.com/git/pru-software-support-package/pru-software-support-package.git git://github.com/varigit/pru-software-support-package.git;protocol=https \n \
"
