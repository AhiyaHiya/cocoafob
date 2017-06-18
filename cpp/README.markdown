# CocoaFob

## C++ implementation
Jaime O. Rios


## Introduction
This is the C++ port of CocoaFob, which allows for the same type of functionality Obj-C and Swift developers have.

Xcode and Visual Studio projects are provided for this port.


Note: CocoaPods is used for managing the external libraries required by the Xcode project; Conan.io is used to manage the libraries for the Visual Studio project.

## Requirements
### macOS

* CocoaPod for macOS (https://guides.cocoapods.org/using/getting-started.html)
* 'pod install' must be run prior to opening Xcode project
* cocoafob.xcworkspace must be opened to get access to 
* Catch C++ Unit Testing Header (Handled by download shell script)
* OpenSSL 1_0_2 stable release (Handled by CocoaPods)

### Windows
* Conan.io for Windows (http://docs.conan.io/en/latest/installation.html)
** "conan install" in project directory must be run in order to get vsprops file with search directories
* Catch C++ Unit Testing Header (Handled by Conan)
* OpenSSL 1_0_2 stable release (Handled by Conan)

### Download script
A bash shell script named download_required_libs.sh is in the same directory as this README file and can be used for downloading the Catch from source and places the headers in the components directory.
