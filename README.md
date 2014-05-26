# What is STP?

[![Build Status](https://travis-ci.org/edoren/STP.svg?branch=master)](https://travis-ci.org/edoren/STP)

STP is a library extension for [SFML2](https://github.com/LaurentGomila/SFML) designed to load the Tiled map format and use it with the SFML library.


## Features

*   Low memory usage.
*   Support all the encoding and compression formats.
*   Only Support for orthogonal maps (At the moment).

## Installing STP ##

You need at least g++ 4.8.  There are *other external dependencies*

### Mac ###

* *Homebrew*: `brew install sfml && brew install zlib`
### Linux ###

* *Apt*:
    `sudo apt-get install libsfml-dev && sudo apt-get install zlib1g-dev`

## Usage

STP is easy to use, here is a example code.

```c++
#include "SFML/Graphics.hpp"
#include "STP/TMXLoader.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(360, 280), "STP Example");
    tmx::TileMap map("path/to/my/file/map.tmx");

    map.ShowObjects(); // Display all the layer objects.

    map.GetLayer("World").visible = false; // Hide a Layer named World

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the map
        window.draw(map);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
```
