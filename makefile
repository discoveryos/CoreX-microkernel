# Makefile for discoveryos/CoreX-microkernel
# - Recursively builds sources in: kernel, apps, user, servers, libc, boot, docs
# - Builds kernel ELF and raw binary
# - Builds simple standalone apps from apps/, user/, servers/
# - Includes Doom glue in apps/ (apps/doomgeneric.h + apps/doomgeneric_yourplatform.c)
# - Linker script default is in the build/ folder (build/linker.ld)
#
# Usage:
#  make                       # build kernel and apps (host toolchain; may require -m32 support)
#  make CROSS_COMPILE=...     # e.g. CROSS_COMPILE=i686-elf-
#  make LINKER_SCRIPT=path    # override linker script path (default: build/linker.ld)
#  make doom                  # build doom glue app (if present)
#  make run                   # run kernel ELF in QEMU
#  make clean
#
# To push this Makefile into the repository tell me and I can create a branch & PR.

# --- Toolchain / build config ---
CROSS_COMPILE ?= i686-elf-
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
AR := $(CROSS_COMPILE)ar
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

BUILD_DIR := build
KERNEL_ELF := $(BUILD_DIR)/corex.elf
KERNEL_BIN := $(BUILD_DIR)/corex.bin

# Linker script is located inside the build/ folder by default per repo layout
LINKER_SCRIPT ?= $(BUILD_DIR)/linker.ld

# Keep an explicit list of top-level folders so they appear in the Makefile
ALL_TOP_DIRS := kernel apps user servers libc boot docs
SRCDIRS := $(ALL_TOP_DIRS)

INCLUDE_DIRS := kernel/include include

# --- Flags (adjust as needed) ---
# Default flags targeting i386/i686 freestanding kernel; override CFLAGS when needed
CFLAGS ?= -m32 -march=i686 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -Wall -Wextra -O2 -g $(patsubst %,-I%,$(INCLUDE_DIRS))
CPPFLAGS ?= $(CFLAGS) -fno-rtti
ASFLAGS ?= -m32 -x assembler-with-cpp $(patsubst %,-I%,$(INCLUDE_DIRS))

# Use CC to link kernel so toolchain-specific flags are honored
LDFLAGS ?= -m32 -Wl,-T,$(LINKER_SCRIPT) -nostdlib -static

# App link flags (simple static userland apps)
APPLDFLAGS ?= -m32 -static -nostdlib

QEMU ?= qemu-system-i386
GRUB_MKRESCUE ?= grub-mkrescue

# --- Discover sources ---
SRC_C   := $(shell find $(SRCDIRS) -type f -name '*.c' 2>/dev/null)
SRC_CPP := $(shell find $(SRCDIRS) -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' \) 2>/dev/null)
SRC_ASM := $(shell find $(SRCDIRS) -type f \( -name '*.S' -o -name '*.s' \) 2>/dev/null)

# Map sources to parallel build tree
OBJ_C   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_C))
OBJ_CPP := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC_CPP)) \
           $(patsubst %.cc,$(BUILD_DIR)/%.o,$(filter %.cc,$(SRC_CPP))) \
           $(patsubst %.cxx,$(BUILD_DIR)/%.o,$(filter %.cxx,$(SRC_CPP)))
OBJ_ASM := $(patsubst %.S,$(BUILD_DIR)/%.o,$(filter %.S,$(SRC_ASM))) \
           $(patsubst %.s,$(BUILD_DIR)/%.o,$(filter %.s,$(SRC_ASM)))

ALL_OBJS := $(OBJ_C) $(OBJ_CPP) $(OBJ_ASM)

# Treat apps/, user/, servers/ files as standalone apps; exclude their objects from kernel linking
OBJS := $(filter-out $(BUILD_DIR)/apps/%.o $(BUILD_DIR)/user/%.o $(BUILD_DIR)/servers/%.o,$(ALL_OBJS))

# Include libc objects (if any) into kernel link
LIBC_OBJS := $(filter $(BUILD_DIR)/libc/%,$(ALL_OBJS))
OBJS := $(OBJS) $(LIBC_OBJS)

# App collections (per-folder)
APP_DIRS := apps user servers
APPS_SRCS := $(shell find $(APP_DIRS) -maxdepth 2 -type f -name '*.c' 2>/dev/null)
APPS_BINS := $(patsubst apps/%.c,$(BUILD_DIR)/apps/%,$(filter apps/%.c,$(APPS_SRCS))) \
             $(patsubst user/%.c,$(BUILD_DIR)/user/%,$(filter user/%.c,$(APPS_SRCS))) \
             $(patsubst servers/%.c,$(BUILD_DIR)/servers/%,$(filter servers/%.c,$(APPS_SRCS)))

