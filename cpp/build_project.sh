#!/usr/bin/env bash

set -e
set -u

BuildUnitTests()
{
	cd mac
	xcodebuild -project cocoafob.xcodeproj -target cocoafob_ctest -configuration Debug -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build

	xcodebuild -project cocoafob.xcodeproj -target cocoafob_ctest -configuration Release -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build
	cd $CURRENT_PATH
}

BuildProject()
{
	cd mac
	xcodebuild -project cocoafob.xcodeproj -target "static lib" -configuration Debug -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build

	xcodebuild -project cocoafob.xcodeproj -target "static lib" -configuration Release -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build
	cd $CURRENT_PATH
}

main()
{
	BuildProject
}

CURRENT_PATH=$PWD
main