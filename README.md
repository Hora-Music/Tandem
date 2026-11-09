# Tandem

Firmware for **Tandem**, a two-channel multimode CV generator for Eurorack (12 HP) by Hora-Music. Each channel can be an LFO, an ADSR envelope, a 16-step pitch sequencer or an accent-style bassline envelope, and the two channels can be patched into each other internally.

## Documentation

| Document | Formats |
|---|---|
| Owner's manual | [Markdown](docs/Tandem-Owner-Manual.md) · [PDF](docs/Tandem-Owner-Manual.pdf) · [HTML](docs/Tandem-Owner-Manual.html) |
| Building and flashing the firmware | [Markdown](docs/Firmware-Build-Guide.md) · [PDF](docs/Firmware-Build-Guide.pdf) |

## Related repositories

- Tandem libraries (`GC_…`): <https://github.com/Hora-Music/TandemLibraries>
- Hardware design files (EAGLE): <https://github.com/Hora-Music/Tandem-Hardware>

## Flash without compiling

You do not need the Arduino IDE, the core or any library to update a module. A ready-built firmware image is in this repository:

```
build/Arduino_STM32.STM32F1.genericSTM32F103C/Tandem.ino.bin
```

Write it to address **`0x08000000`** with either tool below. See sections 8 and 9 of the [build guide](docs/Firmware-Build-Guide.md) for the wiring, the BOOT0 jumper and powering the module.

**STM32CubeProgrammer** (free, from ST — <https://www.st.com/en/development-tools/stm32cubeprog.html>)

1. Choose **UART**, set your COM port and 115200 baud, then click **Connect**.
2. On the **Erasing & Programming** page, select `Tandem.ino.bin` and set the start address to `0x08000000`.
3. Click **Start Programming**, then **Disconnect**.

**stm32flash** (command line, serial only — <https://sourceforge.net/projects/stm32flash/>)

```
stm32flash -w Tandem.ino.bin -v -g 0x08000000 -b 115200 COM6
```

Replace `COM6` with your adapter's port. Put the BOOT0 jumper back on GND when you are done.

## Building from source

See the [build guide](docs/Firmware-Build-Guide.md): Arduino IDE 2.x, the Arduino_STM32 core (Generic STM32F103C series, STM32F103CB variant) and the libraries listed there.

## License

The Tandem firmware and its documentation are free software, released under the **GNU General Public License v3.0 or later** — see [LICENSE](LICENSE).

You may use, study, modify and share them, including commercially, as long as anything you distribute that contains this code (modified firmware, or modules that ship with it) is released under the same license with its complete source code, and keeps the original copyright notices.

Versions published before this license change were released under the MIT license and remain available under it.

## Trademarks

**"Tandem"**, **"Hora-Music"** and the Hora-Music logo are names and marks of Hora-Music. They are **not** covered by the GPL or any other license in this repository.

You may say that a product is "based on the Hora-Music Tandem" to describe where it comes from. You may not sell, distribute or promote a module, kit, PCB, panel or modified firmware under the names "Tandem" or "Hora-Music", or with the Hora-Music logo, without written permission. Derived products must use a different name and must not suggest they are made or endorsed by Hora-Music.
