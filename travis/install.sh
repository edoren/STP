#!/bin/bash

unamestr=$(uname)

if [[ "$unamestr" == "Linux" ]]; then

  if [[ "$CXX" == "g++" ]]; then
    # Install g++ 4.8
    sudo apt-get install -qq g++-4.8
    export CXX="g++-4.8"
  fi

  if [[ "$CXX" == "clang++" ]]; then
    cwd=$(pwd)
    svn co --quiet http://llvm.org/svn/llvm-project/libcxx/trunk@181765 libcxx
    cd libcxx/lib && bash buildit
    sudo cp ./libc++.so.1.0 /usr/lib/
    sudo mkdir /usr/include/c++/v1
    cd .. && sudo cp -r include/* /usr/include/c++/v1/
    cd /usr/lib && sudo ln -sf libc++.so.1.0 libc++.so
    sudo ln -sf libc++.so.1.0 libc++.so.1 && cd $cwd
  fi

  # Install SFML
  sudo apt-get install libsfml-dev

  # Install pugixml
  # sudo apt-get install libpugixml-dev

  # Install zlib
  sudo apt-get install zlib1g-dev

elif [[ "$unamestr" == "Darwin" ]]; then

  # Install SFML
  brew install sfml

  # Install zlib
  brew install zlib

fi




