#include <cstdlib>
#include <iostream>
#include "graph.h"
using namespace std;
#include <limits>

class GraphMatrix : public Graph {
    int matrix[10][10];
    char s_vertices[10];
    int num_vert;
    int s_edges[100];
    int num_edge;

    public:
    GraphMatrix() {
        num_vert = 0;
        num_edge = 0;
    }

    int numVertices() {
        return num_vert;
    }

    char* vertices() {
        return s_vertices;
    }

    int numEdges() {
        return num_edge;
    }

    int* edges() {
        return s_edges;
    }

    int getEdge(char u, char v)  {
        int i;
        
        for(i = 0; i < num_vert; i++){
            if(u == s_vertices[i]){
                break;
            }
        }
        int j;
        for(j = 0; j < num_vert; j++){
            if(v == s_vertices[j]){
                break;
            }
        }
        return matrix[i][j];
    }

    char* endVertices(int e)  {

        int i,j;
        for(i = 0; i < num_vert; i++){
            for(j = 0; j < num_vert; j++){
                if(matrix[i][j] == e){
                     char* temp = (char*) malloc(2*sizeof(char));
                    temp[0] = s_vertices[i];
                    temp[1] = s_vertices[j];
                    return temp;
                }
            }
        }
        return nullptr;    
    }

    char opposite(char v, int e)  {
       int i,j;
        for(i = 0; i < num_vert; i++){
            for(j = 0; j < num_vert; j++){
                if(matrix[i][j] == e){
                    if(v == s_vertices[i]){
                        return s_vertices[j];
                    }
                    return s_vertices[i];
                    
                }
            }
        }  
    }

    int distance(char u, char v) {
        // Implementing Dijkstra's algorithm for shortest path
        int start, end;
        // Finding indices of vertices u and v
        for (int i = 0; i < num_vert; i++) {
            if (u == s_vertices[i]) start = i;
            if (v == s_vertices[i]) end = i;
        }

        int dist[10]; // Assuming at most 10 vertices
        bool visited[10] = {false}; // Assuming at most 10 vertices
        for (int i = 0; i < num_vert; i++) {
            dist[i] = numeric_limits<int>::max(); // Initialize distances to infinity
        }
        dist[start] = 0; // Distance from start to start is 0

        for (int count = 0; count < num_vert - 1; count++) {
            int min_index, min_value = numeric_limits<int>::max();
            for (int i = 0; i < num_vert; i++) {
                if (!visited[i] && dist[i] < min_value) {
                    min_value = dist[i];
                    min_index = i;
                }
            }
            int u = min_index;
            visited[u] = true;

            // Update dist values of adjacent vertices of the picked vertex
            for (int v = 0; v < num_vert; v++) {
                if (!visited[v] && matrix[u][v] && dist[u] != numeric_limits<int>::max() && dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                }
            }
        }

        // Return the shortest distance to the end vertex
        return dist[end];
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
        s_vertices[num_vert] = x;
        num_vert++;
        return true;
    }

    bool insertEdge(char u, char v, int x)  {
        int i;
        
        for(i = 0; i < num_vert; i++){
            if(u == s_vertices[i]){
                break;
            }
        }
        int j;
        for(j = 0; j < num_vert; j++){
            if(v == s_vertices[j]){
                break;
            }
        }
        
        matrix[i][j] = x;
        s_edges[num_edge] = x;
        num_edge++;
        
        return true;
    }

    int removeVertex(char v) {
        return 0;
    }

    bool removeEdge(int e)  {
        return false;
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
                if (matrix[i][j] != 0) {
                    cout << matrix[i][j];
                }
                cout << "\t";
            }
            cout << endl;
        }
    }
};