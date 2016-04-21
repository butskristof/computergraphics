void draw_zbuf_line(ZBuffer &zb, img::EasyImage &img, unsigned int x0, unsigned int y0, double z0, unsigned int x1, unsigned int y1, double z1, img::Color color) {

    // function for drawing zbuffered lines, mostly copied from image.draw_line()

    // for each px on line
    //      calculate 1/z value
    //      if ( 1/z value < zbuffered value) 
    //          overwrite
    //      else 
    //          nothing
    if ( x0 == x1 ) {
        int c = 0;
        for ( unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); ++i ) {
            // 1/z value
            double p = (double) c / ( std::max(y0, y1) - std::min(y0, y1) ); // p e [0, 1]
            double xi, yi; // current coordinate
            xi = x0;
            yi = i;
            double z; // actually 1/z, but for simplicity called z here

            if ( y0 == std::min(y0, y1) ) {
                z = ( p / z0 ) + ( (1.0-p) / z1 );
            } else { 
                z = ( p / z1 ) + ( (1.0-p) / z0 );
            }

            if ( z < zb.buffer.at(xi).at(yi) ) {
                // update buffer and replace color
                zb.buffer[xi][yi] = z;
                img(xi, yi) = color;
            }

            c++;
        }
    } else if ( y0 == y1 ) {
        int c = 0;
        for ( unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); ++i ) {
            // 1/z value
            double p = (double) c / ( std::max(x0, x1) - std::min(x0, x1) ); // p e [0, 1]
            double xi, yi; // current coordinate
            xi = i;
            yi = y0;
            double z; // actually 1/z, but for simplicity called z here

            if ( x0 == std::min(x0, x1) ) {
                z = ( p / z0 ) + ( (1.0-p) / z1 );
            } else { 
                z = ( p / z1 ) + ( (1.0-p) / z0 );
            }

            if ( z < zb.buffer[xi][yi] ) {
                // update buffer and replace color
                zb.buffer[xi][yi] = z;
                img(xi, yi) = color;
            }

            c++;
            
        }
    } else {
        if ( x0 > x1 ) { // flip points if necessary, x0 should have lowest value
            std::swap(x0, x1);
            std::swap(y0, y1);
            std::swap(z0, z1);
        }

        double m = ( (double) y1 - (double) y0 ) / ( (double) x1 - (double) x0 );

        if ( -1.0 <= m and m <= 1.0 ) {
            for ( unsigned int i = 0; i <= (x1 - x0); ++i ) {
                
                double p = (double) (x1 - x0 - i) / (double) (x1 - x0);
                double xi, yi;
                xi = roundToInt( ( p * x0 ) + ( (1.0-p) * x1 ) );
                yi = roundToInt( ( p * y0 ) + ( (1.0-p) * y1 ) );
                double z = ( p / z0 ) + ( (1.0-p) / z1 );

                if ( z < zb.buffer[xi][yi] ) {
                    zb.buffer[xi][yi] = z;
                    img(xi, yi) = color;
                }

            }
            
            
        } else if ( m > 1.0 ) {
            
            for ( unsigned int i = 0; i <= (y1 - y0); ++i ) {
                
                double p = (double) (y1 - y0 - i) / (double) (y1 - y0);
                double xi, yi;
                xi = roundToInt( ( p * x0 ) + ( (1.0-p) * x1 ) );
                yi = roundToInt( ( p * y0 ) + ( (1.0-p) * y1 ) );
                double z = ( p / z0 ) + ( (1.0-p) / z1 );

                if ( z < zb.buffer[xi][yi] ) {
                    zb.buffer[xi][yi] = z;
                    img(xi, yi) = color;
                }

            }

        } else if ( m < -1.0 )  {
            for ( unsigned int i = 0; i <= (y0 - y1); ++i ) {
                
                double p = (double) (y0 - y1 - i) / (double) (y0 - y1);
                double xi, yi;
                xi = roundToInt( ( p * x0 ) + ( (1.0-p) * x1 ) );
                yi = roundToInt( ( p * y0 ) + ( (1.0-p) * y1 ) );
                double z = ( p / z0 ) + ( (1.0-p) / z1 );

                if ( z < zb.buffer[xi][yi] ) {
                    zb.buffer[xi][yi] = z;
                    img(xi, yi) = color;
                }

            }
        }
    }


    return;
}
