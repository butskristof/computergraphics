#include "Lines2D.hh"


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


Line2D::Line2D(const Point2D p1, const double z1, const Point2D p2, const double z2, img::Color color) {
    this->p1 = p1;
    this->z1 = z1;
    this->p2 = p2;
    this->z2 = z2;
    this->color = color;
}

Line2D::Line2D(const double x1, const double y1, const double z1, const double x2, const double y2, const double z2, img::Color color) {
    this->p1 = Point2D(x1, y1);
    this->z1 = z1;
    this->p2 = Point2D(x2, y2);
    this->z2 = z2;
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


void Line2D::setz1(double z1) {
    this->z1 = z1;
}

double Line2D::getz1() {
    return this->z1;
}

void Line2D::setz2(double z2) {
    this->z2 = z2;
}

double Line2D::getz2() {
    return this->z2;
}
