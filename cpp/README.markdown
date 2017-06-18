# CocoaFob

## C++ implementation
Jaime O. Rios


## Introduction
This is the C++ port of CocoaFob, which allows for the same type of functionality Obj-C and Swift developers have, on any platform that supports C++.

Note: CocoaPods is used for managing the external libraries required by the Xcode project; Conan.io is used to manage the libraries for the Visual Studio project.

## Requirements
* CocoaPod for macOS (https://guides.cocoapods.org/using/getting-started.html)
** "pod install" in project directory must be run first to have xcconfig file generated with lib search paths
* Conan.io for Windows (http://docs.conan.io/en/latest/installation.html)
** "conan install" in project directory must be run in order to get vsprops file with search directories

### Libs
Managed by package managers and required by projects
* Catch C++ Unit Testing Header
* OpenSSL 1_0_2 stable release
* ZLIB 1.2.8
