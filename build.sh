PLATFORM=$1
TASK=$2

# Validate arguments
if [ "$PLATFORM" != "linux" ] && [ "$PLATFORM" != "osx" ]; then
    echo "Usage: sh ./build.sh [platform]"
    exit 0
fi

# Base-config
INCDIR=./inc
SRCROOT=./src
SRCDIRS=(.)
BUILDDIR=./build
OUTPUT=sdltest
CFLAGS="-std=c++17"

# Set platform-specific variables
if [ "$PLATFORM" == "linux" ]; then
    echo "Targeting Linux"
    PLATFORM="linux"
    INC="-I/usr/include/zenixel -I/usr/include/SDL2"
    LIB="-L/usr/lib -lSDL2 -lSDL2_ttf -lzenixel"
    CFLAGS="-D_REENTRANT $CFLAGS"
fi
if [ "$PLATFORM" == "osx" ]; then
    echo "Targeting OSX"
    PLATFORM="osx"
    INC="-I/usr/local/include/zenixel -I/usr/local/include/SDL2"
    LIB="-L/usr/local/lib -lSDL2 -lSDL2_ttf -lzenixel"
    CFLAGS="-D_THREAD_SAFE $CFLAGS"
fi

# Clean
if [ "$TASK" == "clean" ] || [ "$TASK" == "" ]; then
    # Clean up previous builds
    echo "Cleaning build output"
    rm -rf $BUILDDIR                                             # Remove build folder
fi

# Build
if [ "$TASK" == "build" ] || [ "$TASK" == "" ]; then
    # Create output folder
    echo "Creating build folder"
    mkdir $BUILDDIR                                             # Create build folder

    # Compile program
    echo "Compiling program"
    g++ -g $SRCROOT/main.cpp $INC $LIB -o $BUILDDIR/$OUTPUT $CFLAGS
fi