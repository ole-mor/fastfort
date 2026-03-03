# --- CMake Wrapper Makefile ---

# Default target: builds the project
all:
	@cmake -B build -S .
	@cmake --build build
	@./build/fastfort

build:
	@cmake -B build -S .
	@cmake --build build

# Quick run (builds first, then runs)
run: build
	@./build/fastfort

# Clean build artifacts
clean:
	@rm -rf build

.PHONY: all run clean
