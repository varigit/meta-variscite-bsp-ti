
PACKAGECONFIG:append = "${@bb.utils.contains("LICENSE_FLAGS_ACCEPTED", "commercial_faad2", " faad", "", d)}"
