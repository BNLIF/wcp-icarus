# wcp-icarus

## build
dependency: Boost, Eigen and ROOT

example configuration with UPS system
```
./wcb configure \
--with-eigen-include="$EIGEN_DIR/include/eigen3/" \
--with-root="$ROOTSYS" \
--boost-includes="$BOOST_INC" \
--boost-libs="$BOOST_LIB" \
--boost-mt \
--prefix=/home/$USER/opt
```

Then build and install:
```
./wcb -p build install
```