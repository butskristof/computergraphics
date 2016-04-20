// session 1

#include <algorithm> // std::max
#include <climits> // INT_MAX/_MIN

img::EasyImage draw2DLines(const Lines2D& lines, const unsigned int size, const img::Color bgc = img::Color(), const bool zbuf = false) {

    // debug for 2D lsystems
    std::cout << "Entering draw2DLines, number of lines to be drawn: " << lines.size() << std::endl;
    
    // find min/max for x/y
    double xmin = INT_MAX, xmax = 0, ymin = INT_MAX, ymax = 0;

    for (auto it: lines) {
        double x1, y1, x2, y2;
        x1 = it.getp1()->getX();
        y1 = it.getp1()->getY();
        x2 = it.getp2()->getX();
        y2 = it.getp2()->getY();

        if ( std::max(x1, x2) > xmax ) {
            xmax = std::max(x1, x2);
        }
        if ( std::min(x1, x2) < xmin ) {
            xmin = std::min(x1, x2);
        }
        if ( std::max(y1, y2) > ymax ) {
            ymax = std::max(y1, y2);
        }
        if ( std::min(y1, y2) < ymin ) {
            ymin = std::min(y1, y2);
        }
    }

    double xrange = xmax - xmin;
    double yrange = ymax - ymin;

    double imgx = size * ( xrange / std::max(xrange, yrange ));
    double imgy = size * ( yrange / std::max(xrange, yrange ));

    double d = 0.95 * (imgx / xrange);
    double dcx = (d * (xmin + xmax) ) / 2.0;
    double dcy = (d * (ymin + ymax) ) / 2.0;
    double dx = (imgx / 2.0) - dcx;
    double dy = (imgy / 2.0) - dcy;

    ZBuffer zbuffer(imgx, imgy);

    // move points

    img::EasyImage img(imgx, imgy, bgc);
    for (auto it: lines) {
        it.getp1()->setX(dx + (d * it.getp1()->getX()) );
        unsigned int x1 = roundToInt(it.getp1()->getX());
        it.getp1()->setY(dy + (d * it.getp1()->getY()) );
        unsigned int y1 = roundToInt(it.getp1()->getY());
        it.getp2()->setX(dx + (d * it.getp2()->getX()) );
        unsigned int x2 = roundToInt(it.getp2()->getX());
        it.getp2()->setY(dy + (d * it.getp2()->getY()) );
        unsigned int y2 = roundToInt(it.getp2()->getY());

        double z1 = it.getz1();
        double z2 = it.getz2();

        if (zbuf) {
            draw_zbuf_line( zb, img, x1, y1, z1, x2, y2, z2, it.getColor() );
        } else {
            img.draw_line( x1, y1, x2, y2, it.getColor());
        }

    }

    return img;
}
