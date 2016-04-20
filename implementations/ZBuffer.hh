#include <vector>

class ZBuffer {
    private:
        std::vector< std::vector< double > > buffer;

    public:
        ZBuffer(const int width, const int height);
}
