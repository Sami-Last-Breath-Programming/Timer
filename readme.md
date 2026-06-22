# ⏱️ Terminal Timer

> A lightweight, terminal-based countdown timer written in **C** with audio notification support.

![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS-lightgrey?style=flat-square)
![Audio](https://img.shields.io/badge/Audio-miniaudio-orange?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)


## ✨ Features

- ⏳ **Custom Countdown** – Define hours, minutes, and seconds via CLI arguments
- 🖥️ **Live Terminal Display** – Auto-refreshes using `clear` for a clean countdown view
- 🔊 **Audio Alert** – Plays & loops a custom `.mp3` alarm when time reaches zero
- ⌨️ **Interactive Stop** – Press `Enter` to silence the alarm and exit gracefully
- 🛡️ **Robust Error Handling** – Graceful exits for memory, engine, sound, and argument failures
- 🧹 **Clean Memory Management** – Proper allocation, initialization, and cleanup of all structures


## 📦 Project Structure

```
.
├── assets/
│   └── sound.mp3          # Alarm audio file
├── build/
│   └── timer              # Compiled executable
├── lib/
│   ├── clangFlags.h       # Clang diagnostic & flag configurations
│   ├── errorsTimer.h      # Custom error message macros
│   └── miniaudio.h        # Single-header audio playback library
├── timer.c                # Main application source
└── README.md              # Project documentation
```


## 🛠️ Prerequisites

- **Operating System:** Linux or macOS (POSIX-compliant)
- **Compiler:** `clang` (recommended) or `gcc`
- **Terminal:** Supports `clear` command & standard I/O
- **Dependencies:**
  - `miniaudio` (bundled in `lib/`)
  - Standard C libraries (`stdio`, `stdlib`, `unistd`)


## 🚀 Build Instructions

1. Navigate to the project root:
   ```bash
   cd ~/Programs/Timer
   ```
2. Compile with Clang (Linux flags for `miniaudio`):
   ```bash
   clang timer.c -o build/timer -lm -lpthread -ldl
   ```

   *(macOS users can typically omit `-lpthread -ldl`)*


## 💡 Usage

Run the binary with **three positional arguments**: `<hours> <minutes> <seconds>`

```bash
./build/timer 0 5 30   # 5 minutes & 30 seconds
./build/timer 1 0 0    # 1 hour
./build/timer 0 0 10   # 10 seconds
```

### 🎵 Runtime Behavior

- ⏱️ Countdown updates every second in `HH : MM : SS` format
- 🔔 At `00 : 00 : 00`, the alarm sound starts looping
- ⏹️ Press **`Enter`** to stop the sound and terminate the program
- ❌ Invalid arguments or missing files will trigger descriptive error messages & safe exit


## ⚠️ Important Notes

- 🔗 **Hardcoded Audio Path:** The sound file path is currently absolute in `timer.c`:
  ```c
  const char soundPath[] = "/home/lbs/Programs/Timer/assets/sound.mp3";
  ```

  Update this line to match your environment, or refactor to accept a dynamic path.
- 🖥️ **Terminal Compatibility:** Relies on `system("clear")`. Works best in standard POSIX terminals.
- 📦 **Single-Header Audio:** `miniaudio` is compiled in implementation mode. No external audio packages or system dependencies are required.
- 🔒 **Memory Safety:** All `malloc` allocations are checked, and `ma_engine`/`ma_sound` are properly uninitialized & freed before exit.


## 📜 License

Distributed under the **MIT License**. See `LICENSE` for more information.


<div align="center">
  Readme is from Ai but this buggy code is handwritten !!
</div>
