#include "Lines2D.hh"

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

// LINE2D

Line2D::Line2D(const Point2D p1, const Point2D p2, img::Color color) { // default color specified in header
    this->p1 = p1;
    this->p2 = p2;
    this->color = color;
}

Line2D::Line2D(const double x1, const double y1, const double x2, const double y2, img::Color color) { // default color specified in header
    this->p1 = Point2D(x1, y1);
    this->p2 = Point2D(x2, y2);
    this->color = color;
}

Point2D* Line2D::getp1() {
    return &(this->p1);
}

Point2D* Line2D::getp2() {
    return &(this->p2);
}

img::Color Line2D::getColor() {
    return this->color;
}
