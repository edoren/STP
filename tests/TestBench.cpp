#include "SFML/Graphics.hpp"
#include "STP/TMXLoader.hpp"

#include <cstdlib>
#include <iostream>

std::vector<std::string> options{
    "desert",
    "hexagonal-mini",
    "isometric_grass_and_water",
    "orthogonal-outside",
    "perspective_walls",
    "sewers"
};

void print_help(const char* program_name) {
    std::cout << "Usage: " << program_name << " id" << std::endl;
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "   " << i + 1 << " - " << options[i] << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        print_help(argv[0]);
        return EXIT_FAILURE;
    }

    size_t index = std::atoi(argv[1]);

    if (index == 0 || index > options.size()) {
        print_help(argv[0]);
        return EXIT_FAILURE;
    }

    std::string option = options[index - 1];

    sf::Vector2f window_size(800, 600);

    tmx::TileMap map("assets/" + option + ".tmx");

    sf::RenderWindow window(
        sf::VideoMode(window_size.x, window_size.y),
        "STP Test Bench"
    );

    sf::Vector2f view_center = window_size / 2.f;
    sf::View view(view_center, window_size);
    window.setView(view);

    bool mouse_pressed = false;
    sf::Vector2i mouse_pos, mouse_last_pos;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    if (event.mouseButton.button == sf::Mouse::Button::Left) {
                        mouse_pressed = true;
                        mouse_pos.x = mouse_last_pos.x = event.mouseButton.x;
                        mouse_pos.y = mouse_last_pos.y = event.mouseButton.y;
                    }
                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    if (event.mouseButton.button == sf::Mouse::Button::Left) {
                        mouse_pressed = false;
                    }
                    break;
                }
                case sf::Event::MouseMoved: {
                    if (mouse_pressed) {
                        mouse_pos = {event.mouseMove.x, event.mouseMove.y};
                        sf::Vector2i delta = mouse_pos - mouse_last_pos;
                        view.move(static_cast<sf::Vector2f>(-delta));
                        window.setView(view);
                        mouse_last_pos = mouse_pos;
                    }
                    break;
                }
                case sf::Event::Resized: {
                    window_size.x = event.size.width;
                    window_size.y = event.size.height;
                    view.setSize(window_size);
                    window.setView(view);
                    break;
                }
                default: {
                    break;
                }
            }
        }
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
