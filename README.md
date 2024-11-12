# MultipassTechnicalTest
This is my submission for Canonical's Multipass engineer technical test.

## Installation
This project requires the installation of two libraries, `nlohmann` and `libcurl`.

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
3. `cd` into `MultipassTechnicalTest` and compile `cmake`
```sh
    cmake .
```

### Windows
Here's how to install with Windows.

### Linux
Here's how to install with Linux.

## Usage

### Compile and run
1. Compile using `make`
```sh
    make
```
2. Run `main`
```sh
    ./main
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