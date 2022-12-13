#include "Cube.h"

Mesh* Cube::create(Vector* center_base, double edgeSize, Vector* kd, Vector* ke, Vector* ka, double shininess, Cluster* cluster) {

    Mesh* mesh = new Mesh(kd, ke, ka, shininess, cluster);

    //vertices
    Vector* vertex1 = new Vector(center_base->getCoordinate(0) - (edgeSize / 2), center_base->getCoordinate(1), center_base->getCoordinate(2) - (edgeSize / 2));
    Vector* vertex2 = new Vector(center_base->getCoordinate(0) - (edgeSize / 2), center_base->getCoordinate(1), center_base->getCoordinate(2) + (edgeSize / 2));
    Vector* vertex3 = new Vector(center_base->getCoordinate(0) + (edgeSize / 2), center_base->getCoordinate(1), center_base->getCoordinate(2) + (edgeSize / 2));
    Vector* vertex4 = new Vector(center_base->getCoordinate(0) + (edgeSize / 2), center_base->getCoordinate(1), center_base->getCoordinate(2) - (edgeSize / 2));
    Vector* vertex5 = new Vector(center_base->getCoordinate(0) - (edgeSize / 2), center_base->getCoordinate(1) + edgeSize, center_base->getCoordinate(2) - (edgeSize / 2));
    Vector* vertex6 = new Vector(center_base->getCoordinate(0) - (edgeSize / 2), center_base->getCoordinate(1) + edgeSize, center_base->getCoordinate(2) + (edgeSize / 2));
    Vector* vertex7 = new Vector(center_base->getCoordinate(0) + (edgeSize / 2), center_base->getCoordinate(1) + edgeSize, center_base->getCoordinate(2) + (edgeSize / 2));
    Vector* vertex8 = new Vector(center_base->getCoordinate(0) + (edgeSize / 2), center_base->getCoordinate(1) + edgeSize, center_base->getCoordinate(2) - (edgeSize / 2));

    mesh->addVertex(vertex1);
    mesh->addVertex(vertex2);
    mesh->addVertex(vertex3);
    mesh->addVertex(vertex4);
    mesh->addVertex(vertex5);
    mesh->addVertex(vertex6);
    mesh->addVertex(vertex7);
    mesh->addVertex(vertex8);

    mesh->initial_vertices.push_back(new Vector(vertex1->getCoordinate(0), vertex1->getCoordinate(1), vertex1->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex2->getCoordinate(0), vertex2->getCoordinate(1), vertex2->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex3->getCoordinate(0), vertex3->getCoordinate(1), vertex3->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex4->getCoordinate(0), vertex4->getCoordinate(1), vertex4->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex5->getCoordinate(0), vertex5->getCoordinate(1), vertex5->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex6->getCoordinate(0), vertex6->getCoordinate(1), vertex6->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex7->getCoordinate(0), vertex7->getCoordinate(1), vertex7->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex8->getCoordinate(0), vertex8->getCoordinate(1), vertex8->getCoordinate(2)));


    //edges
    mesh->addEdge(new Edge(0, 1));
    mesh->addEdge(new Edge(1, 2));
    mesh->addEdge(new Edge(2, 3));
    mesh->addEdge(new Edge(3, 0));
    mesh->addEdge(new Edge(4, 5));
    mesh->addEdge(new Edge(5, 6));
    mesh->addEdge(new Edge(6, 7));
    mesh->addEdge(new Edge(7, 4));
    mesh->addEdge(new Edge(0, 4));
    mesh->addEdge(new Edge(1, 5));
    mesh->addEdge(new Edge(2, 6));
    mesh->addEdge(new Edge(3, 7));
    mesh->addEdge(new Edge(2, 7));
    mesh->addEdge(new Edge(5, 7));
    mesh->addEdge(new Edge(5, 2));
    mesh->addEdge(new Edge(1, 4));
    mesh->addEdge(new Edge(1, 3));
    mesh->addEdge(new Edge(3, 4));

    //faces
    mesh->addFace(new Face(6, 10, 12));
    mesh->addFace(new Face(12, 2, 11));
    mesh->addFace(new Face(7, 4, 13));
    mesh->addFace(new Face(13, 5, 6));
    mesh->addFace(new Face(5, 14, 10));
    mesh->addFace(new Face(9, 1, 14));
    mesh->addFace(new Face(4, 15, 9));
    mesh->addFace(new Face(8, 0, 15));
    mesh->addFace(new Face(1, 16, 2));
    mesh->addFace(new Face(3, 16, 10));
    mesh->addFace(new Face(11, 17, 7));
    mesh->addFace(new Face(3, 8, 17));

    return mesh;
}
