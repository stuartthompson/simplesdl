INC="-I/usr/local/include/zenixel -I/usr/local/include/SDL2"
INCDIR=./inc
LIB="-L/usr/local/lib -lSDL2 -lSDL2_ttf -lzenixel"
SRCROOT=./src
SRCDIRS=(.)
BUILDDIR=./build
OUTPUT=sdltest
CFLAGS="-D_REENTRANT --std=c++17"

# Clean up previous builds
echo "Cleaning build output"
rm -rf build                                                # Remove build folder

# Create output folder
echo "Creating build folder"
mkdir $BUILDDIR                                             # Create build folder

# Compile object files
echo "Compiling program"
g++ -g $SRCROOT/main.cpp $INC $LIB -o $BUILDDIR/$OUTPUT $CFLAGS