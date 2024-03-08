#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string>
#include <sstream>

#define RESET "\e[0m"

struct Color {
    short red, green, blue;
    Color();
    Color(int r, int g, int b);
    std::string get();
};

std::ostream& operator<<(std::ostream &out, const Color &color);

Color::Color() {red = green = blue = 0;}
Color::Color(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
}

std::string Color::get() {
    std::stringstream ss;
    ss << (*this);
    std::string ret;
    ss >> ret;
    return ret;
}

std::ostream& operator<<(std::ostream &out, const Color &color) {
    out << "\e[38;2;" << color.red << ";" << color.green << ";" << color.blue << "m";
    return out;
}

#endif