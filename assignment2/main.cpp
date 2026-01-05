#include "vec2.hpp"
#include <iostream>

int main() {
  Vec2 v1(100, 200);
  Vec2 v2(50, 75);
  // Vec2 v3(v1.x + v2.x, v1.y + v2.y);
  Vec2 v3;
  v3 = v1 + v2;

  std:: cout << v3.x << " " << v3.y << "\n";

  Vec2 v4(1000, 2000);
  v1.add(v2).add(v4);
  std:: cout << v1.x << " " << v1.y << "\n";
}
