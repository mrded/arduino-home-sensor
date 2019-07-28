PORT = /dev/cu.usbmodem14201 
FQBN = arduino:avr:uno
CORE = arduino:avr

default: setup build install 

setup:
	arduino-cli core update-index
	arduino-cli core install $(CORE) 

build:
	arduino-cli compile --fqbn $(FQBN)

install: 
	arduino-cli upload -p $(PORT) --fqbn $(FQBN) 
