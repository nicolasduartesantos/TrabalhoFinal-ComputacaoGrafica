#include "Cube.h"
#include "Mesh.h"
#include "Mesh2.h"
#include "MeshTexturized.h"
#include <iostream>

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
    mesh->addFace(new Face(3, 16, 0));
    mesh->addFace(new Face(11, 17, 7));
    mesh->addFace(new Face(3, 8, 17));

    return mesh;
}

/*
Mesh* Cube::createComplex(Vector* center_base, double edgeSize, Vector* kd, Vector* ke, Vector* ka, double shininess, Cluster* cluster) {

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
    Vector* vertex9 = new Vector(center_base->getCoordinate(0) + (edgeSize * 1.5), center_base->getCoordinate(1) + (edgeSize / 2), center_base->getCoordinate(2));
    Vector* vertex10 = new Vector(center_base->getCoordinate(0) - (edgeSize * 1.5), center_base->getCoordinate(1) + (edgeSize / 2), center_base->getCoordinate(2));

    mesh->addVertex(vertex1);
    mesh->addVertex(vertex2);
    mesh->addVertex(vertex3);
    mesh->addVertex(vertex4);
    mesh->addVertex(vertex5);
    mesh->addVertex(vertex6);
    mesh->addVertex(vertex7);
    mesh->addVertex(vertex8);
    mesh->addVertex(vertex9);
    mesh->addVertex(vertex10);

    for (int i = 0; i < mesh->getVertices().size(); i++) {
        mesh->initial_vertices.push_back(new Vector(mesh->getVertices()[0]->getCoordinate(0), mesh->getVertices()[1]->getCoordinate(1), mesh->getVertices()[2]->getCoordinate(2)));
    }

    mesh->initial_vertices.push_back(new Vector(vertex1->getCoordinate(0), vertex1->getCoordinate(1), vertex1->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex2->getCoordinate(0), vertex2->getCoordinate(1), vertex2->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex3->getCoordinate(0), vertex3->getCoordinate(1), vertex3->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex4->getCoordinate(0), vertex4->getCoordinate(1), vertex4->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex5->getCoordinate(0), vertex5->getCoordinate(1), vertex5->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex6->getCoordinate(0), vertex6->getCoordinate(1), vertex6->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex7->getCoordinate(0), vertex7->getCoordinate(1), vertex7->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex8->getCoordinate(0), vertex8->getCoordinate(1), vertex8->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex9->getCoordinate(0), vertex9->getCoordinate(1), vertex9->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex10->getCoordinate(0), vertex10->getCoordinate(1), vertex10->getCoordinate(2)));


    //edges
    mesh->addEdge(new Edge(0, 1)); //0
    mesh->addEdge(new Edge(1, 2));//1
    mesh->addEdge(new Edge(2, 3));//2
    mesh->addEdge(new Edge(3, 0));//3
    mesh->addEdge(new Edge(4, 5));//4
    mesh->addEdge(new Edge(5, 6));//5
    mesh->addEdge(new Edge(6, 7));//6
    mesh->addEdge(new Edge(7, 4));//7
    mesh->addEdge(new Edge(0, 4));//8
    mesh->addEdge(new Edge(1, 5));//9
    mesh->addEdge(new Edge(2, 6));//10
    mesh->addEdge(new Edge(3, 7));//11
    mesh->addEdge(new Edge(2, 7));//12
    mesh->addEdge(new Edge(5, 7));//13
    mesh->addEdge(new Edge(5, 2));//14
    mesh->addEdge(new Edge(1, 4));//15
    mesh->addEdge(new Edge(1, 3));//16
    mesh->addEdge(new Edge(3, 4));//17
    mesh->addEdge(new Edge(7, 9));//18
    mesh->addEdge(new Edge(6, 9));//19
    mesh->addEdge(new Edge(2, 9));//20
    mesh->addEdge(new Edge(3, 9));//21
    mesh->addEdge(new Edge(4, 10));//22
    mesh->addEdge(new Edge(5, 10));//23
    mesh->addEdge(new Edge(1, 10));//24
    mesh->addEdge(new Edge(0, 10));//25

    //faces
    mesh->addFace(new Face(6, 10, 12));//0
    mesh->addFace(new Face(12, 2, 11));//1
    mesh->addFace(new Face(7, 4, 13));//2
    mesh->addFace(new Face(13, 5, 6));//3
    mesh->addFace(new Face(5, 14, 10));//4
    mesh->addFace(new Face(9, 1, 14));//5
    mesh->addFace(new Face(4, 15, 9));//6
    mesh->addFace(new Face(8, 0, 15));//7
    mesh->addFace(new Face(1, 16, 2));//8
    mesh->addFace(new Face(3, 16, 0));//9
    mesh->addFace(new Face(11, 17, 7));//10
    mesh->addFace(new Face(3, 8, 17));//11
    mesh->addFace(new Face(21, 18, 11));
    mesh->addFace(new Face(2, 20, 21));
    mesh->addFace(new Face(20, 19, 10));
    mesh->addFace(new Face(18, 19, 6));
    mesh->addFace(new Face(24, 9, 23));
    mesh->addFace(new Face(23, 22, 4));
    mesh->addFace(new Face(22, 25, 8));
    mesh->addFace(new Face(25, 0, 24));

    
    return mesh;
}*/


