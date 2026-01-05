# COMP4300 - Assignment1

## Program Specification

Writing a C++/SFML program to read descriptions, draw those shapes to screen. Each shape has a name, position, speed, color, and other unique properties to the entity. Rectangles have width and height, circles have Radius. The position of a shape for this assignment refers to its SFML default of the upper-left corner of the shape.

The shapes must bounce off the sides of the window that contain them. Hitting the top or bottom of the screen causes the Y speed to reverse. Hitting the left or right of the X walls of the screen causes the X speed to reverse. All shapes will always be configured to start within the window. Each shape's name is to be drawn onthe center of the shape with a font, size, and color of choosing.

## Config Specifications
Window Size
Font-location-size-color(rgb)
Circle Name Xposition YPosition XVel YVel R G B Radius
Rectangle Name Xposition YPosition XVel YVel R G B xLength yHeight

Consider the following config.txt for input.

Window 800 600
Font fonts/tech.ttf 18 255 255 255
Circle CGreen 100 100 -0.03 0.02 0 255 0 50
Circle CBlue 200 200 0.02 0.04 0 0 255 100 
Circle CPurple 300 300 -0.02 -0.01 255 0 255 75
Rectangle RRed 200 200 0.1 0.15 255 0 0 50 25
Rectangle RGrey 300 250 -0.2 0.02 100 100 100 50 100
Rectangle RTeal 25 100 -0.02 -0.02 0 255 255 100 100
