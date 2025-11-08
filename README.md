```markdown
# CoreX-microkernel

A UNIX-like microkernel for the i386 / i686 architecture with an included Doom platform glue so you can run Doom (or port it) on the kernel.

This repository contains:
- kernel sources under `kernel/` (CORE kernel implementation)
- simple userland programs and platform apps under `apps/`, `user/`, and `servers/`
- a small libc implementation under `libc/`
- boot-related files under `boot/`
- Doom platform glue in `apps/doomgeneric.h` and `apps/doomgeneric_yourplatform.c`
- build artifacts are expected in `build/` (the default linker script is `build/linker.ld`)

Status
------
Work-in-progress. This is an experimental UNIX-like microkernel for i386/i686 and includes helpers to run Doom as a bundled app/platform port.

Important: The kernel is still under development and not yet production-ready. Expect incomplete features, instability, and frequent changes to APIs and build processes.

Prerequisites
-------------
- A C cross toolchain targeting i686 (recommended): e.g., `i686-elf-gcc` / `i686-elf-binutils` OR host gcc with 32-bit multilib support.
- GNU Make
- QEMU for running the kernel: `qemu-system-i386`
- Optional (for ISO/GRUB): `grub-mkrescue` (grub2)

Recommended packages (Debian/Ubuntu example):
```sh
sudo apt-get install build-essential gcc-multilib qemu-system-i386 grub-pc-bin grub-common
# or, if using a cross toolchain:
sudo apt-get install gcc-multilib binutils-multiarch
# and/or install an i686 cross toolchain such as:i686-elf-gcc toolchain (how you install depends on distro)
```

Top-level layout
----------------
- kernel/        — kernel sources (C, assembly)
- apps/          — small applications and Doom platform glue
- user/          — user programs
- servers/       — server programs
- libc/          — small libc sources
- boot/          — bootloader / boot helpers
- build/         — build output and (by default) linker script: `build/linker.ld`

Building
--------
The repository includes a Makefile at the project root that:
- discovers C/C++/assembly sources under the main folders and compiles them into a parallel `build/` tree
- links kernel objects into an ELF and produces a raw binary
- builds simple standalone apps from `apps/`, `user/`, and `servers/`
- provides an explicit `doom` target to build the Doom platform glue

Basic build examples:

Build everything (kernel + apps) with the default toolchain:
```sh
make
```

Build with a cross-toolchain prefix (recommended for reproducible i686 builds):
```sh
make CROSS_COMPILE=i686-elf-
```

If your linker script is not at the default location (the Makefile defaults to `build/linker.ld`), set it explicitly:
```sh
make LINKER_SCRIPT=kernel/arch/x86/linker.ld
```

Build apps only (apps, user, servers):
```sh
make apps
```

Build the Doom platform glue (convenience target):
```sh
make doom
# resulting binary: build/apps/doomgeneric_yourplatform
```

What the Makefile expects by default
-----------------------------------
- LINKER_SCRIPT defaults to `build/linker.ld` (per the repo layout). If you keep a different linker script path or name, set `LINKER_SCRIPT` when invoking make.
- The Makefile treats any `.c` files under `apps/`, `user/`, and `servers/` as simple standalone programs and will place their outputs under `build/apps/`, `build/user/`, and `build/servers/` respectively.
- The kernel is linked from all discovered kernel/object files (excluding per-file app objects).

Running in QEMU
---------------
Run the kernel ELF directly with QEMU:
```sh
make run
# runs qemu-system-i386 -kernel build/corex.elf -m 512M -serial stdio -no-reboot
```

If you want a GRUB ISO (multiboot kernels), update your linker script / kernel to include a Multiboot header and then create an ISO (Makefile can be adapted to add ISO target). Ensure `grub-mkrescue` is installed.

Doom integration (apps/doomgeneric_*)
-------------------------------------
This repository contains:
- `apps/doomgeneric.h` — Doom platform interface header the Doom engine expects
- `apps/doomgeneric_yourplatform.c` — example glue implementations that map the Doom platform hooks to the kernel (stubs / placeholders are provided)

The `doom` target in the Makefile will build the platform glue as a standalone binary:
```sh
make doom
# -> build/apps/doomgeneric_yourplatform
```

Note: The Doom engine itself is not included in this repository. To run Doom on CoreX you will need to:
1. Provide/compile the Doom engine sources or a Doom binary that uses the `doomgeneric.h` platform functions.
2. Integrate or link the engine with the platform glue provided here, adapting the glue code to your kernel's graphics, timing, and input subsystems.

Customizing for your environment
-------------------------------
- Toolchain: set `CROSS_COMPILE` to your toolchain prefix (e.g. `i686-elf-`) or remove `-m32` flags in `CFLAGS` to build with your host toolchain.
- Linker script: set `LINKER_SCRIPT` to the correct path (default `build/linker.ld`).
- Add or change CFLAGS/LDFLAGS in the Makefile as needed for your toolchain, ABI, or CPU features.

Troubleshooting
---------------
- "missing linker script" — either create `build/linker.ld` or pass `LINKER_SCRIPT=` to `make`.
- Build errors about 32-bit headers/libs when using host gcc — install multilib support or use a cross-toolchain.
- QEMU errors — confirm `qemu-system-i386` is installed and that the kernel image is valid.

Contributing
------------
Contributions, bug reports, and pull requests are welcome. Please:
- open issues for bugs or feature requests,
- create PRs against the `main` branch,
- include build logs and steps to reproduce when reporting build-related issues.

License
-------
See `LICENSE` in this repository for license details.

Contact
-------
Repository owner: discoveryos

Acknowledgements
----------------
- This repository is experimental and educational. The Doom glue is provided as a convenience to demonstrate running a complex app on the kernel — you will need to provide or port the Doom engine itself and adapt the glue to your kernel's APIs.
```
