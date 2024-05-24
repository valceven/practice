#include <cstdlib>
#include <cstring>
#include <iostream>
#include "graph.h"
#include "vertex.h"

using namespace std;

class GraphList : public Graph {
    Vertex** s_vertices;
    int num_vert;
    int s_edges[100][3]; // Array to store edges and their vertices
    int num_edge;

public:
    GraphList() {
        s_vertices = new Vertex*[10];
        num_vert = 0;
        num_edge = 0;
    }

    int numVertices() {
        return num_vert;
    }

    char* vertices() {
        char* vert = new char[num_vert];
        for (int i = 0; i < num_vert; i++) {
            vert[i] = s_vertices[i]->getName();
        }
        return vert;
    }

    int numEdges() {
        return num_edge;
    }

    int* edges() {
        int* edgeList = new int[num_edge];
        for (int i = 0; i < num_edge; i++) {
            edgeList[i] = s_edges[i][2];
        }
        return edgeList;
    }

    int getEdge(char u, char v) {
        for (int i = 0; i < num_edge; i++) {
            if ((s_edges[i][0] == u && s_edges[i][1] == v) || 
                (s_edges[i][0] == v && s_edges[i][1] == u)) {
                return s_edges[i][2];
            }
        }
        return -1; // Edge not found
    }

    char* endVertices(int e) {
        char* verts = new char[2];
        for (int i = 0; i < num_edge; i++) {
            if (s_edges[i][2] == e) {
                verts[0] = s_edges[i][0];
                verts[1] = s_edges[i][1];
                return verts;
            }
        }
        return NULL; // Edge not found
    }

    char opposite(char v, int e) {
        for (int i = 0; i < num_edge; i++) {
            if (s_edges[i][2] == e) {
                if (s_edges[i][0] == v) return s_edges[i][1];
                if (s_edges[i][1] == v) return s_edges[i][0];
            }
        }
        return '-'; // Edge or vertex not found
    }

    int outDegree(char v) {
        for (int i = 0; i < num_vert; i++) {
            if (s_vertices[i]->getName() == v) {
                return s_vertices[i]->getNumOutEdges();
            }
        }
        return 0; // Vertex not found
    }

    int inDegree(char v) {
        int degree = 0;
        for (int i = 0; i < num_edge; i++) {
            if (s_edges[i][1] == v) {
                degree++;
            }
        }
        return degree;
    }

    int* outgoingEdges(char v) {
        for (int i = 0; i < num_vert; i++) {
            if (s_vertices[i]->getName() == v) {
                return s_vertices[i]->getOutEdges();
            }
        }
        return NULL; // Vertex not found
    }

    int* incomingEdges(char v) {
        int* inEdges = new int[100];
        int count = 0;
        for (int i = 0; i < num_edge; i++) {
            if (s_edges[i][1] == v) {
                inEdges[count++] = s_edges[i][2];
            }
        }
        return inEdges;
    }

    bool insertVertex(char x) {
        if (num_vert >= 10) {
            return false;
        }
        Vertex* vert = new Vertex(x);
        s_vertices[num_vert++] = vert;
        return true;
    }

    bool insertEdge(char u, char v, int x) {
        int j = -1, k = -1;
        for (int i = 0; i < num_vert; i++) {
            if (s_vertices[i]->getName() == u) j = i;
            if (s_vertices[i]->getName() == v) k = i;
        }
        if (j == -1 || k == -1) return false; // One of the vertices not found

        s_vertices[j]->addOutEdge(x);
        s_vertices[k]->addOutEdge(x);
        s_edges[num_edge][0] = u;
        s_edges[num_edge][1] = v;
        s_edges[num_edge][2] = x;
        num_edge++;
        return true;
    }

    int removeVertex(char v) {
        int index = -1;
        for (int i = 0; i < num_vert; i++) {
            if (s_vertices[i]->getName() == v) {
                index = i;
                break;
            }
        }
        if (index == -1) return 0; // Vertex not found

        delete s_vertices[index];
        for (int i = index; i < num_vert - 1; i++) {
            s_vertices[i] = s_vertices[i + 1];
        }
        num_vert--;
        return 1; // Vertex removed successfully
    }

    bool removeEdge(int e) {
        int index = -1;
        for (int i = 0; i < num_edge; i++) {
            if (s_edges[i][2] == e) {
                index = i;
                break;
            }
        }
        if (index == -1) return false; // Edge not found

        for (int i = index; i < num_edge - 1; i++) {
            s_edges[i][0] = s_edges[i + 1][0];
            s_edges[i][1] = s_edges[i + 1][1];
            s_edges[i][2] = s_edges[i + 1][2];
        }
        num_edge--;
        return true; // Edge removed successfully
    }

    void print() {
        for (int i = 0; i < num_vert; i++) {
            s_vertices[i]->toString();
            cout << endl;
        }
    }
};

