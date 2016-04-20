#include <vector>

class ZBuffer {
    private:

    public:
        std::vector< std::vector< double > > buffer;
        ZBuffer(const int width, const int height);
};
