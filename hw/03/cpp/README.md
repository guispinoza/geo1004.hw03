# GEO1004
Assignment 3 - Processing a BIM model using CSG

Authors: Eleni Theodoridou, Fabian Visser, Guilherme Spinoza Andreo

## What does the code do?

The code parses the obj file (KIThouse.obj) and converts it into multiple CGAL Polyhedra by generating a CGAL Convex Hull from  the vertices and faces of each shell. Then our code transforms these Polyhedra into Nef Polyhedra, and creates a “Big” nef polyhedra for the space filled by the building’s floors, walls, roofs and shells. Then we extract the geometries of the building’s exterior surface, semantics and individual rooms which are written to a CityJSON file. 

## What files are included?
**main.cpp**

Main program to be executed, instructions on how to build are provided below. Parses the OBJ, creates vectors for each object and vertices, where the shells are added to a vector of each object and the faces are pushed into a vector of the shell of each object. Creates a CGAL polyhedron for every shells which is then used to generate a ```CGAL::convex_hull_3``` that is used to make the multiple ```CGAL Nef Polyhedron```. This result is combined into a single "Big" Nef Polyhedron, where the ```Shell_explorer``` is used to navigate through the exterior, interior and intermediate volumes of the polyhedron to extract the geometries to be written in the final CityJSON file.

**helpstructCGAL.h**

Consists of CGAL libraries, definitions and a ```shell_explorer``` structure that parses the shells by navigating through the nef polyhedron's facets, storing the indices of the vertices to the facets and defines semantics. 

**Structures.h**

Simple structures to help temporarily store the elements related to faces, shells and objects.

**Original IFC Model: [231110AC11-FZK-Haus-IFC.ifc](http://openifcmodel.cs.auckland.ac.nz/Model/Details/109)**

The IFC Model which was converted using [IFCconvert](http://ifcopenshell.org/ifcconvert) with the following command:

```IfcConvert.exe 231110AC11-FZK-Haus-IFC.ifc KIThouse.obj --weld-vertices --orient-shells --include+=entities IfcWallStandardCase IfcSlab --validate```

**Intermediate OBJ (converted from original IFC): KIThouse.obj**

Obj file that contains only the roofs, walls and floors of the house. Composed of objects(g), vertices (v), faces(f) and shells (denoted by usemtl).

**Final CityJSON output file: output.city.json**

The end result when the main.cpp is executed. Consists of a LoD 2.2 type MultiSurface parent Building CityObject enriched with semantics having 4 BuildingRoom(s) as children.

## How to build from command line

The repository is public and available to be cloned.
This code was executed using Clion IDE (Build #CL-213.6777.58) 2021.3.3

Check and edit the CMakelists.txt, so that it is able to find the libraries of their relative paths 

```
    $ git clone https://github.com/guispinoza/geo1004.hw03
    $ cd geo1004.hw03/hw/03/cpp
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ ./hw03
  
```
Or you can download with the zip file, extract and run:
```
    $ cd https://github.com/guispinoza/geo1004.hw03.git/hw/03/cpp
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ ./hw03

```

