#pragma once

class Vec2 {
  public:
	/*
    // addition using chaining
    Vec2& add(const Vec2& v)
    {
      x += v.x;
      y += v.y;
      return *this;
    }
	*/
	/*
    Vec2& rotate (float rot)
    {
      return *this;
    }
	*/
    float x = 0;
    float y = 0;
    Vec2() {}

    Vec2(float xin, float yin);
	bool operator == (const Vec2 & rhs) const;
	bool operator != (const Vec2 & rhs) const;
	
	Vec2 operator + (const Vec2 & rhs) const;
	Vec2 operator - (const Vec2 & rhs) const;
	Vec2 operator / (const float val) const;
	Vec2 operator * (const float val) const;

	Vec2& operator += (const Vec2 & rhs);
	Vec2& operator -= (const Vec2 & rhs);
	Vec2& operator *= (const float val);
	Vec2& operator /= (const float val);

	float dist(const Vec2 & rhs) const;
  private:
};
