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

## full installation
Here is an example for a full set of local installation,
the current work dir is assumed to be `wcp-icarus`
```
mkdir external
export WC_EXTERNAL=$(pwd)/external

#--- eigen
wget https://gitlab.com/libeigen/eigen/-/archive/3.3.9/eigen-3.3.9.tar.gz
tar -xzvf eigen-3.3.9.tar.gz
pushd eigen-3.3.9
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$WC_EXTERNAL ..
make install
popd

#--- boost
wget https://dl.bintray.com/boostorg/release/1.69.0/source/boost_1_69_0.tar.bz2
tar --bzip2 -xf boost_1_69_0.tar.bz2
pushd boost_1_69_0
./bootstrap.sh --prefix=$WC_EXTERNAL
./b2 install
popd

#--- ROOT
wget https://root.cern.ch/download/root_v6.12.06.source.tar.gz
tar -xzvf root_v6.12.06.source.tar.gz
pushd root-6.12.06
mkdir install
cd install
cmake -Dminuit2=ON -Dpython=ON -Dcxx11=ON ..
make -j4
popd

#--- WireCell apps
source root-6.12.06/install/bin/thisroot.sh
mkdir install

./wcb configure \
--with-eigen-include="$WC_EXTERNAL/include/eigen3/" \
--with-root="$ROOTSYS" \
--boost-includes="$WC_EXTERNAL/include/boost/" \
--boost-libs="$WC_EXTERNAL" \
--boost-mt \
--prefix="./install"

./wcb -p build install
```

## environment setup 
Please change your path accordingly
```
source /data1/wgu/wcp-icarus/root-6.12.06/install/bin/thisroot.sh
export PATH=/data1/wgu/wcp-icarus/install/bin:$PATH
export LD_LIBRARY_PATH=/data1/wgu/wcp-icarus/install/lib:$LD_LIBRARY_PATH
```