# Doom glue
DOOM_GLUE_SRC := apps/doomgeneric_yourplatform.c
DOOM_GLUE_HDR := apps/doomgeneric.h
DOOM_GLUE_BIN := $(BUILD_DIR)/apps/doomgeneric_yourplatform

# --- Targets ---
.PHONY: all kernel apps doom run clean distclean info help

all: kernel apps

kernel: $(KERNEL_ELF) $(KERNEL_BIN)

# Warn if linker script is missing (helpful)
$(KERNEL_ELF): $(OBJS) $(LINKER_SCRIPT)
	@mkdir -p $(dir $@)
	@if [ ! -f $(LINKER_SCRIPT) ]; then echo "[WARN] linker script '$(LINKER_SCRIPT)' not found."; fi
	@echo "[LD] $@"
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

# Raw binary image
$(KERNEL_BIN): $(KERNEL_ELF)
	@mkdir -p $(dir $@)
	@echo "[OBJCOPY] $@"
	$(OBJCOPY) -O binary $< $@

# Generic compile rules into the parallel build/ tree
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "[CC] $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "[CXX] $<"
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	@echo "[CXX] $<"
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cxx
	@mkdir -p $(dir $@)
	@echo "[CXX] $<"
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	@echo "[AS] $<"
	$(CC) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	@echo "[AS] $<"
	$(CC) $(ASFLAGS) -c $< -o $@

# --- Apps: link each simple app per-file into build/<folder>/<name> ---
apps: $(APPS_BINS)
	@echo "[APPS] built $(words $(APPS_BINS)) app(s)"

# apps/ -> build/apps/
$(BUILD_DIR)/apps/%: apps/%.c
	@mkdir -p $(dir $@)
	@echo "[APP] $@"
	$(CC) $(CFLAGS) $(APPLDFLAGS) -o $@ $< || (echo "App link failed: $<"; false)

# user/ -> build/user/
$(BUILD_DIR)/user/%: user/%.c
	@mkdir -p $(dir $@)
	@echo "[USER] $@"
	$(CC) $(CFLAGS) $(APPLDFLAGS) -o $@ $< || (echo "App link failed: $<"; false)

# servers/ -> build/servers/
$(BUILD_DIR)/servers/%: servers/%.c
	@mkdir -p $(dir $@)
	@echo "[SERVER] $@"
	$(CC) $(CFLAGS) $(APPLDFLAGS) -o $@ $< || (echo "Server link failed: $<"; false)

# --- Doom target: explicit build of the doom platform glue ---
doom: $(DOOM_GLUE_BIN)
	@echo "[DOOM] Doom glue built at $(DOOM_GLUE_BIN)"

$(DOOM_GLUE_BIN): $(DOOM_GLUE_SRC) $(DOOM_GLUE_HDR)
	@mkdir -p $(dir $@)
	@echo "[DOOM] linking $@"
	$(CC) $(CFLAGS) $(APPLDFLAGS) -o $@ $(DOOM_GLUE_SRC) || (echo "Doom glue build failed"; false)

# --- Run kernel in QEMU ---
run: all
	@echo "[RUN] starting qemu with $(KERNEL_ELF)"
	$(QEMU) -kernel $(KERNEL_ELF) -m 512M -serial stdio -no-reboot

# --- Utilities ---
info:
	@echo "Build info:"
	@echo "  TOP DIRS: $(ALL_TOP_DIRS)"
	@echo "  CROSS_COMPILE: $(CROSS_COMPILE)"
	@echo "  CC: $(CC)"
	@echo "  LINKER_SCRIPT: $(LINKER_SCRIPT)"
	@echo "  Kernel ELF: $(KERNEL_ELF)"
	@printf "  C sources found: %s\n" "$(words $(SRC_C))"
	@printf "  ASM sources found: %s\n" "$(words $(SRC_ASM))"
	@printf "  App C sources found: %s\n" "$(words $(APPS_SRCS))"

help:
	@sed -n '1,240p' $(firstword $(MAKEFILE_LIST))

clean:
	@echo "[CLEAN] removing $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

distclean: clean
	@echo "[DISTCLEAN] done"
