#ifndef TUNKS_VERTEX_HPP
#define TUNKS_VERTEX_HPP

struct Vertex {
    float x;
    float y;
    float z;

    float r;
    float g;
    float b;
    float a;

    Vertex(float x, float y, float z, float r, float g, float b, float a) : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}

};

#endif
