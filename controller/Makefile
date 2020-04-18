# Copyright (c) 2018, Sergiy Yevtushenko
# Copyright (c) 2018-2019, Niklas Hauser
#
# This file is part of the modm project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

BUILD_DIR = build

CMAKE_GENERATOR = Unix Makefiles
CMAKE_FLAGS = -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -DCMAKE_RULE_MESSAGES:BOOL=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=OFF

.PHONY: cmake build clean cleanall program program-bmp debug debug-bmp debug-coredump log-itm

.DEFAULT_GOAL := all

### Targets
all: cmake build

cmake:
	@cmake -E make_directory $(BUILD_DIR)/cmake-build-debug
	@cmake -E make_directory $(BUILD_DIR)/cmake-build-release
	@cd $(BUILD_DIR)/cmake-build-debug && cmake $(CMAKE_FLAGS) -DCMAKE_BUILD_TYPE=Debug -G "$(CMAKE_GENERATOR)" /home/felix/github/DIYHostApplication/controller
	@cd $(BUILD_DIR)/cmake-build-release && cmake $(CMAKE_FLAGS) -DCMAKE_BUILD_TYPE=Release -G "$(CMAKE_GENERATOR)" /home/felix/github/DIYHostApplication/controller

clean:
	@cmake --build $(BUILD_DIR)/cmake-build-release --target clean
	@cmake --build $(BUILD_DIR)/cmake-build-debug --target clean

cleanall:
	@rm -rf $(BUILD_DIR)/cmake-build-release
	@rm -rf $(BUILD_DIR)/cmake-build-debug

profile?=release
build:
	@cmake --build $(BUILD_DIR)/cmake-build-$(profile)

port?=auto
ELF_FILE=$(BUILD_DIR)/cmake-build-$(profile)/controller.elf
program: build
	@python3 modm/modm_tools/avrdude.py -p m328p -c arduino \
			-P $(port) -b 115200 \
			$(ELF_FILE)

