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
