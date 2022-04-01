#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Nef_polyhedron_3.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef CGAL::Nef_polyhedron_3<Kernel> Nef_polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;
typedef Polyhedron::Vertex_iterator Vertex_iterator;

// ## STRUCTURE PROVIDED IN ASSIGNMENT DESCRIPTION ##
template <class HDS>

struct Polyhedron_builder : public CGAL::Modifier_base<HDS> {
    std::vector<Point> vertices;
    std::vector<std::vector<unsigned long>> faces;

    Polyhedron_builder() = default;
    void operator()(HDS& hds) {
      CGAL::Polyhedron_incremental_builder_3<HDS> builder(hds, true);
      std::cout << "building surface with " << vertices.size() << " vertices and " << faces.size() << " faces" << std::endl;

      builder.begin_surface(vertices.size(), faces.size());
      for (auto const &vertex: vertices) builder.add_vertex(vertex);
      for (auto const &face: faces) builder.add_facet(face.begin(), face.end());
      builder.end_surface();
    }
};

struct Shell_explorer {
    std::vector<Point> vertices;
    std::vector<std::vector<unsigned long>> faces;

    void visit(Nef_polyhedron::Vertex_const_handle v) {}
    void visit(Nef_polyhedron::Halfedge_const_handle he) {}
    void visit(Nef_polyhedron::SHalfedge_const_handle she) {}
    void visit(Nef_polyhedron::SHalfloop_const_handle shl) {}
    void visit(Nef_polyhedron::SFace_const_handle sf) {}

    void visit(Nef_polyhedron::Halffacet_const_handle hf) {
      std::cout <<"ok" <<std::endl;
    }
};
