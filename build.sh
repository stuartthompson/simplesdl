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
if [ "$1" = "linux" ]; then
    echo "Building for Linux"
    PLATFORM="linux"
    INC="-I/usr/include/zenixel -I/usr/include/SDL2"
    LIB="-L/usr/lib -lSDL2 -lSDL2_ttf -lzenixel"
    CFLAGS="-D_REENTRANT $CFLAGS"
fi
if [ "$1" = "osx" ]; then
    echo "Building for OSX"
    PLATFORM="osx"
    INC="-I/usr/local/include/zenixel -I/usr/local/include/SDL2"
    LIB="-L/usr/local/lib -lSDL2 -lSDL2_ttf -lzenixel"
    CFLAGS="-D_THREAD_SAFE $CFLAGS"
fi

# Clean up previous builds
echo "Cleaning build output"
rm -rf build                                                # Remove build folder

# Create output folder
echo "Creating build folder"
mkdir $BUILDDIR                                             # Create build folder

# Compile object files
echo "Compiling program"
g++ -g $SRCROOT/main.cpp $INC $LIB -o $BUILDDIR/$OUTPUT $CFLAGS