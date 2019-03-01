all: compile upload

compile: SHELL:=/bin/bash
compile:
		@arduino-cli compile --fqbn adafruit:nrf52:feather52832 build-button

upload: SHELL:=/bin/bash
upload:
		@arduino-cli upload --fqbn adafruit:nrf52:feather52832 --port /dev/tty.SLAB_USBtoUART --input build-button/build-button.adafruit.nrf52.feather52832.hex


