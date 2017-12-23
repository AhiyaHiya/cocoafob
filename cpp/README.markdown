# CocoaFob

## C++ implementation
Jaime O. Rios


## Introduction
This is the C++ port of CocoaFob, which allows for the same type of functionality Obj-C and Swift developers have.

Xcode and Visual Studio projects are provided for this port.


## Requirements
### macOS
* CocoaPods package manager (https://guides.cocoapods.org/using/getting-started.html)
* "pod install" in project directory must be run first to have xcconfig file generated with lib search paths
* cocoafob.xcworkspace must be opened to get access to 

### Windows
* Conan.io package manager (http://docs.conan.io/en/latest/installation.html)
* "conan install" in project directory must be run in order to get vsprops file with search directories


## Notes
### Download script
(macOS only) A bash shell script named download_required_libs.sh is in the same directory as this README file and is used by the Xcode project for downloading the Catch from source and places the headers in the components directory.

### For generating new Public Private Keys
Here are the terminal commands for doing so:
openssl dsaparam -out dsaparam.pem 512
openssl gendsa -out privkey.pem dsaparam.pem
openssl dsa -in privkey.pem -pubout -out pubkey.pem



### Managed Libs
* OpenSSL 1_0_2 stable release
* ZLIB 1.2.8

### Managed Header
* (Windows only) Conan is used to download Catch C++ header
