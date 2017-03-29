# Creating A Bootloader For C030

Clone this repo, then run

`mbed deploy`

...to download the necessary libraries.

To build the bootloader for C030:

`mbed target UBLOX_C030`

`mbed toolchain GCC_ARM`

`mbed compile`

This will create two binary files; the bootloader image is `mbed-os-example-bootloader-c030.bin`, ignore the `mbed-os-example-bootloader-c030_application.bin`.

Just to prove that it works, copy `mbed-os-example-bootloader-c030.bin` to the mbed board and run it.  On a TTY you should see something like:

```
No "update.bin" file found on SD card to apply.
Starting application
```

Next you need to build an application to be bootloaded from the SD card.

# Set Up An Application To Be Bootloaded

The next step is to build an application you can combine with your bootloader to create a loadable image. Clone the application of your choice and, in the `mbed_app.json` for that application, add the following:

```
    "target_overrides": {
        ...
        UBLOX_CO30: {
            "target.bootloader_img": "bootloader/UBLOX_CO30.bin"
        },
        ...
```

Now copy the `mbed-os-example-bootloader-c030.bin` from the first step to become the file `bootloader\UBLOX_C030.bin`.

Build the application for C030:

`mbed target UBLOX_C030`

`mbed toolchain GCC_ARM`

`mbed compile`

Copy `<project_name>_application.bin` to an SD card, rename it to `update.bin` and put the SD card into your board.  When the board is reset, you should now see:

```
Firmware update found
Starting application
```

...and the new application from the SD card should be running on the board (and the `.bin` file will have been deleted from the SD card to prevent it being loaded repeatedly).