#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ifstream config("config.txt");

    string ignore, line;
    stringstream line_stream;

    getline(config, line);
    line_stream.str(line);

    unsigned int xWin, yWin;
    line_stream >> ignore;
    line_stream >> xWin >> yWin;
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({xWin, yWin}), "SFML window");

    getline(config, line);
    line_stream.clear();
    line_stream.str(line);

    string fontPath;
    int fontSize, fontR, fontG, fontB;
    line_stream >> ignore
                >> fontPath
                >> fontSize
                >> fontR
                >> fontG
                >> fontB;

    // sf::Font font(fontPath);
    sf::Font font;
    if (!font.openFromFile(fontPath)) {
      cout << "font path not found";
      return 1;
    }

    vector<sf::CircleShape> circles{};
    vector<sf::RectangleShape> rectangles{};
int counter = 0;
    while (getline(config, line)) {
      string type, name;
      int R, G, B;
      float xPos, yPos, xVel, yVel, radius, length, height;

      line_stream.clear();
      line_stream.str(line);
      line_stream >> type
                 >> name
                 >> xPos
                 >> yPos
                 >> xVel
                 >> yVel
                 >> R
                 >> G
                 >> B;

      if (type == "Circle") {
        line_stream >> radius;

        sf::CircleShape shape(radius);
        shape.setFillColor(sf::Color(R, G, B));
        shape.setPosition({xPos, yPos});
        
        circles.push_back(shape);
      } else if (type == "Rectangle"){
        line_stream >> length >> height;

        sf::RectangleShape shape({length, height});
        shape.setFillColor(sf::Color(R, G, B));
        shape.setPosition({xPos, yPos});

        rectangles.push_back(shape);
      }
      cout << counter++;
    }
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        for (auto r : rectangles) {
          window.draw(r);
        }

        for (auto c : circles) {
          window.draw(c);
        }

        window.display();
        
    }
}
