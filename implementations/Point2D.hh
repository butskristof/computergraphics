#ifndef POINT2D_H
#define POINT2D_H

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

#endif /* POINT2D_H */
