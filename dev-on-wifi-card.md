# Flipper Zero WiFi Devboard - Customize and compile firmware
This is how the Flipper Zero WiFi Devboard works

*   Flipper Zero offers a variety of tools for exploring and testing wireless standards and protocols
*   One of the most popular hardware extensions for Flipper Zero is the WiFi Devboard
*   Compiling the firmware is easy for Flipper Zero, but quite complicated for the WiFi Devboard
*   Once the development environment is set up, further customizations are easily possible

The Flipper Zero is a [very versatile tool](https://www.scip.ch/?labs.20221201) for researching and testing radio protocols, access control systems, hardware in the fields of RFID, RF, infrared, HID emulation, GPIO, hardware debugging, 1-Wire/iButton, Bluetooth, Wifi and more. It is inspired by well-known open source projects such as Proxmark, HydraNFC, Rubber Ducky, pwnagotchi and is offered in a handy form factor. The Flipper Zero is already equipped with many functionalities in its standard configuration and can be adapted and expanded quite easily due to its open source nature. On the one hand, hardware extensions can be connected via its GPIO PINs and on the other hand, various firmware distributions are freely available as open source. This article deals with the popular hardware extension [WiFi Devboard](https://shop.flipperzero.one/products/wifi-devboard) and shows how to adapt, compile and install the corresponding software and firmware. All commands shown in this article apply to Linux systems, but can also be carried out on macOS or Windows systems in the same way.

The firmware is the operating system of the Flipper Zero and usually also contains various apps. In addition to the official version, there are now quite a few alternatives with various additional functions and customizations. There are many resources on these topics on Github. One of the most useful collections is [awesome-flipperzero](https://github.com/djsime1/awesome-flipperzero).

An overview of the most common firmware variants is summarized in the following table.

Update methods
--------------

There are various methods for [updating the firmware](https://docs.flipper.net/basics/firmware-update):

*   Flipper mobile app for [iOS](https://play.google.com/store/apps/details?id=com.flipperdevices.app) and for [Android](https://play.google.com/store/apps/details?id=com.flipperdevices.app)
*   Desktop application [qFlipper](https://docs.flipper.net/qflipper) (Windows, macOS, Linux)
*   Update via a browser with the [Web Updater](https://lab.flipper.net/), whereby the browser must support the [Web Serial API](https://caniuse.com/web-serial)
*   Update directly in the pinball machine itself with an update on the SD card
*   Update via the WiFi devboard
*   Update with the firmware build tool (see next section)

Flipper Zero firmware normally consists of various components: _Radio Stack_, _Hardware Abstraction Layer_ (HAL), _Operating System_ (OS), _Driver_ and _Applications_.

Most firmware distributions include the [Firmware Build Tool](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/fbt.md) `fbt`, which comes from the original firmware and is essentially a wrapper for [SCons](https://scons.org/). This tool is very useful because it can obtain a ready-made toolchain directly from the Internet and allows you to compile and install the Flipper firmware with a simple command. Using the Xtreme firmware as an example, it is shown below how this firmware is compiled and installed on a Flipper Zero.

First clone the git repository, which is currently approx. 670 MB in size: `$ git clone https://github.com/Flipper-XFW/Xtreme-Firmware.git`

Linux recognizes a Flipper Zero connected to the USB port as a Virtual Serial USB Device under `/dev/ttyACM0` (the number can also be larger), for which the kernel module `cdc_acm` is responsible.

With the help of `fbt`, the compilation and subsequent installation of the generated firmware on the pinball machine can be combined in one command: `./Xtreme-Firmware/fbt COMPACT=1 DEBUG=0 flash_usb_full`

When this command is executed for the first time, `fbt` first loads the toolchain, consisting of the GNU compiler for ARM and associated tools and libraries, and stores it under `./Xtreme-Firmware/toolchain`. In addition, several submodules, including the FreeRTOS kernel, are automatically obtained from Github. Now the entire firmware is generated as a “self-update package” with all resources, i.e. including all apps, and stored in the directory `./Xtreme-Firmware/dist/f7-C/`. Several files are generated, whereby the file `firmware.dfu` is the actual firmware and the file `resources.tar` contains the apps and other resources. If `fbt` finds a connected pinball machine, it will be updated automatically. If you only want to create the update package without installing it, the `updater_package` option must be used instead of `flash_usb_full`.

Probably the best-known hardware extension for the Flipper Zero is the [WiFi Devboard](https://shop.flipperzero.one/products/wifi-devboard). It offers a system-on-a-chip (SoC) platform based on the _ESP32-S2_ [chipset](https://www.espressif.com/en/products/modules) from the manufacturer Espressiv, which offers 2.4 GHz WiFi connectivity and contains its own CPU.

![WiFi Devboard with connections and buttons](https://www.scip.ch/labs/images/devboard.jpg "WiFi Devboard with connections and buttons")

The Wifi Devboard uses its own firmware and can be controlled via apps on the pinball machine. The board is connected to the Flipper Zero via the GPIO PINs.

Functionality
-------------

The standard firmware of the WiFi Devboard contains [Black Magic Debug](https://black-magic.org/), which enables debugging of the Flipper Zero firmware based on the _GNU Debugger_ (GDB). The WiFi Devboard acts as a GDB server and can be accessed via WiFi or USB interface. With the standard firmware, no functionalities for WiFi network analysis or penetration testing are available.

Updating the firmware
---------------------

_Standard firmware_

The standard firmware of the WiFi devboard is very easy to update with the [micro Flipper Build Tool](https://pypi.org/project/ufbt) (uFBT) Python module. It is installed as follows: `python -m pip install --upgrade ufbt`

Now connect the board via USB. Then press and hold the BOOT button on the board and then press the RESET button, then release the BOOT button. The devboard now appears as a device under `/dev/ttyACM0`. Update the firmware with the following command: `python3 -m ufbt devboard_flash`

Then press the RESET button, disconnect and reconnect the USB connection and the devboard will appear as a serial device and is ready.

_Alternative firmware_

If you want to use the WiFi devboard for _offensive purposes_, you need the appropriate firmware. The best known are [Marauder](https://github.com/justcallmekoko/ESP32Marauder), which contains various offensive and defensive WiFi tools, and [Evil Portal](https://github.com/bigbrodude6119/flipper-zero-evil-portal), which implements an access point with a captive portal for collecting access data. Both repositories contain pre-compiled `.bin` files, which can be installed with the [Marauder Flasher](https://github.com/SkeletonMan03/FZEasyMarauderFlash) (automatically) or with the web-based tool [https://esp.huhn.me/](https://esp.huhn.me/). The Xtreme firmware also offers the option of installing the Marauder or Evil Portal firmware on the WiFi devboard directly from the pinball machine using an app, but this did not work properly in our tests. The Flipper Zero itself requires apps to interact with the WiFi Devboard, which are already included in the _Xtreme_ firmware.

Note: The latest versions of Marauder now also include an Evil Portal function, but this seems to require an SD card connected directly to the ESP32 and therefore does not work with the WiFi Devboard.

Compile and install source code
-------------------------------

If you want to make adjustments to the firmware of the WiFi devboard, you must then compile the source code and install the firmware created in this way on the devboard. The following sections show how this is done using the Marauder firmware as an example.

### Installing the development tools for Arduino

1.  The first step is to install the development environment (IDE) for Arduino. There are various packages for Linux, macOS and Windows on the [Arduino website](https://www.arduino.cc/en/software). When the IDE is started for the first time, various packages are automatically loaded and installed.
2.  Now the following “Board manager URLs” must be added under `File > Preferences`:
    *   https://dl.espressif.com/dl/package\_esp32\_index.json
    *   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package\_esp32\_dev\_index.json  
        ![Arduino IDE with additional board manager URLs](https://www.scip.ch/labs/images/add_board_manager_urls.png "Arduino IDE with additional board manager URLs")
3.  Next, search for esp32 under `Tools > Board > Boards Manager`. Now select version 2.0.14 from the search result “esp32 by Espressif Systems” and click on the INSTALL button.  
    ![Installation of the ESP32 board support](https://www.scip.ch/labs/images/esp32_support.png "Installation of the ESP32 board support")
4.  Now a few adjustments must be made to the compiler settings. To do this, open the file `~/.arduino15/packages/esp32/hardware/esp32/2.0.14/platform.txt` in an editor.
5.  Add the `-w` flag to all the following settings:
    *   `build.extra_flags.esp32`
    *   `build.extra_flags.esp32s2`
    *   `build.extra_flags.esp32s3`
    *   `build.extra_flags.esp32c3`
6.  Add the flag `-zmuldefs` to all the following settings:
    *   `compiler.c.elf.libs.esp32`
    *   `compiler.c.elf.libs.esp32s2`
    *   `compiler.c.elf.libs.esp32s3`
    *   `compiler.c.elf.libs.esp32c3`
7.  The following libraries must now be downloaded as zip files from Github and installed in the Arduino IDE via the menu `Sketch > Include Library > Add .ZIP Library...`. The Arduino IDE can then automatically update these libraries and displays a message when an update is available.
    *   [lv\_arduino](https://github.com/lvgl/lv_arduino)
    *   [LinkedList](https://github.com/ivanseidel/LinkedList)
    *   [TFT\_eSPI](https://github.com/justcallmekoko/TFT_eSPI)
    *   [JPEGDecoder library](https://github.com/Bodmer/JPEGDecoder)
    *   [NimBLE](https://github.com/h2zero/NimBLE-Arduino)
    *   [NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
    *   [ArduinoJson](https://github.com/bblanchon/ArduinoJson/releases) (select the Source code… file here and not the ArduinoJson-v… file)
    *   [SwitchLib](https://github.com/justcallmekoko/SwitchLib/releases/latest)
    *   [ESPAsyncWebServer](https://github.com/bigbrodude6119/ESPAsyncWebServer)
    *   [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
    *   [MicroNMEA](https://github.com/stevemarple/MicroNMEA)
    *   [EspSoftwareSerial](https://github.com/plerup/espsoftwareserial)
8.  The Arduino ESP32 filesystem uploader is required to upload the firmware to the devboard. To do this, download the [latest release](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases) and place it in the correct directory with the following command: `unzip ESP32FS-1.1.zip -d ~/Arduino/tools` The result should then look like this: `~/Arduino/tools/ESP32FS/tool/esp32fs.jar`
9.  Now the source code of Marauder can be downloaded: `git clone https://github.com/justcallmekoko/ESP32Marauder.git`

Finally, the file `esp32_marauder.ino` can be opened in the Arduino IDE, which opens the entire source code in the IDE. Now select the file `configs.h` and remove the comment character from the line `//#define MARAUDER_FLIPPER` in the BOARD TARGETS section (approx. line 19). All other lines in this section should be commented out. The source code can now be edited.

Compilation is carried out with the menu command `Sketch > Verify/Compile`. If the error `ModuleNotFoundError: No module named 'serial'` occurs, the Python module [pyserial](https://pypi.org/project/pyserial/) must be installed.

### Install firmware

1.  To install the firmware on the WiFi devboard, it must be connected to a USB port and then set to firmware download mode: Press and hold the BOOT button on the board and then press the RESET button, then release the BOOT button.
2.  Now select the devboard in the Arduino IDE via the `Menu Tools > Port`, it should be displayed as `/dev/ttyACM0 (ESP32S2 Dev Module)`.
3.  In the menu `Tools > Board > esp32` select the entry `ESP32S3 Dev Module`.
4.  In the menu `Tools > Partition Scheme` select the entry `Minimal SPIFFS (1.9 MB App with OTA/190KB SPIFFS)`.
5.  In the `Sketch` menu, select the `Upload` command, which writes the firmware to the devboard. If the error message `A fatal error occurred: Could not open /dev/ttyACM0, the port doesn't exist` appears, the authorizations of the port `/dev/ttyACM0` should be checked and adjusted if necessary. Then restart the devboard using the RESET button and the new firmware will be executed.

Compiling and installing firmware for the Flipper Zero and for the WiFi Devboard yourself is perfectly feasible. The official firmware for the pinball machine contains an _easy-to-use tool_ that makes compilation and installation very simple. On the other hand, the initial setup of a development environment for the WiFi Devboard is relatively complicated and requires various libraries to be installed manually. Once this has been mastered and all the necessary tools have been installed, future _compilations and installations are quite simple_.

About the Author
----------------

[

![Tomaso Vasella](https://www.scip.ch/_img/team/medium/tova.jpg "Tomaso Vasella")

](https://www.scip.ch/en/?team.tova)

_Tomaso Vasella_ has a Master in _Organic Chemistry_ at ETH Zürich. He is working in the cybersecurity field since 1999 and worked as a consultant, engineer, auditor and business developer. ([ORCID 0000-0002-0216-1268](https://orcid.org/0000-0002-0216-1268))

Links
-----

*   [https://black-magic.org/](https://black-magic.org/)
*   [https://caniuse.com/web-serial](https://caniuse.com/web-serial)
*   [https://docs.flipper.net/basics/firmware-update](https://docs.flipper.net/basics/firmware-update)
*   [https://docs.flipper.net/qflipper](https://docs.flipper.net/qflipper)
*   [https://esp.huhn.me/](https://esp.huhn.me/)
*   [https://github.com/Bodmer/JPEGDecoder](https://github.com/Bodmer/JPEGDecoder)
*   [https://github.com/ClaraCrazy/Flipper-Xtreme](https://github.com/ClaraCrazy/Flipper-Xtreme)
*   [https://github.com/DXVVAY/xvirus-firmware](https://github.com/DXVVAY/xvirus-firmware)
*   [https://github.com/DarkFlippers/unleashed-firmware](https://github.com/DarkFlippers/unleashed-firmware)
*   [https://github.com/Korai-Labs/Korai](https://github.com/Korai-Labs/Korai)
*   [https://github.com/RogueMaster/flipperzero-firmware-wPlugins](https://github.com/RogueMaster/flipperzero-firmware-wPlugins)
*   [https://github.com/SkeletonMan03/FZEasyMarauderFlash](https://github.com/SkeletonMan03/FZEasyMarauderFlash)
*   [https://github.com/adafruit/Adafruit\_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
*   [https://github.com/bblanchon/ArduinoJson/releases](https://github.com/bblanchon/ArduinoJson/releases)
*   [https://github.com/bigbrodude6119/ESPAsyncWebServer](https://github.com/bigbrodude6119/ESPAsyncWebServer)
*   [https://github.com/bigbrodude6119/flipper-zero-evil-portal](https://github.com/bigbrodude6119/flipper-zero-evil-portal)
*   [https://github.com/djsime1/awesome-flipperzero](https://github.com/djsime1/awesome-flipperzero)
*   [https://github.com/flipperdevices/flipperzero-firmware](https://github.com/flipperdevices/flipperzero-firmware)
*   [https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/fbt.md](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/fbt.md)
*   [https://github.com/h2zero/NimBLE-Arduino](https://github.com/h2zero/NimBLE-Arduino)
*   [https://github.com/haisenteck/flipperzero-Haisenteck](https://github.com/haisenteck/flipperzero-Haisenteck)
*   [https://github.com/ivanseidel/LinkedList](https://github.com/ivanseidel/LinkedList)
*   [https://github.com/justcallmekoko/ESP32Marauder](https://github.com/justcallmekoko/ESP32Marauder)
*   [https://github.com/justcallmekoko/SwitchLib/releases/latest](https://github.com/justcallmekoko/SwitchLib/releases/latest)
*   [https://github.com/justcallmekoko/TFT\_eSPI](https://github.com/justcallmekoko/TFT_eSPI)
*   [https://github.com/lvgl/lv\_arduino](https://github.com/lvgl/lv_arduino)
*   [https://github.com/me-no-dev/AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
*   [https://github.com/me-no-dev/arduino-esp32fs-plugin/releases](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases)
*   [https://github.com/plerup/espsoftwareserial](https://github.com/plerup/espsoftwareserial)
*   [https://github.com/skizzophrenic/SquachWare-CFW](https://github.com/skizzophrenic/SquachWare-CFW)
*   [https://github.com/stevemarple/MicroNMEA](https://github.com/stevemarple/MicroNMEA)
*   [https://lab.flipper.net/](https://lab.flipper.net/)
*   [https://play.google.com/store/apps/details?id=com.flipperdevices.app](https://play.google.com/store/apps/details?id=com.flipperdevices.app)
*   [https://pypi.org/project/pyserial/](https://pypi.org/project/pyserial/)
*   [https://pypi.org/project/ufbt](https://pypi.org/project/ufbt)
*   [https://scons.org/](https://scons.org/)
*   [https://shop.flipperzero.one/products/wifi-devboard](https://shop.flipperzero.one/products/wifi-devboard)
*   [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
*   [https://www.espressif.com/en/products/modules](https://www.espressif.com/en/products/modules)
*   [https://www.scip.ch/?labs.20221201](https://www.scip.ch/?labs.20221201)