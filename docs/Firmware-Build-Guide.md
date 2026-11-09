# Tandem — Building and Flashing the Firmware

This guide takes you from a bare computer to a Tandem running freshly compiled firmware: installing the tools, getting the right libraries, compiling, connecting to the module, uploading, and preparing the microSD card.

It is written for Windows with the Arduino IDE 2.x. The same steps work on macOS and Linux; only the paths and the serial port names change.

---

## 1. What you need

**Software**

- Arduino IDE 2.x — <https://www.arduino.cc/en/software>
- The Arduino_STM32 core by Roger Clark (not the official STMicroelectronics core)
- The Tandem firmware — <https://github.com/Hora-Music/Tandem>
- The Tandem libraries — <https://github.com/Hora-Music/TandemLibraries>
- Four third-party libraries (section 4)

**Hardware design files**

The schematics and board layouts (EAGLE) for the main board, the control board and the panel are at <https://github.com/Hora-Music/Tandem-Hardware>. You need them only to locate the programming headers (section 8) or to build a module yourself.

**Hardware**

- A Eurorack case or power supply to power the module while you program it
- A USB-to-serial adapter with **3.3 V logic** (CP2102, CH340, FTDI…) and three jumper wires
- A jumper cap for the BOOT header
- A microSD card (FAT32), for running the module afterwards

---

## 2. Install the Arduino IDE and the compiler

1. Install Arduino IDE 2.x and start it once, then close it.
2. Open it again, go to **Tools → Board → Boards Manager**, search for **Arduino SAM Boards (32-bits ARM Cortex-M3)** and install it.
   The Tandem does not use these boards, but this package brings the ARM compiler (`arm-none-eabi-gcc 4.8.3-2014q1`) that the Arduino_STM32 core relies on.

## 3. Install the Arduino_STM32 core

The core is not in the Boards Manager; it is installed by hand into your sketchbook.

1. Download <https://github.com/rogerclarkmelbourne/Arduino_STM32> (**Code → Download ZIP**).
2. Unzip it and rename the folder `Arduino_STM32-master` to **`Arduino_STM32`**.
3. Move it into the `hardware` folder of your sketchbook (create `hardware` if it does not exist):

   ```
   Documents\Arduino\hardware\Arduino_STM32\
       STM32F1\
       STM32F4\
       drivers\
       tools\
   ```

4. Restart the IDE. **Tools → Board** now lists an **STM32F1 Boards (Arduino_STM32)** section containing **Generic STM32F103C series**.

> The firmware was last built with the core reporting itself as `STM32F1 Boards (STM32duino.com)`, version 0.1.2.

---

## 4. Install the libraries

Tandem needs fifteen libraries. Four come with the core, seven are the Hora-Music libraries, and four come from the internet.

