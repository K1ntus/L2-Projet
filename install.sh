#Feel free to read installation instructions on util/README.*

mkdir -p build
cd build
cmake ..
make
cp undead_text ../executable/undead_text
cp undead_solve ../executable/undead_solve
cp undead_sdl ../executable/undead_sdl
cd ..
rm -r build
cd executable
chmod +x *
