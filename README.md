LEDCONTROL

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