| Library | Version | Where it comes from | What Tandem uses it for |
|---|---|---|---|
| SPI, Wire, EEPROM, STM32ADC | bundled | Arduino_STM32 core | DAC and SD bus, settings storage, fast ADC with DMA |
| GC_ControlScan, GC_CV_mixer, GC_gate_mixer, GC_OctaLFO, GC_Envelope, GC_Sequencer, GC_StepSequencer | — | [Hora-Music/TandemLibraries](https://github.com/Hora-Music/TandemLibraries) | Buttons and knobs, CV/gate routing, LFO, envelopes, sequencers |
| SdFat | **1.1.0** exactly | Bill Greiman — Library Manager or [github.com/greiman/SdFat](https://github.com/greiman/SdFat/releases/tag/1.1.0) | Presets and pitch tables on the microSD card |
| Adafruit GFX Library | 1.5.6 (tested) | Adafruit — Library Manager | Drawing on the OLED |
| SH1106 | 1.0.0, **patched** | [github.com/winneymj/SH1106](https://github.com/winneymj/SH1106) | OLED driver (`SH1106.h`) |
| MegunoLink | 1.28 (tested) | Library Manager, or [github.com/Megunolink/MLP](https://github.com/Megunolink/MLP) | `Filter.h`, the smoothing filters for knobs and CV inputs |

### 4.1 Tandem libraries

1. Download <https://github.com/Hora-Music/TandemLibraries> (**Code → Download ZIP**, or `git clone`).
2. Copy every `GC_…` folder into the core's own library folder:

   ```
   Documents\Arduino\hardware\Arduino_STM32\STM32F1\libraries\
       GC_ControlScan\
       GC_CV_mixer\
       GC_Envelope\
       GC_gate_mixer\
       GC_OctaLFO\
       GC_Sequencer\
       GC_StepSequencer\
       ...
   ```

   Putting them next to the core's libraries keeps them away from boards they were not written for. `GC_ControlScan_Synth` and `GC_DrumSampler` belong to other projects; copying them does no harm.

### 4.2 SdFat 1.1.0

In **Library Manager**, search **SdFat**, choose the one by **Bill Greiman**, pick version **1.1.0** in the version list, and install.

Do not use SdFat 2.x. The firmware relies on the 1.x API (`SdFat(SPIClass*)`, `ifstream`/`ofstream` from `sdios.h`) and will not compile against 2.x.

### 4.3 Adafruit GFX Library

In **Library Manager**, search **Adafruit GFX Library** and install version **1.5.6**. If the IDE offers to install dependencies, you can accept.

Newer versions may work but have not been tested with this core.

### 4.4 SH1106 (with one-line patch)

1. Download <https://github.com/winneymj/SH1106> as a ZIP and unzip it into `Documents\Arduino\libraries\SH1106-master\`.
2. Open `SH1106-master\SH1106.cpp` in a text editor. Find this line (around line 120):

   ```cpp
   #define SH1106_swap(a, b) { int16_t t = a; a = b; b = t; }
   ```

3. Add this line right below it, and save:

   ```cpp
   #define swap(a, b) { int16_t t = a; a = b; b = t; }
   ```

   Recent Adafruit GFX versions no longer define `swap()`, which this driver still uses. Without the patch the build stops with `'swap' was not declared in this scope`.

### 4.5 MegunoLink

In **Library Manager**, search **MegunoLink** and install it (1.28 is the tested version). Tandem only uses its `Filter.h`.

### 4.6 Watch out for duplicate libraries

If you have several copies of the same library in `Documents\Arduino\libraries` (for example `SdFat-master` with SdFat 2.x next to `SdFat-1.1.0`, or `Adafruit_SH1106-master` next to `SH1106-master`), the IDE may pick the wrong one. After compiling, read the end of the output panel:

```
Multiple libraries were found for "SdFat.h"
  Used: ...\libraries\SdFat-1.1.0
  Not used: ...\libraries\SdFat-master
```

Make sure the **Used** lines point to the versions in the table above. If not, move the other copies out of the `libraries` folder.

---

## 5. Get the firmware

Clone or download <https://github.com/Hora-Music/Tandem> into your sketchbook so that the folder is called **`Tandem`** (the Arduino IDE requires the folder name to match `Tandem.ino`):

```
Documents\Arduino\Tandem\
    Tandem.ino
    Setting.cpp, Setting.h, ...
```

Open `Tandem.ino` in the Arduino IDE. All the other `.ino` files open as tabs.

---

## 6. Board settings

In the **Tools** menu:

| Setting | Value |
|---|---|
| Board | **Generic STM32F103C series** |
| Variant | **STM32F103CB (20k RAM. 128k Flash)** |
| Upload method | **Serial** |
| CPU Speed | **72Mhz (Normal)** |
| Optimize | **Smallest (default)** |
| Port | The COM port of your USB-to-serial adapter |

The **STM32F103CB** variant matters: the firmware is about 106 KB and does not fit in the 64 KB of the C8 variant.

With `arduino-cli`, the same settings are this FQBN:

```
Arduino_STM32:STM32F1:genericSTM32F103C:device_variant=STM32F103CB,upload_method=serialMethod,cpu_speed=speed_72mhz,opt=osstd
```

---

## 7. Compile

Click **Verify** (the check mark). A successful build ends with something like:

```
Sketch uses 106312 bytes (81%) of program storage space. Maximum is 131072 bytes.
```

To keep the binary, use **Sketch → Export Compiled Binary**. It is written to `Tandem\build\Arduino_STM32.STM32F1.genericSTM32F103C\Tandem.ino.bin`. A ready-built binary is also kept in that folder of the repository.

### If the build fails

| Message | Cause | Fix |
|---|---|---|
| `GC_controlScan.h: No such file or directory` (or any `GC_…`) | Tandem libraries missing | Section 4.1 |
| `Filter.h: No such file or directory` | MegunoLink missing | Section 4.5 |
| `SH1106.h: No such file or directory` | SH1106 missing | Section 4.4 |
| `'swap' was not declared in this scope` | SH1106 not patched | Section 4.4, step 3 |
| Errors in `SdFat`, `sdios.h`, `ofstream`, `SdFat(SPIClass*)` | SdFat 2.x picked up | Section 4.2 and 4.6 |
| `Sketch too big` / `region rom overflowed` | Wrong variant | Choose STM32F103CB (section 6) |
| `arm-none-eabi-g++: not found` | Compiler missing | Install Arduino SAM Boards (section 2) |
| Board not in the list | Core in the wrong folder | Check `Documents\Arduino\hardware\Arduino_STM32\STM32F1\boards.txt` exists |

---

## 8. Connect to the module (serial method)

All programming connections are on the **main board** (the board with the STM32 chip), on the side facing away from the panel. Labels below are those printed on that board. The main-board schematic and layout in [Tandem-Hardware](https://github.com/Hora-Music/Tandem-Hardware) show exactly where each header is.

| Header | Label | Pins | Use |
|---|---|---|---|
| Serial header (1×6) | **SERIAL PROG** | **GND**, **TX** (PA9), **RX** (PA10) | Serial upload |
| BOOT header (2×3) | **BOOT** | 3V3 — BOOT0 — GND, and 3V3 — BOOT1 — GND | Selects the bootloader |
| Push button | RESET | — | Restarts the processor |

> **Power.** Power the module from your Eurorack supply while you program it. Do **not** connect the adapter's 5 V or 3.3 V pin to the module. Use an adapter with 3.3 V logic levels.

1. Switch the rack **off**.
2. Wire the adapter to **SERIAL PROG**, crossing TX and RX:

   | Adapter | Tandem SERIAL PROG |
   |---|---|
   | GND | GND |
   | RX | **TX** |
   | TX | **RX** |

3. On the **BOOT** header, move the BOOT0 jumper from **GND** to **3V3**. Leave BOOT1 on GND.
4. Plug the adapter into the computer and note its COM port (Device Manager → Ports). Select it in **Tools → Port**.
5. Switch the rack **on**. The screen stays dark: the processor is waiting in its serial bootloader.

## 9. Upload

### 9.1 From the Arduino IDE

1. Click **Upload** (the arrow). The IDE compiles, then runs `stm32flash`. A good upload ends with:

   ```
   Wrote address 0x08019f48 (100.00%) Done.
   Starting execution at address 0x08000000... done.
   ```

2. Switch the rack **off**, move the BOOT0 jumper back to **GND**, and remove the adapter.
3. Switch the rack on. The screen shows **HORA - TANDEM**, then the main menu.

If you forget step 2, the module will start in the bootloader again (dark screen) at the next power-up.

**Upload problems**

| Message | Fix |
|---|---|
| `Failed to init device` / `Timeout` | BOOT0 not on 3V3, TX/RX not crossed, or the module was powered before the jumper was moved. Fix it, press RESET (or power-cycle), and upload again. |
| `Cannot open COMx` | Wrong port, or another program (serial monitor) has it open. |
| Works once, then not again | Press **RESET** on the main board before each upload while BOOT0 is on 3V3. |

### 9.2 Flash without compiling

You do not need the Arduino IDE, the core or any library to update a module. The repository holds a ready-built firmware image:

```
build/Arduino_STM32.STM32F1.genericSTM32F103C/Tandem.ino.bin
```

Write it to address **`0x08000000`** with either tool below. Wire and power the module as in section 8 first, and put the BOOT0 jumper back on GND afterwards.

**STM32CubeProgrammer** (free, from ST — <https://www.st.com/en/development-tools/stm32cubeprog.html>; Windows, macOS, Linux)

1. Choose **UART** in the connection panel, set your COM port and 115200 baud, then click **Connect**.
2. Open the **Erasing & Programming** page, select `Tandem.ino.bin`, and set the start address to `0x08000000`.
3. Click **Start Programming**, then **Disconnect**.

**stm32flash** (command line, serial only — <https://sourceforge.net/projects/stm32flash/>; also included with the Arduino_STM32 core in `tools\win`)

```
stm32flash -w Tandem.ino.bin -v -g 0x08000000 -b 115200 COM6
```

Replace `COM6` with your adapter's port (on macOS or Linux, something like `/dev/ttyUSB0`). The `.elf` and `.map` files in the same folder are not needed.

---

## 10. Prepare the microSD card

The firmware reads and writes files in fixed folders and does not create them itself.

1. Format the card as **FAT32**.
2. Create these folders at the root of the card:

   ```
   Presets\BANK_A\  …  Presets\BANK_P\     (16 folders)
   P_MEM\
   P_MEM\CV_tables\
   ```

   In PowerShell, with the card on drive `E:`:

   ```powershell
   'A'..'P' | ForEach-Object { New-Item -ItemType Directory -Force "E:\Presets\BANK_$_" }
   New-Item -ItemType Directory -Force "E:\P_MEM\CV_tables"
   ```

3. Insert the card into the slot on the panel before switching the rack on. Empty preset slots load as empty presets, so a blank card works; save your first presets from the module.

To move a setup to another Tandem, copy the whole card.

## 11. First start after flashing

1. Check the start-up screen and the main menu appear.
2. Run the **pitch calibration** (hold **PATCH** while switching on; see the owner's manual). Until a pitch table exists on the card, the step sequencer's notes are not in tune.
3. Optionally run the **CV input calibration** (hold **2** while switching on, with no cables plugged in).

Your presets and pitch tables live on the microSD card, so reflashing the firmware does not erase them.

---

## Appendix — Where things are on this setup

| Item | Path |
|---|---|
| Sketchbook | `Documents\Arduino\` |
| Firmware | `Documents\Arduino\Tandem\` |
| Hardware design files | <https://github.com/Hora-Music/Tandem-Hardware> |
| Arduino_STM32 core | `Documents\Arduino\hardware\Arduino_STM32\` |
| Tandem libraries | `Documents\Arduino\hardware\Arduino_STM32\STM32F1\libraries\GC_…` |
| Third-party libraries | `Documents\Arduino\libraries\` (`SdFat-1.1.0`, `Adafruit-GFX-Library`, `SH1106-master`, `MLP-master`) |
| ARM compiler | `%LOCALAPPDATA%\Arduino15\packages\arduino\tools\arm-none-eabi-gcc\4.8.3-2014q1\` |
| Upload tools | `Documents\Arduino\hardware\Arduino_STM32\tools\win\` (`stm32flash.exe`) |
