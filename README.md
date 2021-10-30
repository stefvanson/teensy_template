## Project initialization
1. `python3 -m pip install virtualenv`
2. `python3 -m virtualenv .venv`
3. `source .venv/bin/activate`
4. `pip install cmake`
5. Install the following using your package manager:</br>
   `sudo dnf install doxygen g++ plantuml`</br>
   _Note: I'm using Fedora, but probably replacing dnf by the package manager
   for your Linux distro, e.g. apt-get for Ubuntu, you can do the same._

### Installing GoogleTest
1. `git clone https://github.com/google/googletest.git`
2. `cd googletest`
3. `mkdir build`
4. `cd build`
5. `cmake ..`
6. `make`
7. `sudo make install`

## Building the project
1. `source .venv/bin/activate`
2. `mkdir build`
3. `cd build`
4. `cmake ..`
5. `make test` to run the tests
6. `make` to build the binaries for Teensy
7. `make upload` to run the Teensy uploader tool
8. `make docs` to generate some example documentation
