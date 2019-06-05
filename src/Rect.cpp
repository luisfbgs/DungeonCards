#include "Rect.h"
#include "Vec2.h"

Rect::Rect(float x, float y, float w, float h) : leftUp(x, y), w(w), h(h) {
    this->angle = 0;
}

Rect::Rect(Vec2 leftUp, float w, float h) : leftUp(leftUp), w(w), h(h) {
    this->angle = 0;
}

Rect Rect::operator+(const Vec2 &o) const {
    return {this->leftUp + o, w, h};
}

Rect Rect::operator-(const Vec2 &o) const {
    return {this->leftUp - o, w, h};
}

Vec2 Rect::Center() const {
    return {this->leftUp.x + this->w / 2,
            this->leftUp.y + this->h / 2};
}

void Rect::CenterIn(const Vec2 &pos) {
    this->leftUp = pos - Vec2(this->w / 2, this->h / 2);
}

bool Rect::Contains(float x, float y) const {
    return (x >= this->leftUp.x && x <= this->leftUp.x + this->w
            && y >= this->leftUp.y && y <= this->leftUp.y + this->h);
}

float Rect::Dist(const Rect &o) const {
    return this->Center().Dist(o.Center());
}