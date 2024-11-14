# MultipassTechnicalTest
This is my submission for Canonical's Multipass engineer technical test.

## Installation
This project requires the installation of two libraries, `nlohmann` and `libcurl`.
For installing `nlohmann` with other package managers not listed, check [here](https://json.nlohmann.me/integration/package_managers/).

### macOS
_Using Homebrew_
1. Install `nlohmann`
```sh
    brew install nlohmann-json
```
2. Install `libcurl`
```sh
    brew install curl
```

### Windows
Note - Visual Studio must be installed.

_Using vcpkg_
1. Install `nlohmann`
```sh
    vcpkg install nlohmann-json
```
2. Install `libcurl`
```sh
    vcpkg install libcurl
```

### Linux
1. Install `nlohmann`
```sh
    sudo apt-get install nlohmann-json3-dev
```
2. Install `libcurl`
```sh
    sudo apt-get install libcurl4-openssl-dev
```

## Usage

### Compile and run
#### macOS and Linux:
1. `cd` into `MultipassTechnicalTest` and compile `cmake` (this step only needs to be done once)
```sh
    cmake .
```
2. Compile using `make`
```sh
    make
```
3. Run `main`
```sh
    ./main
```
#### Windows:
1. `cd` into `MultipassTechnicalTest` and compile `cmake` (this step only needs to be done once)
```sh
    mkdir build
    cd build
    cmake -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>\scripts\buildsystems\vcpkg.cmake -DCMAKE_PREFIX_PATH=<vcpkg-root>\installed\x64-windows ..
    cmake -G "Visual Studio 17 2022" ..     # Note - change 17 and 2022 to your version of Visual Studio
    cmake --build . --config Release
```
2. `cd` into `Release` and run
```sh
    cd Release
    .\main.exe
```

### CLI usage
The program will supply you with these options:
```sh
    0 - Quit
    1 - Return a list of all currently supported Ubuntu releases
    2 - Return the current Ubuntu LTS version
    3 - Return the sha256 of the disk1.img item of a given Ubuntu release
```
Type the corresponding number for your choice in the terminal and hit `enter`.
The program will keep asking for a new choice until you exit by entering `0`.