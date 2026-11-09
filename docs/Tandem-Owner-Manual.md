# Tandem — Owner's Manual

**Hora-Music · Multimode CV generator**

<img src="images/screen-boot.png" alt="Start-up screen: HORA - TANDEM" width="320">

Tandem is a two-channel multimode CV generator. Each channel can be an LFO, an ADSR envelope, a 16-step pitch sequencer or an accent-style bassline envelope, and the two channels can be patched into each other without cables.

Each channel has its own set of four jacks: a gate input, a CV input, a gate output and a CV output. You pick a mode for each channel in the main menu, then edit it with the four knobs and the buttons around the screen. Whole setups (both modes, every parameter and the internal patching) are stored as presets on a microSD card.

| Format | Channels | Modes | Presets | CV outputs | Display |
|---|---|---|---|---|---|
| 12 HP Eurorack | 2 | 4 per channel | 16 banks × 32 | 12-bit | 128 × 64 OLED |

## Contents

1. [The panel](#the-panel)
2. [Finding your way](#finding-your-way)
3. [Main menu](#main-menu)
4. [Saving presets](#saving-presets)
5. [Internal patching](#internal-patching)
6. [LFO](#lfo)
7. [Envelope](#envelope)
8. [Step sequencer](#step-sequencer)
9. [Bassline envelope](#bassline-envelope)
10. [CV modulation](#cv-modulation)
11. [Example patches](#example-patches)
12. [Power-up utilities](#power-up-utilities)
13. [microSD card](#microsd-card)
14. [Quick reference](#quick-reference)

---

## The panel

<img src="images/panel.svg" alt="Tandem front panel" width="300" align="right">

Channel 1 is marked in white, channel 2 in amber.

### Knobs

| | Knob | Function |
|---|---|---|
| **K1** | PRESET · POS (top left) | Picks the preset in the main menu; first parameter of the channel being edited (rate, attack, step position…). |
| **K2** | BANK · NOTE (top right) | Picks the bank (A–P) in the main menu; second parameter when editing (waveform, decay, note…). |
| **K3** | Lower left | Picks the mode of channel 1 in the main menu; third parameter when editing. |
| **K4** | Lower right | Picks the mode of channel 2 in the main menu; fourth parameter when editing. |

### Buttons

| Button | Function |
|---|---|
| **MAIN** | Opens the main menu from anywhere. In the main menu, opens the save screen. |
| **SELECT · WRITE** | Loads the chosen preset. In the modes: reset, manual gate, or write a step. |
| **PATCH · SLIDE** | Opens internal patching from the main menu. In the modes: snap, knob function, or slide. |
| **REST** | Confirms the channel 1 mode and answers YES in dialogs. In the modes: CV page, gate length. |
| **CLK DIV** | Confirms the channel 2 mode and answers NO in dialogs. In the modes: output polarity, or the sequencer's clock page. |
| **1** | Edits channel 1. Its light shows which channel you are editing. |
| **2** | Edits channel 2. |

### Other

| | |
|---|---|
| **Screen** | 128 × 64 OLED. The words in its corners name what the nearest button does on that page. |
| **microSD slot** | Holds the presets and pitch tables. Leave a card in the slot while the module runs. |

### Jacks

The top row holds the inputs (marked **I**), the bottom row the outputs (marked **O**). In each pair, the left jack (⎍) carries gates and the right jack (∿) carries CV.

| | Channel 1 (white) | Channel 2 (amber) |
|---|---|---|
| Inputs ⎍ | **Gate in 1** — trigger, gate or clock | **Gate in 2** |
| Inputs ∿ | **CV in 1** — modulation | **CV in 2** |
| Outputs ⎍ | **Gate out 1** — triggers and gates | **Gate out 2** |
| Outputs ∿ | **CV out 1** — the channel's signal | **CV out 2** |

<br clear="right">

---

## Finding your way

Tandem has four kinds of page. You will spend most of your time on the edit pages.

| Page | How to get there | What it is for |
|---|---|---|
| **Main menu** | Press **MAIN** from any page. Tandem also starts here. | Load presets, pick the mode of each channel. |
| **Edit** | In the main menu, press **1** or **2**. | Set the parameters of one channel. **1** and **2** switch channel. |
| **Patch** | In the main menu, press **PATCH**. | Connect outputs to inputs internally. |
| **Save** | In the main menu, press **MAIN** again. | Name and store the current setup. |

### Knob pick-up

Each time you change page or channel, the knobs are parked: turning a knob a little does nothing, so the values you just left stay where they were. Once you turn a knob past about a tenth of its travel, it takes over and the parameter jumps to the knob's position.

### Value read-outs

On the edit pages, a knob's label (RATE, ATT, SUS…) turns into its value, 0 to 127, while you turn it, and goes back to the label a few seconds after you let go.

### Restart

Hold **MAIN** down for a moment to restart the module. It comes back on the last preset you loaded.

---

## Main menu

The screen is laid out like the knobs above and below it.

| Preset loaded | Browsing |
|---|---|
| <img src="images/screen-mainLoaded.png" alt="Main menu, preset loaded" width="340"> | <img src="images/screen-mainBrowse.png" alt="Main menu while browsing" width="340"> |
| Preset 5 of bank A is loaded: the name and the bank letter are filled in. | **K1** has moved to preset 6. Its name stays outlined until you press **SELECT**. |

| Screen area | Shows | Set with |
|---|---|---|
| Number, top left | Preset number, 0–31 | **K1** |
| Bar below it | Preset name | follows **K1** |
| Letter, top right | Bank, A–P | **K2** |
| Patch icon, top right | Reminder that **PATCH** opens patching | |
| Box, lower left | Mode of channel 1 | **K3** |
| Box, lower right | Mode of channel 2 | **K4** |

### Load a preset

1. Turn **K2** to pick a bank and **K1** to pick a preset. The name appears as you turn.
2. Press **SELECT** to load it. Name and bank letter turn solid.

If you do not press **SELECT**, the display goes back to the loaded preset after about five seconds.

### Change a channel's mode

| <img src="images/mode0.png" alt="LFO icon" width="110"> | <img src="images/mode1.png" alt="Envelope icon" width="110"> | <img src="images/mode2.png" alt="Bassline envelope icon" width="110"> | <img src="images/mode3.png" alt="Step sequencer icon" width="110"> |
|:---:|:---:|:---:|:---:|
| LFO | Envelope | Bassline envelope | Step sequencer |

1. Turn **K3** (channel 1) or **K4** (channel 2) until the icon of the mode you want appears. Its frame disappears and the icon blinks: the change is not active yet.
2. Press **REST** to confirm channel 1, or **CLK DIV** to confirm channel 2.
3. Tandem asks for confirmation. Press **REST** for YES or **CLK DIV** for NO.

| Mode change waiting | Confirmation dialog |
|---|---|
| <img src="images/screen-modePending.png" alt="Main menu with a mode change waiting" width="340"> | <img src="images/screen-confirmModel.png" alt="Model confirmation dialog" width="340"> |
| Channel 2 turned to LFO and waiting for **CLK DIV**. | YES and NO sit next to the two lower buttons (**REST** / **CLK DIV**). |

> **Note.** Confirming a mode resets that channel to the mode's default settings. Save first if you want to keep what you had.

### Edit a channel

Press **1** or **2**. The light in that button turns on and the screen shows the channel's edit page. If a mode change is still waiting for confirmation, finish or cancel it first. Press **MAIN** to come back.

---

## Saving presets

A preset holds both modes, all their settings and the internal patching. It is saved into the bank that is currently loaded.

<img src="images/screen-save.png" alt="Save screen with character grid" width="420">

| Control | On the save screen |
|---|---|
| **K1** | Pick a character in the grid |
| **K2** | Move along the name |
| **K3** / **K4** | Destination slot |
| **WRITE** (SELECT) | Enter the character |
| **PATCH** | Back (`<<`), without saving |

1. In the main menu, press **MAIN**. The save screen opens with the current name.
2. Turn **K3** or **K4** to choose the destination slot, 0–31. The number blinks when it differs from the loaded preset, which means you are about to save to another slot.
3. To rename: turn **K2** to move the cursor along the name, turn **K1** to highlight a character, and press **WRITE** to enter it. The cursor moves on by one letter. Names are 11 characters: A–Z, 0–9, underscore and space.
4. Press **MAIN**. Tandem asks `SAVE?`
5. Press **REST** for YES or **CLK DIV** for NO.

Press **PATCH** at any time on the save screen to leave without saving.

---

## Internal patching

Send either channel's outputs into the inputs, with no cables. Connections are saved with the preset.

<img src="images/screen-routing.png" alt="Patch screen" width="420">

The circles are drawn like the jacks: inputs on top, outputs below, channel 1 on the left. Solid lines are connections. The blinking line is the pair you have selected but not yet connected.

| Row | Circle 1 | Circle 2 | Circle 3 | Circle 4 |
|---|---|---|---|---|
| Top: inputs | Gate in 1 | CV in 1 | Gate in 2 | CV in 2 |
| Bottom: outputs | Gate out 1 | CV out 1 | Gate out 2 | CV out 2 |

1. In the main menu, press **PATCH**.
2. Turn **K1** or **K2** to select an input (top row), and **K3** or **K4** to select an output (bottom row).
3. Press **SELECT** (or **1** or **2**) to connect them. Press again to disconnect.
4. Press **PATCH** to go back to the main menu.

An internal connection is combined with whatever is plugged into the same input jack. An output can feed several inputs, and an input can receive several outputs.

---

## LFO

A free-running low-frequency oscillator with eight waveforms you can morph between, a reset input and a trigger output.

<img src="images/screen-lfo.png" alt="LFO edit page" width="420">

One full cycle of the LFO is drawn across the screen. The square rides along with the output. The line with the arrowheads and the number is the phase; the second line is the trigger point.

| Control | Function |
|---|---|
| **K1** Rate | Speed of the LFO. |
| **K2** Wave | Morphs through the eight shapes below. While you turn it, the shape appears at the top of the screen in place of `WAV`. |
| **K3** Phase | The point of the cycle the LFO jumps to when it is reset. |
| **K4** Trig | The point of the cycle where gate out fires a short trigger, once per cycle. |
| **SELECT** | Resets the LFO to its phase point. On channel 1 it also switches the drawing between the LFO and a scope of CV in 1 (the corner reads `Scop` or `Lfo`, naming the view you will get). |
| **PATCH** | `Snap`: when on (shown inverted), **K2** steps between the eight pure shapes instead of morphing. On channel 2, when channel 1 is also an LFO, this button sets `SYNC` instead: LFO 2 follows the timing of LFO 1, and an `S` appears in the top right corner. |
| **REST** | Opens the [CV page](#cv-modulation). Press again to come back. |
| **CLK DIV** | Output polarity: `Bi` (swings above and below 0 V) or `Uni` (positive only). |

### Waveforms

In the order **K2** reaches them, from fully left:

| <img src="images/wave0.png" width="60" alt="Sine"> | <img src="images/wave1.png" width="60" alt="Ramp down"> | <img src="images/wave2.png" width="60" alt="Arch"> | <img src="images/wave3.png" width="60" alt="Triangle"> | <img src="images/wave4.png" width="60" alt="Square"> | <img src="images/wave5.png" width="60" alt="Bounce"> | <img src="images/wave6.png" width="60" alt="Ramp up"> | <img src="images/wave7.png" width="60" alt="Stepped random"> |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| Sine | Ramp down | Arch | Triangle | Square | Bounce | Ramp up | Stepped random |

### Jacks

- **Gate in**: a rising edge resets the LFO to the phase point.
- **CV in**: modulation, set up on the CV page.
- **Gate out**: a short trigger each time the LFO passes the trigger point.
- **CV out**: the LFO.

---

## Envelope

An ADSR envelope with an adjustable curve and an end-of-stage trigger.

<img src="images/screen-env.png" alt="Envelope edit page" width="420">

The curve is drawn from the attack, decay and release settings. The two lines inside the curve mark the end of attack and the end of decay; the line at the end marks where the trigger output fires (here: end of release). The square follows the output. The ▶ in the top left corner stands for **SELECT**, the ← in the top right corner for **PATCH**.

| Control | Function |
|---|---|
| **K1** Att | Attack time. |
| **K2** | Does one of three jobs. Press **PATCH** to step through them; the label above the knob changes. `DEC` decay time · `SHAPE` curve, from exponential (left) to linear (right) · `TRIG` when gate out fires: end of attack (left third), end of decay (middle) or end of release (right third). |
| **K3** Sus | Sustain level. |
| **K4** Rel | Release time. |
| **SELECT** | Manual gate: the envelope runs while you hold the button. |
| **REST** | Opens the [CV page](#cv-modulation). |
| **CLK DIV** | Output: `Uni` (positive), `Bi` (shifted to swing around 0 V) or `Inv` (inverted). |

### Jacks

- **Gate in**: the envelope attacks when the gate goes high, holds at sustain while it stays high, and releases when it goes low.
- **CV in**: modulation, set up on the CV page.
- **Gate out**: a short trigger at the end of the stage chosen with `TRIG`. Patch it back into a gate input to chain or loop envelopes.
- **CV out**: the envelope.

---

## Step sequencer

Up to 16 steps of pitch, each with its own gate, gate length and slide. It moves one step for each clock received at gate in.

<img src="images/screen-seq.png" alt="Step sequencer edit page" width="420">

Top: the step being edited and its note. Then one box per step: a filled mark means the step plays, and the bar under it shows the gate length. The tall bars are the pitches; the outlined one is the step under **K1** and the inverted one is the step playing now. Small ticks at the bottom are slides. Bottom: root and length.

| Control | Function |
|---|---|
| **K1** Pos | Chooses the step to edit (`POS:` 1–16). The knob's travel is spread over the current length. |
| **K2** Note | Pitch of that step, over about two and a half octaves. The note name and octave show at the top right. |
| **K3** Root | Transposes the whole sequence in semitones (`ROOT:`). |
| **K4** Length | Number of steps, 1–16, shown bottom right. The step boxes stretch to fill the screen. |
| **WRITE** | Turns the selected step on or off. Steps that are off play no gate. |
| **SLIDE** | Turns slide on or off for the selected step: the pitch glides into the next note. |
| **REST** | Switches the selected step between a short gate and a long gate. |
| **CLK DIV** | Opens the clock page. Press again to come back. |
| **1** / **2** | Switch channel. |

### Clock page

<img src="images/screen-seqClock.png" alt="Sequencer clock page" width="320">

- **WRITE** steps through the clock divisions: 1, 1/2, 1/3, 1/4, 1/6, 1/8, 1/12, 1/16. At 1/4 the sequence advances once every four clocks.
- **REST** sets the direction: `FWD` forward, `BWD` backward, `RND` random.
- **CLK DIV** goes back to the step page.

### Jacks

- **Gate in**: clock. Each rising edge (after division) moves one step.
- **Gate out**: the gate of each active step.
- **CV out**: pitch, 1 V/oct, using the pitch table chosen at power-up (see [Pitch calibration](#pitch-calibration)).
- **CV in**: not used by this mode.

---

## Bassline envelope

A snappy decay envelope with accents, made to work with a step sequencer on the other channel.

<img src="images/screen-bass.png" alt="Bassline envelope edit page" width="420">

Top: the other channel's sequence, with a mark above each accented step and a frame above the step selected with **K1**. Below: three dials for attack, decay and the accent setting.

| Control | Function |
|---|---|
| **K1** | Selects a step of the other channel's sequence. |
| **SELECT** | Turns the accent on or off for that step. Accents are stored with the sequencer channel. |
| **K2** | Does one of three jobs. Press **PATCH** to step through them. `accent` / `gap`: in the left half, how much louder accented notes are; in the right half (shown as `gap`), the normal notes get louder and the difference to the accents shrinks. `Hard.`: how sharply the accent hits. `Length`: how long the accent lasts. |
| **K3** | Attack time. |
| **K4** | Decay time. |

If the other channel is not a step sequencer, the top of the screen reads `Use a sequencer on ch 2 for accent's seq` (or ch 1). The envelope still works from its gate input, without accents.

### Jacks

- **Gate in**: fires the envelope. Usually the sequencer's gate out, patched internally.
- **CV out**: the envelope, with accents added.

---

## CV modulation

In LFO and envelope modes, both CV inputs can modulate the channel. Each input gets its own destination and amount.

<img src="images/screen-cvPage.png" alt="CV modulation page" width="420">

The CV page of an LFO: CV in 1 bends the rate, CV in 2 morphs the waveform.

1. On the LFO or envelope page, press **REST**.
2. Turn **K1** to choose what CV in 1 changes and **K2** for CV in 2. LFO: `RATE`, `WAVE`, `PHASE`, `T-POS`. Envelope: `Attack`, `Decay`, `Sustain`, `Release`.
3. Turn **K3** and **K4** to set how much each input changes it (0–127).
4. Press **REST** to go back.

The CV is added to the knob setting. With the level at 0, the input has no effect. Internal patches into the CV inputs (see [Internal patching](#internal-patching)) go through the same settings.

---

## Example patches

Three starting points. Build them, then save each one as a preset.

### Acid line, one cable for the clock

1. Main menu: set channel 1 to **step sequencer** and channel 2 to **bassline envelope**.
2. **PATCH**: connect Gate out 1 to Gate in 2.
3. Patch a clock into **Gate in 1**, **CV out 1** to your oscillator's pitch input and **CV out 2** to a VCA or filter cutoff.
4. Program notes, slides and long gates on channel 1, then go to channel 2 and add accents with **K1** and **SELECT**.

### Two LFOs in step

1. Set both channels to **LFO**.
2. Edit channel 2 and press **PATCH** until `SYNC` shows. LFO 2 now follows LFO 1.
3. Give them different waveforms and phase points. Patch a clock or a reset gate into **Gate in 1** if you want both restarted together.

### Envelope that speeds up an LFO

1. Set channel 1 to **envelope** and channel 2 to **LFO**.
2. **PATCH**: connect CV out 1 to CV in 2.
3. Edit channel 2, press **REST**, set **K2** to `RATE` and raise **K4**.
4. Each gate into **Gate in 1** now sweeps the LFO's speed.

---

## Power-up utilities

Hold a button while you switch the rack on to start one of these tools. Switch off and on again to return to normal use.

| Hold at power-up | Starts |
|---|---|
| **MAIN** | Tuner and scope |
| **SELECT** | Pitch table selection |
| **PATCH** | Pitch calibration of the CV outputs |
| **2** | CV input calibration |

### Tuner and scope

| Tuner | Scope |
|---|---|
| <img src="images/screen-tuner.png" alt="Tuner" width="340"> | <img src="images/screen-scope.png" alt="Scope" width="340"> |
| The oscillator on Gate in 1 reads 110 Hz, an A in tune. The one on Gate in 2 is a little sharp: the dash sits to the right of the note. | CV in 1 and CV in 2 drawn together. |

- **Tuner.** Patch an oscillator's square or pulse output into **Gate in 1** or **Gate in 2**. The frequency and note name appear on the left for input 1 and on the right for input 2. A dash before the note means flat, after it means sharp. While the tuner runs, CV out 1 plays a square wave one octave below the signal on Gate in 1.
- **Scope.** Press **MAIN** to switch between tuner and scope. The scope draws the signals on **CV in 1** and **CV in 2**. Turn **K4** to change the time scale.

### Pitch calibration

The step sequencer plays pitch from a table that matches the CV outputs to your oscillator. Tandem builds that table itself by listening to the oscillator. You can store four tables and pick one later.

1. Tune your oscillator low, around 16–30 Hz with nothing in its pitch input.
2. Hold **PATCH** and switch the rack on. The screen reads `calib`.
3. Patch **CV out 1** to the oscillator's 1 V/oct input, and the oscillator's square output into **Gate in 1**. Tandem sweeps the output upward and records the voltage for each note. The screen shows the measured frequency and the last value stored.
4. When it asks, patch **CV out 2** to the oscillator and the oscillator into **Gate in 2**, then press **MAIN**.
5. When channel 2 is done, a list of the four table slots appears. Turn **K1** to choose a slot and press **MAIN**. That slot becomes the active table.
6. Name the table as you would a preset (**K1** character, **K2** position, **WRITE** to enter) and press **MAIN**. The table is saved to the card.

| Calibration running | Prompt for channel 2 |
|---|---|
| <img src="images/screen-calibProgress.png" alt="Calibration in progress" width="340"> | <img src="images/screen-calibCh2.png" alt="Calibration prompt for channel 2" width="340"> |
| Calibration running on channel 1. | The prompt to move the cables to channel 2. The text wraps on the real screen too. |

### Pitch table selection

<img src="images/screen-tables.png" alt="Pitch table selection" width="320">

The filled bar is the active table; the frame follows **K1**. Table names here are examples.

1. Hold **SELECT** and switch the rack on.
2. Turn **K1** to frame a table, then press **MAIN** to make it active.
3. Switch off and on again.

### CV input calibration

Trims the CV inputs so that an unplugged input reads exactly zero. Most modules never need it.

1. Unplug every cable from Tandem.
2. Hold **2** and switch the rack on. The screen asks you to unplug the jacks.
3. Press any other button. A percentage counts up for about ten seconds, then the screen reads `Calibration done`.
4. Switch off and on again.

---

## microSD card

Presets and pitch tables live on the card in plain files, so you can back them up or copy them between modules from a computer. Switch the rack off before you remove the card.

| Path | Contents |
|---|---|
| `Presets/BANK_A` … `BANK_P/` | One folder per bank |
| `Presets/BANK_A/preset_00.gcp` … `preset_31.gcp` | One file per preset |
| `P_MEM/pmem.pmem` | The last preset loaded, recalled at power-up |
| `P_MEM/CV_tables/CV_Table01.cvt` … `04` | The four pitch tables |
| `P_MEM/name_list_0.cvt` … `3` | Pitch table names |

Keep the folder structure exactly as it is. A preset slot with no file loads as an empty preset.

---

## Quick reference

What every control does on every page. Entries in *italics* apply to the step sequencer's clock page.

| | Main menu | LFO | Envelope | Step sequencer | Bassline env. | CV page |
|---|---|---|---|---|---|---|
| **K1** | Preset | Rate | Attack | Step (Pos) | Step to accent | CV 1 destination |
| **K2** | Bank | Wave | Decay / Shape / Trig | Note | Accent / Hardness / Length | CV 2 destination |
| **K3** | Mode ch 1 | Phase | Sustain | Root | Attack | CV 1 level |
| **K4** | Mode ch 2 | Trig point | Release | Length | Decay | CV 2 level |
| **Select** | Load preset | Reset · scope (ch 1) | Manual gate | Step on/off · *clock div.* | Accent on/off | – |
| **Patch** | Patch page | Snap · Sync (ch 2) | K2 function | Slide on/off | K2 function | – |
| **Rest** | Confirm mode ch 1 · YES | CV page | CV page | Short/long gate · *direction* | – | Back |
| **Clk div** | Confirm mode ch 2 · NO | Bi / Uni | Uni / Bi / Inv | Clock page | – | Polarity |
| **1 / 2** | Edit channel | Switch channel | Switch channel | Switch channel | Switch channel | – |
| **Main** | Save page | Back to main menu | Back to main menu | Back to main menu | Back to main menu | Back to main menu |
| **Gate in** | – | Reset | Gate | Clock | Trigger | – |
| **Gate out** | – | Trigger at trig point | End-of-stage trigger | Step gates | – | – |

*Screens in this manual are drawn from the module's firmware with example settings.*
