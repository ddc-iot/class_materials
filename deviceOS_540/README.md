# Upgrade Photon2 to Device OS 5.4.0

Clone this respository and using the CLI from within the respository.

## System Part1
Place device in DFU mode either manually or by using the CLI command:
* particle usb dfu

Flash System Part1:
* particle flash --usb p2-system-part1@5.4.0.bin

## Bootloader
Place device in Listening mode before each of the below, by press and release of reset and then holding down the mode button until flashing blue

Flash PreBootloader Part1:
* particle flash --serial p2-prebootloader-part1@5.4.0.bin

Flash PreBootloader MBR:
* particle flash --serial p2-prebootloader-mbr@5.4.0.bin

Flash Bootloader:

* particle flash --serial p2-bootloader@5.4.0.bin