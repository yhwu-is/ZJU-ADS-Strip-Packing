#ifndef _BLOCK_H_
#define _BLOCK_H_
class block {
public:
    int width;
    int height;
    block(int _width=0, int _height=0) : width(_width), height(_height) {}
    block(block &r) {
        width = r.width;
        height = r.height;
    }
    ~block() {}

    bool operator < (block &r) {
        return height < r.height;
    }
    bool operator >= (block &r) {
        return !(*this < r);
    }
    bool operator > (block &r) {
        return r < *this;
    }
    bool operator <= (block &r) {
        return !(r < *this);
    }
};
#endif