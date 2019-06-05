#pragma once

class Vec2Int {
public:
    Vec2Int(int x = 0, int y = 0);
    int x, y;

    Vec2Int operator+(const Vec2Int &o) const;
    Vec2Int operator+=(const Vec2Int &o);
	Vec2Int operator-(const Vec2Int &o) const;
	Vec2Int operator-=(const Vec2Int &o);
	Vec2Int operator*(int t) const;
	Vec2Int operator*=(int t);
	Vec2Int operator/(int t) const;
	Vec2Int Rotate(int ang) const;
	Vec2Int Norm() const;
	int operator*(const Vec2Int &o) const;
	int operator^(const Vec2Int &o) const;
	int Cross(const Vec2Int &a, const Vec2Int &b) const;
	int Dist(const Vec2Int &a) const;
	int Length() const;
	int Angle() const;
    bool operator==(const Vec2Int &o) const;
    bool operator!=(const Vec2Int &o) const;
	bool operator<(const Vec2Int &o) const;
};

