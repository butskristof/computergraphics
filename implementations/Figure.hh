#ifndef FIGURE_HH
#define FIGURE_HH

#include <vector>
#include <list>
#include "Face.hh"
#include "../easy_image.hh"

class Figure {
    public:
        std::vector<Vector3D> points;
        std::vector<Face> faces;
        img::Color color;
};


typedef std::list<Figure> Figures3D;

#endif /* FIGURE_HH */
