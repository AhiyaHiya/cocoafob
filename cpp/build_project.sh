set -e
set -u

xcodebuild -target cocoafob_ctest -configuration Debug -verbose CONFIGURATION_BUILD_DIR=xcbuild clean build