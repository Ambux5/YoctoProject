SUMMARY = "Hello world program"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"
SRC_URI = "file://helloworld_linux/"
S = "${WORKDIR}/helloworld_linux"

DEPENDS = "i2c-tools ssd1306 ina219"
LDFLAGS = "-loleddisplay -lcursensor -static"
TARGET_CC_ARCH += "${LDFLAGS}"

do_compile() {
    ${CC} -o helloworld helloworld.c ${TARGET_CC_ARCH}
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 helloworld ${D}${bindir}
}