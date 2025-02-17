DESCRIPTION = "SSD1306 OLED Display library for Linux"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://src"

S = "${WORKDIR}/src"
# DEPENDS = "i2c-tools"

inherit autotools
inherit logging

do_compile:append() {
    bbwarn "Hello this is a debug message from ${USER}"
}

# The autotools configuration I am basing this on seems to have a problem with a race condition when parallel make is enabled
# PARALLEL_MAKE = ""
