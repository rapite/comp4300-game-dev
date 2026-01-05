#pragma once

class Vec2 {
  public:
    float x = 0;
    float y = 0;
    Vec2() {}
    Vec2(float xin, float yin)
      : x(xin)
      , y(yin)
  {}

    // addition using chaining
    Vec2& add(const Vec2& v)
    {
      x += v.x;
      y += v.y;
      return *this;
    }

    Vec2& scale (float s)
    {
      x *= s;
      y *= s;
      return *this;
    }

    Vec2& rotate (float rot)
    {
      return *this;
    }

    bool operator == (const Vec2 & rhs) const {
      if (x == rhs.x && y == rhs.y) {
        return true;
      }
      return false;
    }

    Vec2 operator + (const Vec2 & rhs) const {
      return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2 operator * (const float & val) const {
      return Vec2(x * val, y * val);
    }

    void operator += (const Vec2 & rhs) {
      x += rhs.x;
      y += rhs.y;
    }
  private:
};
