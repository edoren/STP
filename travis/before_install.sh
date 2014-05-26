#!/bin/bash

unamestr=$(uname)

if [[ "$unamestr" == "Linux" ]]; then

  if [[ "$CXX" == "g++" ]]; then
    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
  fi

  # SFML repository
  sudo add-apt-repository -y ppa:sonkun/sfml
  sudo apt-get update

elif [[ "$unamestr" == "Darwin" ]]; then

  brew update

fi