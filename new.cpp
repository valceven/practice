





#include <cstdlib>
#include <iostream>
#include "graph.h"
#include "vertex.h"
using namespace std;

class GraphList : public Graph {
    Vertex** s_vertices;
    int num_vert;
    int s_edges[100];
    int num_edge;

    public:
    GraphList() {
        s_vertices = (Vertex**) malloc( 10 * sizeof(Vertex*) );
        num_vert = 0;
        num_edge = 0;
    }

    int numVertices() {
        return num_vert;
    }

    char* vertices() {
        char* vert = (char*) calloc(num_vert, sizeof(char));
        int count = 0;
        for (int i = 0; i< num_vert; i++) {
            vert[count++] + s_vertices[i]->getName();
        }
        return vert;
    }

    int numEdges() {
        return num_edge;
    }

    int* edges() {
        return s_edges;
    }

    int getEdge(char u, char v)  {
        return 0;
    }

    char* endVertices(int e)  {
        return NULL;
    }

    char opposite(char v, int e)  {
        return '-';
    }

    int outDegree(char v)  {
        return 0;
    }

    int inDegree(char v)  {
        return 0;
    }

    int* outgoingEdges(char v) {
        return NULL;
    }

    int* incomingEdges(char v) {
        return NULL;
    }

    bool insertVertex(char x)  {
        if (num_vert > 10) {
            return false;
        }
        Vertex* vert = new Vertex (x);
        s_vertices[num_vert++] = vert;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        int j, k;
        for (int i = 0; i < num_vert; i++) {
            if (s_vertices[i]->getName() == u){
                j = i;
            }
            if (s_vertices[i]->getName() == v){
                k = i;
            }
        }
        s_vertices[j] ->addOutEdge(x);
        s_vertices[k] ->addOutEdge(x);
        s_edges[num_edge++] = x;
        return true;
    }

    int removeVertex(char v) {
        return 0;
    }

    bool removeEdge(int e)  {
        return false;
    }

    void print() {
        for (int i = 0; i < num_vert; i++) {
            s_vertices[i]->toString();
            cout << endl;
        }
    }
};





#include <cstdlib>
#include <iostream>
#include "graph.h"
using namespace std;

class GraphMatrix : public Graph {
    int matrix[10][10];
    char s_vertices[100];
    int num_vert;
    int s_edges[100];
    int num_edge;

    bool insertVertex(char x)  {
        s_vertices[num_vert] = x;
        num_vert++;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        int u_ind = 0, v_ind = 0;
        for (int i = 0; i < num_vert; i++) {
            if (u == s_vertices[i]) {
                u_ind = i;
            }
            if (v == s_vertices[i]) {
                v_ind = i;
            }
        }
        if (matrix[u_ind][v_ind] != 0) {
            cout << "Not null" << endl;
            return false;
        }
        matrix[u_ind][v_ind] = x;
        matrix[v_ind][u_ind] = x;
        s_edges[num_edge] = x;
        num_edge++;
        return true;
    }

    int distance(char u, char v) {
        // TODO returns the distance from vertex u to vertex v
        int u_ind = 0, v_ind = 0;
        int temp1 = 0, temp2 = 0;
        for (int i = 0; i < num_vert; i++) {
            if (u == s_vertices[i]) {
                u_ind = i;
            }
            if (v == s_vertices[i]) {
                v_ind = i;
            }
        }
        
        temp1 = matrix[u_ind][v_ind];
        temp2 = matrix[v_ind][u_ind];

        if (temp1 != 0 || temp2 != 0) {
            return (temp1 + temp2)/2;
        }
        if (temp1 == temp2) {
            return 0;
        }
        return -1;
    }

    void print() {
        cout << "\t";
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < num_vert; i++) {
            cout << s_vertices[i] << "\t";
            for (int j = 0; j < num_vert; j++) {
                // cout << "i: " << i << " | j: " << j << endl;
                if (matrix[i][j] != 0) {
                    cout << matrix[i][j];
                }
                cout << "\t";
            }
            cout << endl;
        }
    }
};