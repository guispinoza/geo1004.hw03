struct Face {
    std::vector<unsigned long> vertices; // indices in a vector of points
    int a,b,c;
};

struct Shell {
    std::vector<Face> faces;
};

struct Object {
    std::string id;
    std::vector<Shell> shells;
};
