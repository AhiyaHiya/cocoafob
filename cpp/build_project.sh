#!/usr/bin/env bash

set -e
set -u

CURRENT_PATH=$PWD

function BuildUnitTests()
{
	cd mac
	xcodebuild -project cocoafob.xcodeproj -target cocoafob_ctest -configuration Debug -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build

	xcodebuild -project cocoafob.xcodeproj -target cocoafob_ctest -configuration Release -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build
	cd $CURRENT_PATH
}

function BuildProject()
{
	cd mac
	xcodebuild -project cocoafob.xcodeproj -target "static lib" -configuration Debug -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build

	xcodebuild -project cocoafob.xcodeproj -target "static lib" -configuration Release -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build
	cd $CURRENT_PATH
}

BuildProject