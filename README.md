# Teensy template

## Installing the required tools
1. Install the following using your package manager:</br>
   `sudo dnf install doxygen g++ plantuml`</br>
   _Note: I'm using Fedora, but probably replacing dnf by the package manager
   for your Linux distro, e.g. apt-get for Ubuntu, you can do the same._
2. Installing GoogleTest (for running the unit tests), if you haven't done so
   already. In a directory outside of this project directory do:
  1. `git clone https://github.com/google/googletest.git`
  2. `cd googletest`
  3. `mkdir build`
  4. `cd build`
  5. `cmake ..`
  6. `make`
  7. `sudo make install`

## Initializing the project
This only needs to be done once after cloning:
1. Create a Python virtual environment: `python3 -m venv .venv`
2. Enter the virtual environment: `source .venv/bin/activate`
3. Install CMake: `pip install cmake`
4. Create a build directory: `mkdir build`
5. Enter the build directory: `cd build`
6. Create the make files using CMake: `cmake ..`

## Building the project
Whenever you want to continue developing:
1. Enter the previously created virtual environment: `source .venv/bin/activate`
2. `make test` to run the tests
3. `make` to build the binaries for Teensy
4. `make upload` to run the Teensy uploader tool
5. `make docs` to generate the documentation
