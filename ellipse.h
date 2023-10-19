//
// Created by dcpre on 5/4/2021.
//

#ifndef FP_ELLIPSE_H
#define FP_ELLIPSE_H

#include <SFML/Graphics.hpp>
using namespace sf;
#include <cmath>

/* This class was found as an example in the sfml documentation, and is used for the UNO sprite in GameWindow. */

class Ellipse : public Shape {
public:
    explicit Ellipse(const Vector2f& radius = Vector2f(0.f, 0.f));
    void setRadius(const Vector2f& radius);
    Vector2f getRadius() const;
    virtual size_t getPointCount() const;
    virtual Vector2f getPoint(size_t index) const;
private:
    Vector2f m_radius;
};

#endif //FP_ELLIPSE_H
