mkdir build
cd build
sudo cmake .. -DSAPPHIRE_BOOST_VER="1.54.0" -DCMAKE_CXX_COMPILER=g++-4.9 -DCMAKE_C_COMPILER=gcc-4.9 && make
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo add-apt-repository universe
sudo apt-get update 
sudo apt-get install -y software-properties-common
sudo apt-get update
sudo apt-get install gcc-4.9 g++-4.9 gcc-4.9-multilib g++-4.9-multilib
sudo apt-get install libboost-dev libboost-all-dev libmysqlclient-dev lib32z1-dev