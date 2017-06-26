# CocoaFob

## C++ implementation
Jaime O. Rios


## Introduction
This is the C++ port of CocoaFob, which allows for the same type of functionality Obj-C and Swift developers have.

Xcode and Visual Studio projects are provided for this port.


## Requirements
### macOS

* CocoaPods must be installed first
* 'pod install' must be run prior to opening Xcode project
* cocoafob.xcworkspace must be opened to get access to 
* Catch C++ Unit Testing Header (Handled by download shell script)
* OpenSSL 1_0_2 stable release (Handled by CocoaPods)

### Windows
* Conan C++ Package manager
* Catch C++ Unit Testing Header (Handled by Conan)
* OpenSSL 1_0_2 stable release (Handled by Conan)


### Git repos for libraries
* Catch Unit Testing: https://github.com/philsquared/Catch
   * Placed single_include header file into ./components/catch/include/

## Libs imported by CocoaPod 
* OpenSSL 1_0_2 stable

### Download script
A bash shell script named download_required_libs.sh is in the same directory as this README file and can be used for downloading the Catch from source and places the headers in the components directory.

