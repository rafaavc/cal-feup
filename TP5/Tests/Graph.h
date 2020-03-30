/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for (typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->dist = DBL_MAX;
        (*it)->path = NULL;
    }

    Vertex<T> * s = findVertex(orig);
    if (s == NULL) return;

    s->dist = 0;

    queue<Vertex<T> *> vertexQueue;

    vertexQueue.push(s);

    while(!vertexQueue.empty()) {
        s = vertexQueue.front();
        vertexQueue.pop();

        for (Edge<T> a : s->adj) {
            if (a.dest->getDist() == DBL_MAX) {
                vertexQueue.push(a.dest);
                a.dest->dist = s->getDist() + 1;
                a.dest->path = s;
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for (typename vector<Vertex<T> *>::const_iterator it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->dist = DBL_MAX;
        (*it)->path = NULL;
    }

    Vertex<T> * s = findVertex(origin);
    if (s == NULL) return;

    s->dist = 0;

    MutablePriorityQueue<Vertex<T>> vertexQueue;

    vertexQueue.insert((Vertex<T> *) s);

    while(!vertexQueue.empty()) {
        s = vertexQueue.extractMin();

        for (Edge<T> a : s->adj) {
            if (a.dest->getDist() > s->getDist() + a.weight) {
                double oldDist = a.dest->getDist();
                a.dest->dist = s->getDist() + a.weight;
                a.dest->path = s;
                if (oldDist == DBL_MAX) {
                    vertexQueue.insert((Vertex<T> *) a.dest);
                } else {
                    vertexQueue.decreaseKey(a.dest);
                }
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	Vertex<T> * v = findVertex(orig);
	if (v == NULL) return;

	for (Vertex<T> * vertex : vertexSet) {
	    vertex->dist = DBL_MAX;
	    vertex->path = NULL;
	}

	v->dist = 0;
	queue<Vertex<T> *> vertexQueue;
	vertexQueue.push(v);
    while(!vertexQueue.empty()) {
        Vertex<T> * vertex = vertexQueue.front();
        vertexQueue.pop();
        for (Edge<T> edge : vertex->adj) {
            if (edge.dest->getDist() > vertex->getDist() + edge.weight) {
                edge.dest->dist = vertex->getDist() + edge.weight;
                edge.dest->path = vertex;
                vertexQueue.push(edge.dest);
            }
        }
	}

    vertexQueue.push(v);
    while(!vertexQueue.empty()) {
        Vertex<T> * vertex = vertexQueue.front();
        vertexQueue.pop();
        for (Edge<T> edge : vertex->adj) {
            if (edge.dest->getDist() > vertex->getDist() + edge.weight) {
                cout << "ERROR: There are cycles of negative weight.\n" << endl;
                return;
            }
        }
    }
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	stack<T> stackRes;
	Vertex<T> * v = findVertex(dest);

	while(true) {
	    stackRes.push(v->getInfo());
	    if (v->getDist() == 0) break;
	    v = v->getPath();
	}

	vector<T> res;
	while(!stackRes.empty()) {
	    res.push_back(stackRes.top());
        stackRes.pop();
	}
	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {

}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;

	return res;
}


#endif /* GRAPH_H_ */
