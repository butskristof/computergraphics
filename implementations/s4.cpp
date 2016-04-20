void draw_zbuf_line(ZBuffer &zb, img::EasyImage &img, unsigned int x0, unsigned int y0, double z0, unsigned int x1, unsigned int y1, unsigned int z1, img::Color color) {

    // function for drawing zbuffered lines, mostly copied from image.draw_line()

    if ( x0 == x1 ) {
        int c = 0;
        for ( unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); ++i) {
            double p = (double) (c) / (std::max(y0, y1) - std::min(y0, y1));
            double xi, yi;
            xi = x0;
            yi = i;
            double z;
            if ( y0 == std::min(y0, y1) ) {
                z = ( p / z0 ) + ( (1.0 - p) / z1);
            } else {
                z = ( p / z1 ) + ( (1.0 - p) / z0);
            }

            if ( z < zb.buffer[xi][yi] ) {
                zb.buffer[xi][yi] = z;
                img(xi, yi) = color;
            }
            ++c;
        }
    } else if ( y0 == y1 ) {

        int c = 0;
        for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); ++i) { 
            double p = (double) (c) / ( std::max(x0, x1) - std::min(x0, x1) );
            double xi, yi;

            xi = i;
            yi = y0;
            double z;

            if ( x0 == std::min(x0, x1) ) {
                z = ( p / z0 ) + ( (1.0-p) / z1 );
            } else {
                z = ( p / z1 ) + ( (1.0-p) / z0 );
            }

            if ( z < zb.buffer[xi][yi] ) {
                zb.buffer[xi][yi] = z;
                img(xi, yi) = color;
            }
            ++c;
        }

    } else {
        
        if ( x0 > x1 ) {
            // flip points if x1 > x0, x0 should be lowest value
            std::swap(x0, x1);
            std::swap(y0, y1);
            std::swap(z0, z1);
        }

        double m = ( (double) y1 - (double) y0 ) / ( (double) x1 - (double) x0 );

        if ( -1.0 <= m && m <= 1.0 ) {
            for ( unsigned int i = 0; i <= (x1 - x0); ++i ) {
                double p = (double ( (x1 - x0 - i) / (double) (x1 - x0)); // p: 1 -> 0
                double xi, yi;
            }
        }

    }



    return;
}
