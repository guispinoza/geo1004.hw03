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
typedef Nef_polyhedron::Halffacet_cycle_const_iterator Halffacet_iterator;

struct Shell_explorer {
    bool first; //Check if the current shell is the first shell i.e. the outer shell
    std::vector<Point> vertices; //Global store of vertices
    std::vector<std::vector<std::vector<unsigned long>>> faces; //Stores faces of one shell
    std::vector<int> surfsem; //Stores semantics of outer shell

    //Visit functions
    void visit(Nef_polyhedron::Vertex_const_handle v) {}
    void visit(Nef_polyhedron::Halfedge_const_handle he) {}
    void visit(Nef_polyhedron::SHalfedge_const_handle she) {}
    void visit(Nef_polyhedron::SHalfloop_const_handle shl) {}
    void visit(Nef_polyhedron::SFace_const_handle sf) {}
    void visit(Nef_polyhedron::Halffacet_const_handle hf) {
      std::vector<unsigned long> face; //Will contain indices of vertices of face
      for (Halffacet_iterator it = hf->facet_cycles_begin(); it != hf->facet_cycles_end(); it++) {
        Nef_polyhedron::SHalfedge_const_handle sedge = Nef_polyhedron::SHalfedge_const_handle(it);
        CGAL_assertion(sedge!=0);
        //Iterate through halfedges of halffacet
        Nef_polyhedron::SHalfedge_around_facet_const_circulator hc_start(sedge);
        Nef_polyhedron::SHalfedge_around_facet_const_circulator hc_end(hc_start);
        CGAL_For_all(hc_start,hc_end) {
          Nef_polyhedron::SVertex_const_handle svert = hc_start->source();
          Point vpoint = svert->center_vertex()->point();//Calculate vertices
          std::vector<Point>::iterator it = std::find(vertices.begin(), vertices.end(), vpoint);
          if(it != vertices.end()) {//Vertex exists in global list of vertices
            face.push_back(it - vertices.begin());
          }
          else {//Vertex doesn't exist in global list of vertices
            face.push_back(vertices.size());
            vertices.push_back(vpoint);
          }
        }
      }
      //Define semantics
      if (first == true) {//Outer Shell
        Kernel::RT znt = hf->plane().orthogonal_direction().dz();
        double zval = CGAL::to_double(znt);
        if (zval > 1e-9) {//Points up -> Roof
          surfsem.push_back(0);
        } else if (zval < 1e-9) {//Points down -> Floor
          surfsem.push_back(2);
        } else {//Points sideways -> Wall
          surfsem.push_back(1);
        }
      }
      std::vector<std::vector<unsigned long>> facesurf = {face};
      faces.push_back({facesurf});
    }
};

