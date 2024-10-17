DESCRIPTION = "SSD1306 OLED Display library for Linux"
LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SRC_URI = "file://ssd1306_linux/"

S = "${WORKDIR}/ssd1306_linux"
DEPENDS = "i2c-tools"


do_compile() {
    cd ${S}
    echo "Current directory: $(pwd)"
    oe_runmake CC="${CC}" CFLAGS="${CFLAGS}" LDFLAGS="${LDFLAGS}"
}

do_install() {
    install -d ${D}${bindir}
    install -d ${D}${includedir}
    install -m 0755 ${S}/ssd1306_bin ${D}${bindir}/ssd1306
    install -m 0644 ${S}/ssd1306.h ${D}${includedir}/
}

FILES_${PN} += "/usr/lib"
