## easyprofiler [![Build Status](https://travis-ci.org/In-line/easyprofiler.svg?branch=master)](https://travis-ci.org/In-line/easyprofiler)
Easy to use amxx profiler as module.

## Compilation
cmake, boost, gcc, g++ packages may be required.
<pre>
sudo apt-get install libboost-dev cxxtest cmake gcc g++ # gcc > 4.8 required
sudo apt-get install gcc-multilib g++-multilib libc6-dev-i386 libc6-i386 # If cross compiling from 64 bit linux  
cmake .
make -j$((2 * `getconf _NPROCESSORS_ONLN`)) # Multicore build
</pre>
