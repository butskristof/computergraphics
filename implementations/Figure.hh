#ifndef FIGURE_HH
#define FIGURE_HH

#include <vector>
#include <vector>
#include "Face.hh"
#include "../easy_image.hh"
#include "../ini_configuration.hh"

class Figure {
    public:
        std::vector<Vector3D> points;
        std::vector<Face> faces;
        std::vector<ini::IntTuple> lines;
        img::Color color;
};


typedef std::vector<Figure> Figures3D;

#endif /* FIGURE_HH */
