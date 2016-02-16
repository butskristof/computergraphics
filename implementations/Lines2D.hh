#ifndef LINES2D_H
#define LINES2D_H

#include <list>
#include "../easy_image.hh"

class Point2D {
    private:
        double x;
        double y;
    public:
        Point2D();
        Point2D(const double x, const double y);

        void setX(const double x);
        double getX();
        void setY(const double y);
        double getY();

        bool operator==(Point2D& r);
        bool operator!=(Point2D& r);
};

class Line2D {
    private:
        Point2D p1;
        Point2D p2;
        img::Color color;

    public:
        Line2D(const Point2D p1, const Point2D p2, img::Color color = img::Color());
        Line2D(const double x1, const double y1, const double x2, const double y2, img::Color color = img::Color());

        Point2D* getp1();
        Point2D* getp2();
        img::Color getColor();
};

typedef std::list<Line2D> Lines2D;

#endif /* LINES2D_H */
