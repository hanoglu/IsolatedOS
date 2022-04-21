# IsolatedOS
Alien Isolation inspired fan made 32 bit real operating system. This operating system consist of it's own bootloader and -very- little kernel which not derived from Linux or something.
# Installation
Download ISO file in releases page and use an emulator to run it. 
Operating system can be run in legacy bios mode on any computer in theory but **I strongly suggest you to run it on virtual device**.
# How to build
## Required Packages
Install the required packages to compile operating system.
```bash
gcc
nasm
qemu-kvm
```
Note: qemu-kvm package is required for testing iso
## Build Scripts
Open a terminal in project root directory and run script files.
```bash
chmod +x build.sh
chmod +x run.sh
./build.sh
./run.sh
```
To build and run
```bash
./build.sh && ./run.sh
```
# How to change messages in OS
To change messages in OS open vgasrc.cpp file in winsis directory and change following lines.
```cpp
// PERSONAL:
#define _PersonalCount 2
const char* personal_title = "CONFIGURING MESSAGES";
const char* personal[_PersonalCount] = {
    "ALL MESSAGES CAN BE EDITTED ON TOP OF THE VGASRC CPP SOURCE",
    "FILE"
};

// UTILITIES
#define _UtilitiesCount 1
const char* utilities_title = "COMPILATION OF SOURCE";
const char* utilities[_UtilitiesCount] = {
    "LOOK AT BUILD SHELL FILE"
};

// ABOUT
#define _AboutCount 5
const char* about_title = "ABOUT ISOLATED OS";
const char* about[_AboutCount] = {
    "ISOLATED OS VERSION A",
    "THIS OPERATING SYSTEM IS DEVELOPED FOR ENTERTAINMENT PURPOSES",
    "INSPIRED BY FAMOUS VIDEO GAME AND NOT RELATED WITH ANY TRADEMARK",
    "OF IT",
    "PROJECT LICENSED UNDER GPL VERSION TWO"
};
```
If you change the line count you should change '_PersonalCount, _UtilitiesCount or _AboutCount' as well.
# Login Password
Default login password is 'ADMIN'.<br>
You can change password in vgasrc.cpp file.
```cpp
const char* passwd = "ADMIN";

```

# Gallery

<img width="577" alt="resim" src="https://user-images.githubusercontent.com/56837349/162581070-88d740fb-0b0a-444b-b54b-fe687d487585.png">
<img width="577" alt="resim" src="https://user-images.githubusercontent.com/56837349/162581102-4403fe16-29af-4e48-9f04-044617349535.png">
<img width="577" alt="resim" src="https://user-images.githubusercontent.com/56837349/162581115-d553dd64-c717-4058-a409-c57fddc61678.png">
<img width="577" alt="resim" src="https://user-images.githubusercontent.com/56837349/162581124-cbf2fde0-830d-4668-a7aa-0e6907f70019.png">

# License
```
Copyright (C) 2021  Yusuf K. Hanoğlu
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. 

```

# Disclaimer
This project is developed for **entertainment only** and is **not related** with aforementioned game or any of it's trademark.
