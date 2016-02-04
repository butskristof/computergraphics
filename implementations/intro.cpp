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
