mkdir -p build
cd build
cmake ..
make
cp undead_text ../executable/undead_text
cp undead_solve ../executable/undead_solve
cd ..
rm -r build
cd executable
chmod +x *
