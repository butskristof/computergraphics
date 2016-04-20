#include "ZBuffer.hh"
#include <limits>

ZBuffer::ZBuffer(const int width, const int height) {
    for ( int i = 0 ; i < width ; ++i) {
            std::vector<double> t;
        for ( jnt j = 0 ; j < height ; ++j) {
            t.push_back( std::numberic_limits<double>::infinity() );
        }
        this->buffer.push_back(t);
}
