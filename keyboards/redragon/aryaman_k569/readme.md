# Redragon Aryaman K569

![Redragon Aryaman K569]()

Keyboard Maintainer: [DEREFERENC3D](https://github.com/DEREFERENC3D)

Hardware Supported: VS11K13A (rebranded SN32F268)

Make example for this keyboard (after setting up your build environment):

    make redragon/aryaman_k569:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Always works, including on stock firmware, but bothersome:
* **Boot pin**: Short the MCU's `BOOT` pin to ground, then plug in the keyboard

If the jumploader is installed:
* **Jumploader reset**: Hold down the Escape key and plug in the keyboard

If QMK is installed:
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
