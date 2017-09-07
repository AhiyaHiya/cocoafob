#!/usr/bin/env bash

set -e
set -u

BuildUnitTests()
{
	cd mac
	xcodebuild -workspace cocoafob.xcworkspace -target cocoafob_ctest -configuration Debug -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build

	xcodebuild -workspace cocoafob.xcworkspace -target cocoafob_ctest -configuration Release -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build
	cd $CURRENT_PATH
}

BuildProject()
{
	cd mac
	xcodebuild -workspace cocoafob.xcworkspace -target "static lib" -configuration Debug -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build

	xcodebuild -workspace cocoafob.xcworkspace -target "static lib" -configuration Release -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build
	cd $CURRENT_PATH
}

BuildRelease()
{
	cd mac
	local readonly XBUILD_DIR=xcbuild2
	xcodebuild -workspace cocoafob.xcworkspace -scheme "install" -configuration Debug -verbose CONFIGURATION_BUILD_DIR=$XBUILD_DIR clean 
	xcodebuild -workspace cocoafob.xcworkspace -scheme "install" -configuration Release -verbose CONFIGURATION_BUILD_DIR=$XBUILD_DIR clean 
	
	xcodebuild -workspace cocoafob.xcworkspace -scheme "install" -configuration Debug -verbose CONFIGURATION_BUILD_DIR=$XBUILD_DIR build
	xcodebuild -workspace cocoafob.xcworkspace -scheme "install" -configuration Release -verbose CONFIGURATION_BUILD_DIR=$XBUILD_DIR build
	cd $CURRENT_PATH
}

main()
{
	BuildProject
	#BuildRelease
}

CURRENT_PATH=$PWD
main