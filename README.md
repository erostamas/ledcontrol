LEDCONTROL

#INSTALL BOOST

'''
mkdir boost
cd boost
wget http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.bz2
tar xvfo boost_1_60_0.tar.bz2

cd boost_1_60_0
./bootstrap.sh
sudo ./b2 install
'''

#INSTALL CPP-REDIS

'''
git clone https://github.com/Cylix/cpp_redis.git
cd cpp_redis
git submodule init && git submodule update
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
'''

#INSTALL GMOCK
'''
sudo apt-get install google-mock
cd /usr/src/gtest
mkdir build && cd build
sudo cmake ../
sudo make -j
ls build/libgtest*
build/libgtest.a  build/libgtest_main.a
sudo cp libgmock* /usr/lib/
'''