Mesh2* Cube::createComplex(Vector* kd, Vector* ke, Vector* ka, double shininess, Cluster* cluster) {

    Mesh2* mesh = new Mesh2(kd, ke, ka, shininess, cluster);

    //vertices
    Vector* vertex1 = new Vector(0.000000, 0.724319, 0.000000);
    Vector* vertex2 = new Vector(0.101530, 1.178639, 0.148010);
    Vector* vertex3 = new Vector(0.143348, 0.872970, 0.171692);
    Vector* vertex4 = new Vector(-0.101530, 1.178639, 0.148010);
    Vector* vertex5 = new Vector(-0.143348, 0.872970, 0.171692);
    Vector* vertex6 = new Vector(-0.143348, 0.872970, 0.000000);
    Vector* vertex7 = new Vector(0.095250, 1.278639, 0.000000);
    Vector* vertex8 = new Vector(-0.095250, 1.278639, 0.000000);
    Vector* vertex9 = new Vector(0.143348, 0.872970, 0.000000);
    Vector* vertex10 = new Vector(-0.200000, 1.502128, 0.000000);
    Vector* vertex11 = new Vector(0.600000, 1.500000, 0.000000);
    Vector* vertex12 = new Vector(0.000000, 1.300000, 0.000000);
    Vector* vertex13 = new Vector(-0.000000, 1.702128, 0.000000);
    Vector* vertex14 = new Vector(-0.109280, 0.800000, 0.086035);
    Vector* vertex15 = new Vector(0.000000, 0.000000, 0.076035);
    Vector* vertex16 = new Vector(0.000000, 0.800000, 0.232577);
    Vector* vertex17 = new Vector(0.109280, 0.800000, 0.086035);
    Vector* vertex18 = new Vector(-0.078058, 1.278058, 0.160000);
    Vector* vertex19 = new Vector(-0.000000, 1.200000, 0.760000);
    Vector* vertex20 = new Vector(-0.078058, 1.143884, 0.160000);
    Vector* vertex21 = new Vector(0.056116, 1.278058, 0.160000);
    Vector* vertex22 = new Vector(-0.000000, 1.501596, 0.198010);
    Vector* vertex23 = new Vector(-0.106272, 1.048041, 0.124192);
    Vector* vertex24 = new Vector(0.106272, 1.048041, 0.124192);
    Vector* vertex25 = new Vector(0.106272, 1.048041, 0.000000);
    Vector* vertex26 = new Vector(-0.106272, 1.048041, 0.000000);
    Vector* vertex27 = new Vector(0.184307, 1.559332, 0.123756);
    Vector* vertex28 = new Vector(0.168236, 1.658126, 0.104701);
    Vector* vertex29 = new Vector(0.154242, 1.559332, 0.155941);
    Vector* vertex30 = new Vector(0.138172, 1.658126, 0.136887);
    Vector* vertex31 = new Vector(0.101530, 1.178639, -0.148010);
    Vector* vertex32 = new Vector(0.143348, 0.872970, -0.171692);
    Vector* vertex33 = new Vector(-0.101530, 1.178639, -0.148010);
    Vector* vertex34 = new Vector(-0.143348, 0.872970, -0.171692);
    Vector* vertex35 = new Vector(-0.109280, 0.800000, -0.086035);
    Vector* vertex36 = new Vector(0.000000, 0.000000, -0.076035);
    Vector* vertex37 = new Vector(0.000000, 0.800000, -0.232577);
    Vector* vertex38 = new Vector(0.109280, 0.800000, -0.086035);
    Vector* vertex39 = new Vector(-0.078058, 1.278058, -0.160000);
    Vector* vertex40 = new Vector(-0.000000, 1.200000, -0.760000);
    Vector* vertex41 = new Vector(-0.078058, 1.143884, -0.160000);
    Vector* vertex42 = new Vector(0.056116, 1.278058, -0.160000);
    Vector* vertex43 = new Vector(-0.000000, 1.501596, -0.198010);
    Vector* vertex44 = new Vector(-0.106272, 1.048041, -0.124192);
    Vector* vertex45 = new Vector(0.106272, 1.048041, -0.124192);
    Vector* vertex46 = new Vector(0.184307, 1.559332, -0.123756);
    Vector* vertex47 = new Vector(0.168236, 1.658126, -0.104701);
    Vector* vertex48 = new Vector(0.154242, 1.559332, -0.155941);
    Vector* vertex49 = new Vector(0.138172, 1.658126, -0.136887);


    mesh->addVertex(vertex1);
    mesh->addVertex(vertex1);
    mesh->addVertex(vertex2);
    mesh->addVertex(vertex3);
    mesh->addVertex(vertex4);
    mesh->addVertex(vertex5);
    mesh->addVertex(vertex6);
    mesh->addVertex(vertex7);
    mesh->addVertex(vertex8);
    mesh->addVertex(vertex9);
    mesh->addVertex(vertex10);
    mesh->addVertex(vertex11);
    mesh->addVertex(vertex12);
    mesh->addVertex(vertex13);
    mesh->addVertex(vertex14);
    mesh->addVertex(vertex15);
    mesh->addVertex(vertex16);
    mesh->addVertex(vertex17);
    mesh->addVertex(vertex18);
    mesh->addVertex(vertex19);
    mesh->addVertex(vertex20);
    mesh->addVertex(vertex21);
    mesh->addVertex(vertex22);
    mesh->addVertex(vertex23);
    mesh->addVertex(vertex24);
    mesh->addVertex(vertex25);
    mesh->addVertex(vertex26);
    mesh->addVertex(vertex27);
    mesh->addVertex(vertex28);
    mesh->addVertex(vertex29);
    mesh->addVertex(vertex30);
    mesh->addVertex(vertex31);
    mesh->addVertex(vertex32);
    mesh->addVertex(vertex33);
    mesh->addVertex(vertex34);
    mesh->addVertex(vertex35);
    mesh->addVertex(vertex36);
    mesh->addVertex(vertex37);
    mesh->addVertex(vertex38);
    mesh->addVertex(vertex39);
    mesh->addVertex(vertex40);
    mesh->addVertex(vertex41);
    mesh->addVertex(vertex42);
    mesh->addVertex(vertex43);
    mesh->addVertex(vertex44);
    mesh->addVertex(vertex45);
    mesh->addVertex(vertex46);
    mesh->addVertex(vertex47);
    mesh->addVertex(vertex48);
    mesh->addVertex(vertex49);

    mesh->initial_vertices.push_back(new Vector(vertex1->getCoordinate(0), vertex1->getCoordinate(1), vertex1->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex1->getCoordinate(0), vertex1->getCoordinate(1), vertex1->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex2->getCoordinate(0), vertex2->getCoordinate(1), vertex2->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex3->getCoordinate(0), vertex3->getCoordinate(1), vertex3->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex4->getCoordinate(0), vertex4->getCoordinate(1), vertex4->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex5->getCoordinate(0), vertex5->getCoordinate(1), vertex5->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex6->getCoordinate(0), vertex6->getCoordinate(1), vertex6->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex7->getCoordinate(0), vertex7->getCoordinate(1), vertex7->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex8->getCoordinate(0), vertex8->getCoordinate(1), vertex8->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex9->getCoordinate(0), vertex9->getCoordinate(1), vertex9->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex10->getCoordinate(0), vertex10->getCoordinate(1), vertex10->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex11->getCoordinate(0), vertex11->getCoordinate(1), vertex11->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex12->getCoordinate(0), vertex12->getCoordinate(1), vertex12->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex13->getCoordinate(0), vertex13->getCoordinate(1), vertex13->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex14->getCoordinate(0), vertex14->getCoordinate(1), vertex14->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex15->getCoordinate(0), vertex15->getCoordinate(1), vertex15->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex16->getCoordinate(0), vertex16->getCoordinate(1), vertex16->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex17->getCoordinate(0), vertex17->getCoordinate(1), vertex17->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex18->getCoordinate(0), vertex18->getCoordinate(1), vertex18->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex19->getCoordinate(0), vertex19->getCoordinate(1), vertex19->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex20->getCoordinate(0), vertex20->getCoordinate(1), vertex20->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex21->getCoordinate(0), vertex21->getCoordinate(1), vertex21->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex22->getCoordinate(0), vertex22->getCoordinate(1), vertex22->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex23->getCoordinate(0), vertex23->getCoordinate(1), vertex23->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex24->getCoordinate(0), vertex24->getCoordinate(1), vertex24->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex25->getCoordinate(0), vertex25->getCoordinate(1), vertex25->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex26->getCoordinate(0), vertex26->getCoordinate(1), vertex26->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex27->getCoordinate(0), vertex27->getCoordinate(1), vertex27->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex28->getCoordinate(0), vertex28->getCoordinate(1), vertex28->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex29->getCoordinate(0), vertex29->getCoordinate(1), vertex29->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex30->getCoordinate(0), vertex30->getCoordinate(1), vertex30->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex31->getCoordinate(0), vertex31->getCoordinate(1), vertex31->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex32->getCoordinate(0), vertex32->getCoordinate(1), vertex32->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex33->getCoordinate(0), vertex33->getCoordinate(1), vertex33->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex34->getCoordinate(0), vertex34->getCoordinate(1), vertex34->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex35->getCoordinate(0), vertex35->getCoordinate(1), vertex35->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex36->getCoordinate(0), vertex36->getCoordinate(1), vertex36->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex37->getCoordinate(0), vertex37->getCoordinate(1), vertex37->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex38->getCoordinate(0), vertex38->getCoordinate(1), vertex38->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex39->getCoordinate(0), vertex39->getCoordinate(1), vertex39->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex40->getCoordinate(0), vertex40->getCoordinate(1), vertex40->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex41->getCoordinate(0), vertex41->getCoordinate(1), vertex41->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex42->getCoordinate(0), vertex42->getCoordinate(1), vertex42->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex43->getCoordinate(0), vertex43->getCoordinate(1), vertex43->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex44->getCoordinate(0), vertex44->getCoordinate(1), vertex44->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex45->getCoordinate(0), vertex45->getCoordinate(1), vertex45->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex46->getCoordinate(0), vertex46->getCoordinate(1), vertex46->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex47->getCoordinate(0), vertex47->getCoordinate(1), vertex47->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex48->getCoordinate(0), vertex48->getCoordinate(1), vertex48->getCoordinate(2)));
    mesh->initial_vertices.push_back(new Vector(vertex49->getCoordinate(0), vertex49->getCoordinate(1), vertex49->getCoordinate(2)));

    mesh->addFace(new Face2(23, 3, 24));
    mesh->addFace(new Face2(1, 9, 3));
    mesh->addFace(new Face2(25, 2, 24));
    mesh->addFace(new Face2(4, 26, 23));
    mesh->addFace(new Face2(6, 1, 5));
    mesh->addFace(new Face2(11, 22, 12));
    mesh->addFace(new Face2(15, 16, 14));
    mesh->addFace(new Face2(15, 14, 17));
    mesh->addFace(new Face2(15, 17, 16));
    mesh->addFace(new Face2(17, 14, 16));
    mesh->addFace(new Face2(19, 18, 20));
    mesh->addFace(new Face2(20, 18, 21));
    mesh->addFace(new Face2(20, 21, 19));
    mesh->addFace(new Face2(21, 18, 19));
    mesh->addFace(new Face2(12, 22, 10));
    mesh->addFace(new Face2(10, 22, 13));
    mesh->addFace(new Face2(22, 11, 13));
    mesh->addFace(new Face2(23, 6, 5));
    mesh->addFace(new Face2(3, 5, 1));
    mesh->addFace(new Face2(9, 24, 3));
    mesh->addFace(new Face2(24, 4, 23));
    mesh->addFace(new Face2(8, 2, 7));
    mesh->addFace(new Face2(32, 44, 45));
    mesh->addFace(new Face2(1, 32, 9));
    mesh->addFace(new Face2(25, 31, 7));
    mesh->addFace(new Face2(26, 33, 44));
    mesh->addFace(new Face2(6, 34, 1));
    mesh->addFace(new Face2(11, 12, 43));
    mesh->addFace(new Face2(36, 35, 37));
    mesh->addFace(new Face2(36, 38, 35));
    mesh->addFace(new Face2(36, 37, 38));
    mesh->addFace(new Face2(38, 37, 35));
    mesh->addFace(new Face2(40, 41, 39));
    mesh->addFace(new Face2(41, 42, 39));
    mesh->addFace(new Face2(41, 40, 42));
    mesh->addFace(new Face2(42, 40, 39));
    mesh->addFace(new Face2(12, 10, 43));
    mesh->addFace(new Face2(10, 13, 43));
    mesh->addFace(new Face2(43, 13, 11));
    mesh->addFace(new Face2(6, 44, 34));
    mesh->addFace(new Face2(32, 1, 34));
    mesh->addFace(new Face2(9, 45, 25));
    mesh->addFace(new Face2(44, 31, 45));
    mesh->addFace(new Face2(31, 8, 7));
    mesh->addFace(new Face2(23, 5, 3));
    mesh->addFace(new Face2(25, 7, 2));
    mesh->addFace(new Face2(4, 8, 26));
    mesh->addFace(new Face2(23, 26, 6));
    mesh->addFace(new Face2(9, 25, 24));
    mesh->addFace(new Face2(24, 2, 4));
    mesh->addFace(new Face2(8, 4, 2));
    mesh->addFace(new Face2(32, 34, 44));
    mesh->addFace(new Face2(25, 45, 31));
    mesh->addFace(new Face2(26, 8, 33));
    mesh->addFace(new Face2(6, 26, 44));
    mesh->addFace(new Face2(9, 32, 45));
    mesh->addFace(new Face2(44, 33, 31));
    mesh->addFace(new Face2(31, 33, 8));
    mesh->addFace(new Face2(27, 30, 29));
    mesh->addFace(new Face2(46, 49, 47));
    mesh->addFace(new Face2(27, 28, 30));
    mesh->addFace(new Face2(46, 48, 49));


    return mesh;
}



