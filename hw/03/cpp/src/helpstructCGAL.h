#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Nef_polyhedron_3.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
<<<<<<< Updated upstream
typedef CGAL::Nef_polyhedron_3<Kernel> Nef_polyhedron;
=======
typedef CGAL::Nef_polyhedron_3<Kernel> Nef_polyhedron;
typedef Polyhedron::HalfedgeDS HalfedgeDS;

// ## STRUCTURE PROVIDED IN ASSIGNMENT DESCRIPTION ##
//template <class HDS>

// struct Polyhedron_builder : public CGAL::Modifier_base<HDS> {
//     std::vector<Point> vertices;
//     std::vector<std::vector<unsigned long>> faces;

//     Polyhedron_builder() = default;
//     void operator()(HDS& hds) {
//       CGAL::Polyhedron_incremental_builder_3<HDS> builder(hds, true);
//       std::cout << "building surface with " << vertices.size() << " vertices and " << faces.size() << " faces" << std::endl;

//       builder.begin_surface(vertices.size(), faces.size());
//       for (auto const &vertex: vertices) builder.add_vertex(vertex);
//       for (auto const &face: faces) builder.add_facet(face.begin(), face.end());
//       builder.end_surface();
//     }
// };

/*
Polyhedron polyhedron;
Polyhedron_builder<Polyhedron::HalfedgeDS> polyhedron_builder;
for (auto const &face: ...) {
polyhedron_builder.faces.emplace_back();
for (auto const &vertex: face.vertices) {
polyhedron_builder.vertices.push_back(...);
polyhedron_builder.faces.back().push_back(...);
}
} polyhedron.delegate(polyhedron_builder);
*/
>>>>>>> Stashed changes
