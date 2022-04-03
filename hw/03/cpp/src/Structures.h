struct Face {
    std::vector<unsigned long> vertices; // indices in a vector of points
};

struct Shell {
    std::vector<Face> faces;
};

struct Object {
    std::string id;
    std::vector<Shell> shells;
};
