img::EasyImage colorRectangle( const unsigned int w, const unsigned int h ) {
    img::EasyImage image(w, h);

    for ( unsigned int i = 0; i < w; ++i) {
        for ( unsigned int j = 0; j < h; ++j) {
            image(i, j).red = i;
            image(i, j).green = j;
            image(i, j).blue = (i+j)%256;
        }
    }

    return image;
}

img::EasyImage introBlocks( const unsigned int w, const unsigned int h, const unsigned int nx, const unsigned int ny, const ini::DoubleTuple col1, const ini::DoubleTuple col2 ) {
    img::EasyImage image(w, h);

    // we can suppose nx | w 
    unsigned int bw = w / nx; // width of block
    unsigned int bh = h / ny; // width of block

    for ( int i = 0; i < w; ++i ) {
        for ( int j = 0; j < h; ++j ) {
            // calculate coordinates of block
            unsigned int bx = std::floor(i / bw);
            unsigned int by = std::floor(j / bh);

            if ( ((bx+by)%2) == 0 ) {
                image(i, j) = img::Color(col1);
                /*
                image(i, j).red = col1.at(0) * 255;
                image(i, j).green = col1.at(1) * 255;
                image(i, j).blue = col1.at(2) * 255;
                */
            } else {
                image(i, j) = img::Color(col2);
                /*
                image(i, j).red = col2.at(0) * 255;
                image(i, j).green = col2.at(1) * 255;
                image(i, j).blue = col2.at(2) * 255;
                */
            }
        }
    }

    return image;
}

img::EasyImage introQuarterCircle( const unsigned int w, const unsigned int h, const unsigned int nrLines, const img::Color linecolor, const img::Color bgcolor ) {
    // width, height, # lines, linecolor, bgcolor

    img::EasyImage image(w, h, bgcolor);

    double hs = h / (nrLines - 1);
    double ws = w / (nrLines - 1);

    for ( unsigned int i = 0; i < nrLines; ++i) {
//        image.drawLine( x1, y1, x2, y2, color);
        unsigned int x1 = 0;
        unsigned int y1 = roundToInt( (h-1) - (i*hs) );
        unsigned int x2 = roundToInt( (w-1) - (i*ws) );
        unsigned int y2 = h - 1;
        image.draw_line( x1, y1, x2, y2, linecolor);
    }
    
    return image;
}

img::EasyImage introEye( const unsigned int w, const unsigned int h, const unsigned int nrLines, const img::Color linecolor, const img::Color bgcolor ) {
    img::EasyImage image(w, h, bgcolor);

    double hs = h / (nrLines - 1);
    double ws = w / (nrLines - 1);

    for ( unsigned int i = 0; i < nrLines; ++i) {
        unsigned int x1 = 0;
        unsigned int y1 = roundToInt( (h-1) - (i*hs) );
        unsigned int x2 = roundToInt( (w-1) - (i*ws) );
        unsigned int y2 = h - 1;
        image.draw_line( x1, y1, x2, y2, linecolor);

        x1 = roundToInt( i*ws );
        y1 = 0;
        x2 = w - 1;
        y2 = roundToInt( i*hs );
        image.draw_line( x1, y1, x2, y2, linecolor);
    }

    return image;
}

img::EasyImage introDiamond( const unsigned int w, const unsigned int h, const unsigned int nrLines, const img::Color linecolor, const img::Color bgcolor ) {
    img::EasyImage image(w, h, bgcolor);

    double halfwi = (double)w / 2.0;
    double halfhi = (double)h / 2.0;

    double ws = halfwi / (nrLines - 1);
    double hs = halfhi / (nrLines - 1);

    for ( unsigned int i = 0; i < nrLines; ++i) {
        unsigned int x1, y1, x2, y2;
        // 1st quarter
        x1 = roundToInt((w-1) - (i*ws));
        y1 = roundToInt(halfhi);
        x2 = roundToInt(halfwi);
        y2 = roundToInt((halfhi - 1) + (i*hs));
        image.draw_line(x1, y1, x2, y2, linecolor);
        // 2nd quarter
        x1 = roundToInt((i*ws));
        y1 = roundToInt(halfhi);
        x2 = roundToInt(halfwi);
        y2 = roundToInt((halfhi - 1) + (i*hs));
        image.draw_line(x1, y1, x2, y2, linecolor);
        // 3rd quarter
        x1 = roundToInt((w-1) - (i*ws));
        y1 = roundToInt(halfhi);
        x2 = roundToInt(halfwi);
        y2 = roundToInt((halfhi) - (i*hs));
        image.draw_line(x1, y1, x2, y2, linecolor);
        // 4th quarter
        x1 = roundToInt((i*ws));
        y1 = roundToInt(halfhi);
        x2 = roundToInt(halfwi);
        y2 = roundToInt((halfhi) - (i*hs));
        image.draw_line(x1, y1, x2, y2, linecolor);
    }
    
    return image;
}
