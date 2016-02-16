#include "Point2D.hh"

// POINT2D

Point2D::Point2D() {
}

Point2D::Point2D(const double x, const double y) {
    this-> x = x;
    this-> y = y;
}

void Point2D::setX(const double x) {
    this->x = x;
}

double Point2D::getX() {
    return this->x;
}

void Point2D::setY(const double y) {
    this->y = y;
}

double Point2D::getY() {
    return this->y;
}

bool Point2D::operator==(Point2D& r) {
    if ( (this->getX() == r.getX()) and (this->getY() == r.getY()) ) {
        return true;
    }
    return false;
}

bool Point2D::operator!=(Point2D& r) {
    if ( (this->getX() == r.getX()) and (this->getY() == r.getY()) ) {
        return false;
    }
    return true;
}
