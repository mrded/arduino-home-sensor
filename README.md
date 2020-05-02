# arduino-home-sensor

## Get the code 

`git clone --recursive https://github.com/mrded/arduino-home-sensor.git`

## Load submodules 

`git submodule update --init`

## pull all changes for the submodules

`git submodule update --remote`


## Build

- Install [arduino-cli](https://github.com/arduino/arduino-cli)
- Updatethe platform indexes: `arduino-cli core update-index`
- Install the right core. I'm using `Arduino/Genuino Uno` board: `arduino-cli core install arduino:avr`
- Compile: `arduino-cli compile --fqbn arduino:avr:uno`
- Get a port of your board: `arduino-cli board list` -> `/dev/cu.usbmodem14201`
- Upload: `arduino-cli upload -p /dev/cu.usbmodem14201 --fqbn arduino:avr:uno`
