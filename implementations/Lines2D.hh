#ifndef LINES2D_H
#define LINES2D_H

#include <list>
#include "../easy_image.hh"
#include "Point2D.hh"

class Line2D {
    private:
        Point2D p1;
        Point2D p2;
        img::Color color;

        double z1;
        double z2; // to fill in during projection

    public:
        Line2D(const Point2D p1, const Point2D p2, img::Color color = img::Color());
        Line2D(const double x1, const double y1, const double x2, const double y2, img::Color color = img::Color());

        Line2D(const Point2D p1, const double z1, const Point2D p2, const double z2, img::Color color = img::Color());
        Line2D(const double x1, const double y1, const double z1, const double x2, const double y2, const double z2, img::Color color = img::Color());

        Point2D* getp1();
        Point2D* getp2();
        img::Color getColor();


        void setz1(double z1);
        double getz1();
        void setz2(double z2);
        double getz2();

};

typedef std::list<Line2D> Lines2D;

#endif /* LINES2D_H */
