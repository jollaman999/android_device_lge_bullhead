#include <stdlib.h>

// These are paths to folders in /sys which contain "uevent" file
// need to init this device.
// MultiROM needs to init framebuffer, mmc blocks, input devices,
// some ADB-related stuff and USB drives, if OTG is supported
// You can use * at the end to init this folder and all its subfolders
const char *mr_init_devices[] =
{
    "/sys/class/graphics/fb0",

    "/sys/block/mmcblk0",
    "/sys/block/mmcblk0rpmb",
    "/sys/devices/soc.0/f9824900.sdhci",
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host",
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0",
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001",
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0",
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p37", // boot
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p40", // cache
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p1", // modem
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p24", // persist
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p41", // system
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p45", // userdata
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p30", // metadata
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p21", // ssd
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0rpmb", // rpmb

    "/sys/bus/mmc",
    "/sys/bus/mmc/drivers/mmcblk",
    "/sys/bus/sdio/drivers/bcmsdh_sdmmc",
    "/sys/module/mmc_core",
    "/sys/module/mmcblk",

    "/sys/class/input/input0",
    "/sys/class/input/input0/event0",
    "/sys/class/input/input1",
    "/sys/class/input/input1/event1",
    "/sys/class/input/input2",
    "/sys/class/input/input2/event2",
    "/sys/class/input/input3",
    "/sys/class/input/input3/event3",
    "/sys/class/input/input4",
    "/sys/class/input/input4/event4",
    "/sys/class/input/input5",
    "/sys/class/input/input5/event5",
    "/sys/class/input/input6",
    "/sys/class/input/input6/event6",
    
    // for adb
    "/sys/class/tty/ptmx",
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p41", // system
    "/sys/devices/soc.0/f9824900.sdhci/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p40", // cache
    "/sys/class/misc/android_adb",
    "/sys/class/android_usb/android0/f_ffs",
    "/sys/bus/usb",

    // USB Drive is in here
    "/devices/soc.0/f9200000.ssusb/f9200000.dwc3/xhci-hcd.0.auto/usb*",

    // Encryption
    "/sys/devices/virtual/misc/device-mapper",
    "/sys/devices/virtual/misc/ion",
    "/sys/devices/virtual/qseecom/qseecom",

    // exfat requires fuse device
    "/sys/devices/virtual/misc/fuse",

    NULL
};
