#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();

using namespace std;

void exercicio1()
{
    GraphViewer * gv = new GraphViewer(600, 600, true);
    gv->createWindow(600, 600);

    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    gv->addNode(0);
    gv->addNode(1);
    gv->rearrange();

    gv->addEdge(0, 0, 1, EdgeType::DIRECTED);
    gv->removeNode(1);
    gv->addNode(2);

    gv->addEdge(1, 0, 2, EdgeType::DIRECTED);
    gv->setVertexLabel(2, "Node");

    gv->setEdgeLabel(1, "Edge");

    gv->setVertexColor(2, "green");

    gv->setEdgeColor(1, "yellow");
    gv->rearrange();
}

void exercicio2()
{
    GraphViewer * gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);

    gv->addNode(0, 300, 50);
    gv->addNode(1, 318, 58);
    gv->addNode(2, 325, 75);
    gv->addNode(3, 318, 93);
    gv->addNode(4, 300, 100);
    gv->addNode(5, 282, 93);
    gv->addNode(6, 275, 75);
    gv->addNode(7, 282, 58);
    gv->addNode(8, 150, 200);
    gv->addNode(9, 300, 200);
    gv->addNode(10, 450, 200);
    gv->addNode(11, 300, 400);
    gv->addNode(12, 200, 550);
    gv->addNode(13, 400, 550);

    gv->addEdge(0, 0, 1, EdgeType::DIRECTED);
    gv->addEdge(1, 1, 2, EdgeType::DIRECTED);
    gv->addEdge(2, 2, 3, EdgeType::DIRECTED);
    gv->addEdge(3, 3, 4, EdgeType::DIRECTED);
    gv->addEdge(4, 4, 5, EdgeType::DIRECTED);
    gv->addEdge(5, 5, 6, EdgeType::DIRECTED);
    gv->addEdge(6, 6, 7, EdgeType::DIRECTED);
    gv->addEdge(7, 7, 0, EdgeType::DIRECTED);
    gv->addEdge(8, 4, 9, EdgeType::DIRECTED);
    gv->addEdge(9, 9, 8, EdgeType::DIRECTED);
    gv->addEdge(10, 9, 10, EdgeType::DIRECTED);
    gv->addEdge(11, 9, 11, EdgeType::DIRECTED);
    gv->addEdge(12, 11, 12, EdgeType::DIRECTED);
    gv->addEdge(13, 11, 13, EdgeType::DIRECTED);
    gv->rearrange();

    sleep(3);

    gv->removeNode(12);
    gv->removeNode(13);
    gv->rearrange();

    sleep(2);

    gv->addNode(14, 250, 550);
    gv->addNode(15, 350, 550);
    gv->rearrange();
}

void exercicio3()
{
    ifstream nodes("../resources/mapa1/nos.txt");
    ifstream edges("../resources/mapa1/arestas.txt");
    string line;

    GraphViewer * gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);

    while(getline(nodes, line)) {
        stringstream l(line);
        string tok;
        int id, x, y;
        int i = 0;
        while(getline(l, tok, ';')) {
            switch(i) {
                case 0:
                    id = stoi(tok);
                    break;
                case 1:
                    x = stoi(tok);
                    break;
                case 2:
                    y = stoi(tok);
                    break;
            }
            i++;
        }
        gv->addNode(id, x, y);
    }
    while(getline(edges, line)) {
        stringstream l(line);
        string tok;
        int id, x, y;
        int i = 0;
        while(getline(l, tok, ';')) {
            switch(i) {
                case 0:
                    id = stoi(tok);
                    break;
                case 1:
                    x = stoi(tok);
                    break;
                case 2:
                    y = stoi(tok);
                    break;
            }
            i++;
        }
        gv->addEdge(id, x, y, EdgeType::UNDIRECTED);
    }
    edges.close();
    nodes.close();
    gv->rearrange();
}

int main() {
    /*
     * Uncomment the line below to run Exercise 1
     */
    //exercicio1();

    /*
      * Uncomment the line below to run Exercise 2
      */
    //exercicio2();

    /*
      * Uncomment the line below to run Exercise 3
      */
	//
	exercicio3();

	getchar();
	return 0;
}
