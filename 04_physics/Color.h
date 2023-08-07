#pragma once
#include <fstream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;

  private:
    double r{};
    double g{};
    double b{};
};

inline std::ifstream &operator>>(std::ifstream &stream, Color &m_vector) {
  double r, g, b;
  stream >> r >> g >> b;
  m_vector = Color(r, g, b);
  
  return stream;
}