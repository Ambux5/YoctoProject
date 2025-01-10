DESCRIPTION = "Expander for Linux"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://src/"

S = "${WORKDIR}/src"

do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/pi4ioe5v64 ${D}${bindir}
}

DEPENDS = "i2c-tools"
LDFLAGS = "-static"
TARGET_CC_ARCH += "${LDFLAGS}"

do_compile() {
    ${CXX} -o pi4ioe5v64 main.cpp pi4ioe5v64xx.cpp i2c.cpp -lm ${TARGET_CC_ARCH}
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 pi4ioe5v64 ${D}${bindir}
}