MeshTexturized* Cube::createWithTexture(Vector* center_base, double edgeSize, Image* texture, double shininess, Cluster* cluster) {

    MeshTexturized* mesh = new MeshTexturized(texture, shininess, cluster);

    //vertices
    Vector* vertex1 = new Vector(center_base->getCoordinate(0) - (edgeSize / 2), center_base->getCoordinate(1), center_base->getCoordinate(2) - (edgeSize / 2));
    Vector* vertex2 = new Vector(center_base->getCoordinate(0) - (edgeSize / 2), center_base->getCoordinate(1), center_base->getCoordinate(2) - (edgeSize / 2) + 5.0);
    Vector* vertex3 = new Vector(center_base->getCoordinate(0) + (edgeSize / 2), center_base->getCoordinate(1), center_base->getCoordinate(2) - (edgeSize / 2) + 5.0);
    Vector* vertex4 = new Vector(center_base->getCoordinate(0) + (edgeSize / 2), center_base->getCoordinate(1), center_base->getCoordinate(2) - (edgeSize / 2));
    Vector* vertex5 = new Vector(center_base->getCoordinate(0) - (edgeSize / 2), center_base->getCoordinate(1) + edgeSize, center_base->getCoordinate(2) - (edgeSize / 2));
    Vector* vertex6 = new Vector(center_base->getCoordinate(0) - (edgeSize / 2), center_base->getCoordinate(1) + edgeSize, center_base->getCoordinate(2) - (edgeSize / 2) + 5.0);
    Vector* vertex7 = new Vector(center_base->getCoordinate(0) + (edgeSize / 2), center_base->getCoordinate(1) + edgeSize, center_base->getCoordinate(2) - (edgeSize / 2) + 5.0);
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
    mesh->addFace(new FaceTexturized(6, 10, 12));
    mesh->addFace(new FaceTexturized(12, 2, 11));
    mesh->addFace(new FaceTexturized(7, 4, 13));
    mesh->addFace(new FaceTexturized(13, 5, 6));
    mesh->addFace(new FaceTexturized(5, 14, 10));
    mesh->addFace(new FaceTexturized(9, 1, 14));
    mesh->addFace(new FaceTexturized(4, 15, 9));
    mesh->addFace(new FaceTexturized(8, 0, 15));
    mesh->addFace(new FaceTexturized(1, 16, 2));
    mesh->addFace(new FaceTexturized(3, 16, 0));
    mesh->addFace(new FaceTexturized(11, 17, 7));
    mesh->addFace(new FaceTexturized(3, 8, 17));

    return mesh;
}

