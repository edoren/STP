# What is STP?

[![Build Status](https://travis-ci.org/edoren/STP.svg?branch=master)](https://travis-ci.org/edoren/STP)

STP is an extension library for [SFML2](https://github.com/LaurentGomila/SFML) designed to read the [Tiled](http://www.mapeditor.org/) map format. It uses the new C++11 standard features, so be sure to have a C++11 compatible compiler like g++ 4.7, clang 3.3 or Visual Studio 2013 compiler.

## Features

*   Low memory usage.
*   Supports all the encoding and compression formats.
*   Support for orthogonal, isometric and staggered maps.

## Usage

STP is easy to use; here is some example code.

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
