# Yocto Project and Bitbake Commands

This README provides a collection of useful Bitbake commands, basic Yocto variables, and instructions for working with BeagleBone.

## Bitbake Layers Commands

- **Show all available packages**
    ```
    bitbake-layers show-recipes
    ```
- **Show a specific package (e.g., python3)**
    ```
    bitbake-layers show-recipes python3
    ```
- **Create your own layer**
    ```
    bitbake-layers create-layer ../meta-mylayer
    ```
- **Add the created layer to bblayers.conf**

    ```
    bitbake-layers add-layer ../meta-mylayer/
    ```

## Basic Yocto Variables
Yocto follows a specific naming convention for recipes: PN_PV_PR.bb

For example: example2_0.1_r1.bb

You can extract values from a recipe using bitbake -e and grep:

- **Retrieve PN (Package Name)**

    ```
    bitbake -e example | grep ^PN=
    ```
- **Retrieve PV (Package Version)**

    ```
    bitbake -e example | grep ^PV=
    ```
- **Retrieve PR (Package Revision)**

    ```
    bitbake -e example | grep ^PR=
    ```
    Note: If PV and PR are not defined, defaults will be used (PV=1.0 and PR=r0).

- **Retrieve the working directory path**

    ```
    bitbake -e example | grep ^WORKDIR=
    ```
    WORKDIR structure: PN/PV-PR

- **Retrieve the source path (S)**

    ```
    bitbake -e example | grep ^S=
    ```
    S = WORKDIR/PV-PR

- **Retrieve the built example path (B)**

    ```
    bitbake -e example | grep ^B=
    ```
    B = S

- **Retrieve the destination path (D)**

    ```
    bitbake -e example | grep ^D=
    ```

    This is where the package image is located.

## Adding a Package to the Build

- **To add a package (e.g., python3) to the build, modify the local.conf file:**

    

    ```
    IMAGE_INSTALL:append = " python3"
    ```

    The space before python3 is intentional.


## Working with BeagleBone

- **Opening Serial Communication**

    To open a serial communication session with BeagleBone, use:

    ```
    sudo picocom -b 115200 /dev/ttyUSB0
    ```

- **I2C Detection**

    To detect I2C devices on BeagleBone, use:

    ```
    i2cdetect -y -r 2
    ```

## Creating and Uploading an IMG File

- **Create the IMG File**

    To create an IMG file:

    ```sh
    bitbake core-image-full-cmdline
    ```

- **Upload the IMG to an SD Card**

    Use Balena Etcher to upload the IMG file to your SD card. The IMG file will be located at:

    ```
    sources/tmp/deploy/images/beaglebone-yocto/core-image-full-cmdline-beaglebone-yocto.wic
    ```

## SSD1306 OLED Display Control

Here are some commands to control the ssd1306 OLED display library:

### Params
```sh
-I		init oled (128x32 or 128x64 or 64x48)
-c		clear (line number or all)
-d		0/display off 1/display on
-f      0/small font 5x7 1/normal font 8x8 (default small font)
-h		help message
-i		0/normal oled 1/invert oled
-l		put your line to display
-m		put your strings to oled
-n      I2C device node address (0,1,2..., default 0)
-r		0/normal 180/rotate
-x		x position
-y 		y position
```

- **Initialize the display**

    ```sh
    ssd1306 -I 128x64 -n 2
    ```

- **Clear the display**

    ```sh
    ssd1306 -I 128x64 -n 2 -c
    ```

- **Display text**

    ```sh
    ssd1306 -I 128x64 -n 2 -l "Hello world" -x 2 -y 0
    ```

## Reference
Source of oled page is [Here](https://github.com/armlabs/ssd1306_linux)
