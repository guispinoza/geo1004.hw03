#pragma once


#include "helpstructCGAL.h"
//calling structures
struct Face;
struct Shell;
struct Object;
struct Vertex;
// struct Shell_explorer;

int shell_id = 0;

struct Vertex {
    // the coordinates of this vertex:
    Point point;

    // constructor without arguments
    Vertex() : point(Point()) {}

    // constructor with x,y,z arguments to immediately initialise the point member on this Vertex.
    Vertex(const double &x, const double &y, const double &z) : point(Point(x, y, z)) {}
};

struct Face {
    std::vector<int> vertices; // indices in a vector of points
    int a,b,c;

};

struct Shell {
    std::vector<Face> faces;
};

struct Object {
    std::string id;
    std::vector<Shell> shells;
};

/* # STRUCT TO FIND THE SHELLS AND EXTRACT THEIR GEOMETRIES
struct Shell_explorer {
    std::vector<Point> vertices;
    std::vector<std::vector<unsigned long>> faces;

    void visit(Nef_polyhedron::Vertex_const_handle v) {}
    void visit(Nef_polyhedron::Halfedge_const_handle he) {}
    void visit(Nef_polyhedron::SHalfedge_const_handle she) {}
    void visit(Nef_polyhedron::SHalfloop_const_handle shl) {}
    void visit(Nef_polyhedron::SFace_const_handle sf) {}

    void visit(Nef_polyhedron::Halffacet_const_handle hf) {
      ... // do something to each half-face of a shell
    }
};*/
