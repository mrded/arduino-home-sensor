# home-sensor

## Get the code 

`git clone --recursive https://github.com/mrded/home-sensor.git`

## Load submodules 

`git submodule update --init`

## pull all changes for the submodules

`git submodule update --remote`


## Build

- Install [arduino-cli](https://github.com/arduino/arduino-cli)
- Updatethe platform indexes: `core update-index`
- Install the right core. I'm using `Arduino/Genuino Uno` board: `arduino-cli core install arduino:avr`
- Compile: `arduino-cli compile --fqbn arduino:avr:uno`
  
