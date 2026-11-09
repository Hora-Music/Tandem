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

MIT — see the header of `Tandem.ino`.
