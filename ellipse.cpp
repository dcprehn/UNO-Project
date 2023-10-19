//
// Created by dcpre on 5/4/2021.
//

#include "ellipse.h"

Ellipse::Ellipse(const Vector2f &radius) : m_radius(radius) {
    update();
}

void Ellipse::setRadius(const Vector2f &radius) {
    m_radius = radius;
}

Vector2f Ellipse::getRadius() const {
    return m_radius;
}

size_t Ellipse::getPointCount() const {
    return 30;
}

Vector2f Ellipse::getPoint(size_t index) const {
    const float PI = 3.14159265;
    float angle = ((2 * PI) * index) / getPointCount() - (PI / 2);
    float x = cos(angle) * m_radius.x;
    float y = sin(angle) * m_radius.y;
    return Vector2f(m_radius.x + x, m_radius.y + y);
}
