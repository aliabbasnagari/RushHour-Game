BUILD_DIR := build

.PHONY: all build run clean

all: build

build:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	cmake --build $(BUILD_DIR) --config Release

run: build
	cmake --build $(BUILD_DIR) --target run --config Release

clean:
	rm -rf $(BUILD_DIR)
