DESCRIPTION = "INA219 Current sensor library for Linux"
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
