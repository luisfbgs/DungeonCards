#include <cmath>
#include "Vec2Int.h"
#include "Common.h"

Vec2Int::Vec2Int(int x, int y) : x(x), y(y) {}

Vec2Int Vec2Int::operator+(const Vec2Int &o) const {
    return {this->x + o.x, this->y + o.y};
}

Vec2Int Vec2Int::operator+=(const Vec2Int &o) {
    *this = *this + o;
    return *this;
}

Vec2Int Vec2Int::operator-(const Vec2Int &o) const {
    return {this->x - o.x, this->y - o.y};
}

Vec2Int Vec2Int::operator-=(const Vec2Int &o) {
    *this = *this - o;
    return *this;
}

Vec2Int Vec2Int::operator*(int t) const {
    return {this->x * t, this->y * t};
}

Vec2Int Vec2Int::operator*=(int t) {
    *this = *this * t;
    return *this;
}

Vec2Int Vec2Int::operator/(int t) const {
    return {this->x / t, this->y / t};
}

Vec2Int Vec2Int::Rotate(int ang) const {
    int rad = degToRad(ang);
    return {this->x * cosf(rad) - this->y * sinf(rad),
            this->y * cosf(rad) + this->x * sinf(rad)};
}

Vec2Int Vec2Int::Norm() const {
    return *this / this->Length();
}

int Vec2Int::Angle() const {
    return radToDeg(atan2(this->y, this->x));
}

int Vec2Int::operator*(const Vec2Int &o) const {
    return this->x * o.x + this->y * o.y;
}

int Vec2Int::operator^(const Vec2Int &o) const {
    return this->x * o.y - this->y * o.x;
}

int Vec2Int::Length() const {
    return hypot(this->x, this->y);
}

int Vec2Int::Cross(const Vec2Int &a, const Vec2Int &b) const {
    return (a-(*this)) ^ (b-(*this));
}

int Vec2Int::Dist(const Vec2Int &a) const {
    return (a-(*this)).Length();
}

bool Vec2Int::operator==(const Vec2Int &o) const {
    return (x == o.x) && (y == o.y);
}

bool Vec2Int::operator!=(const Vec2Int &o) const {
    return !(x == o.x);
}

bool Vec2Int::operator<(const Vec2Int &o) const {
    if(!equals(x, o.x)) return x < o.x;
    return y < o.y;
}

