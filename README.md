# Signer


### pre-requsition  

- ubuntu 18.04 

- C++ > 17 : https://linuxconfig.org/how-to-install-g-the-c-compiler-on-ubuntu-18-04-bionic-beaver-linux

- CMake > 3.15 : https://cmake.org/install/

- LIBSODIUM > 1.0.17  : https://libsodium.gitbook.io/doc/installation

### build
<pre><code>
 git clone https://github.com/wowlsh93/Signer.git
 cd Signer
 mkdir build
 cd build
 cmake ..
 cmake --build .
 ./Signer [command] [option] 
</pre></code>
### run 
 
./Signer keypair

./Signer sign $SEED $DATA

./Signer verify $PUBLIC_KEY $SIGNATURE $DATA
