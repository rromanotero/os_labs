# Operating Systems Labs for Raspberry PI 3

## Bare-metal Raspberry PI 3 Resources ( We'll be building on these )
- [Application note. Bare-metal Boot Code for ARMv8-A Processors](http://infocenter.arm.com/help/topic/com.arm.doc.dai0527a/DAI0527A_baremetal_boot_code_for_ARMv8_A_processors.pdf)
- [MiniOS](https://github.com/rromanotero/minios)
- [Sergey Matyukevich's Raspberry PI OS](https://github.com/s-matyukevich/raspberry-pi-os/)
- [Leon de Boer's Bare Metal Examples](https://github.com/LdB-ECM/Raspberry-Pi/)
- [Zoltan Baldaszti's PI3's Tutorial](https://github.com/bztsrc/raspi3-tutorial)
- [PeterLemon's Bare Metal Assembly  for PI 3](https://github.com/PeterLemon/RaspberryPi)
- [Maciej Muszkowski's No OS Bootstrap](https://github.com/mmuszkow/NoOsBootstrap/)

## Getting the aarch64-elf bare-metal GNU Toolchain

I've created an image with the aarch64-toolchain. All labs use it. To get it:

```bash
docker pull rromanotero/aarch64
```

## Compiling this Lab on Windows
##### ( Docker Windows requires the FULL PATH TO THE LAB FOLDER to bind mount it)
```bash
git clone https://github.com/rromanotero/os_labs.git
cd os_labs
docker run `
       -v C:\...\LAB_FOLDER:/src `
       rromanotero/aarch64 `
       bash -c "cd src && make"
```   

## Compiling this Lab on Linux/Mac
```bash
git clone https://github.com/rromanotero/os_labs.git
cd os_labs
docker run \
       -v ./LAB_FOLDER:/src \
       rromanotero/aarch64 \
       bash -c "cd src && make"
```

## Running Labs in QEMU

All labs have been tested with [QEMU](https://www.qemu.org/download/).

**The exact command for every lab is on its README**

## Running Labs in a PI 3

You'll need a Raspberry PI 3 MOdel A+, a [USB to UART converter](https://www.adafruit.com/product/954), [PuTTY](https://www.putty.org/), and the boot files from [Raspbian Buster Lite image](https://www.raspberrypi.org/downloads/raspbian/).

1. Get an SDCard with [Raspbian Buster Lite](https://www.raspberrypi.org/downloads/raspbian/) installed on it (see [installation instructions](https://www.raspberrypi.org/documentation/installation/installing-images/README.md))
2. replace **kernel8.img in the boot partition of the SDCard** (you'll see it when reading the PI's SDCard from a laptop) with ./LAB_DIRECTORY/output/kernel8.img
3. Insert back the SD Card onto the PI
4. Depending on the USB to UART converter, drivers may need to be installed (if you're using the one from Adafruit, they also have a tutorial)
5. Plug the PI's UART to yout laptop (via the converter) as per the [PI 3's pinout](https://pi4j.com/1.1/pins/model-a-plus.html), and access the PI from PuTTY:

  <img src="https://github.com/rromanotero/computer_architecture_labs/blob/master/images/lab_setup_a.jpg" width="240"/>
  <img src="https://github.com/rromanotero/computer_architecture_labs/blob/master/images/lab_setup_b.png" width="480"/>
