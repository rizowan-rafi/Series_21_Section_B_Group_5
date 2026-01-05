# 🍚 kacchiOS

A minimal, educational multitasking operating system kernel built from scratch.

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![Platform](https://img.shields.io/badge/platform-x86-lightgrey.svg)]()

## 📖 Overview

kacchiOS is a bare-metal operating system kernel designed to demonstrate the core fundamentals of OS architecture. Unlike standard educational skeletons, this version implements **true multitasking**, **dynamic memory management**, and **process scheduling**.

It serves as a functional proof-of-concept for:
* **Memory Management:** Heap allocation (`kmalloc`) and deallocation (`kfree`).
* **Process Management:** Process Control Blocks (PCB), state transitions, and stack forging.
* **Context Switching:** Low-level x86 assembly to swap CPU states between tasks.

### ✅ Implemented Features

#### 1. Memory Manager
* **Dynamic Allocation:** Implemented a First-Fit allocator.
* **Heap:** Manages a 64KB heap for kernel structures and process stacks.
* **Stack Management:** Automatically allocates and frees stack memory for every new process.
* **Deallocation:** Supports `kfree()` with block coalescing (merging free blocks) to prevent fragmentation.

#### 2. Process Manager
* **PCB Structure:** Tracks Process ID (PID), Stack Pointer (SP), and Process State.
* **State Machine:** Handles transitions between `UNUSED`, `READY`, `CURRENT`, and `TERMINATED`.
* **Lifecycle:** * `create_process()`: Forges an initial stack frame to "fake" an interrupt return.
    * `terminate_process()`: Safely cleans up resources and memory when a task finishes.

#### 3. Scheduler
* **Round Robin Policy:** Fairly cycles through all `READY` processes.
* **Context Switch:** Optimized x86 assembly (`ctx_switch`) to save/restore General Purpose Registers (GPRs) using `pusha` and `popa`.
* **Cooperative Multitasking:** Tasks yield control using `schedule()`.

#### 4. I/O & Drivers
* **Serial Port (COM1):** Integrated serial driver for kernel logging and debugging via QEMU `stdio`.

## 🚀 Quick Start

### Prerequisites

* **Compiler:** `gcc` (with 32-bit support via `gcc-multilib`)
* **Linker:** `ld`
* **Emulator:** `qemu-system-i386`
* **Build Tool:** `make`

### Build and Run

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/rizowan-rafi/Series_21_Section_B_Group_5.git](https://github.com/rizowan-rafi/Series_21_Section_B_Group_5.git)
    cd Series_21_Section_B_Group_5
    ```

2.  **Navigate to Source:**
    ```bash
    cd src
    ```

3.  **Build and Run:**
    ```bash
    make clean
    make
    make run
    ```

### Expected Output

You will see the Kernel Boot Log, followed by the Scheduler interleaving the tasks. **Task C** will run briefly, terminate itself, and then **Task A** and **Task B** will continue forever.

```text
--- kacchiOS Booting (Slow Mode) ---
[Process Manager] Creating PID 1...
   -> State: READY
   -> Stack Allocated: 2048 bytes

Processes created. Starting Scheduler...

[Scheduler] Context Switch:
   PID 1 (READY)   -> CURRENT
 [Task A] is running...

[Scheduler] Context Switch:
   PID 1 (CURRENT) -> READY
   PID 2 (READY)   -> CURRENT
 [Task B] is running...

 [Task C] Countdown: 3
 ...
 [Task C] Work done. Killing self...
[Process Manager] PID 3 Terminated. (State: TERMINATED)


## Project Structure

```text
kacchiOS/
├── src/
│   ├── kernel.c
│   ├── memory.c
│   ├── memory.h
│   ├── process.c
│   ├── process.h
│   ├── scheduler.c
│   ├── scheduler.h
│   ├── serial.c
│   ├── serial.h
│   ├── types.h
│   ├── boot.S
│   ├── link.ld
│   └── Makefile
├── docs/
│   ├── Project_Report.pdf
│   └── Checklist.pdf
├── video/
│   └── Demo_Video.mp4
└── README.md

