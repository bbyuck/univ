#include <iostream>
#include <string>
#include <vector>

#define MAX_VTXS 256

using namespace std;

class vnode {
public:
	int elem;
	int degree;
	vnode* link;

	vnode(int o) {
		elem = o;
		degree = 0;
		link = NULL;
	}
	void linking(vnode* opposite) {
		link = opposite;
	}
	vnode* opposite() {
		return link;
	}

	bool isAdjacent(vnode* v) {
		return link == v;
	}
};

class enode {
public:
	int weight;
	vnode* start;
	vnode* end;

	enode(vnode* v, vnode* w, int o) {
		weight = o;
		start = v;
		end = w;
	}
};

class graph {
public:
	vector<vnode*> adjacencyList[MAX_VTXS];
	vector<vnode*> vertices;
	vector<enode*> edges;

	graph() {
	}

	bool isEmpty() {
		return vertices.size() == 0;
	}
	bool isFull() {
		return vertices.size() >= MAX_VTXS;
	}

	void addVertex(int o) {
		vnode* newVertex = new vnode(o);
		vertices.push_back(newVertex);
	}

	void addEdge(int v, int w, int o) {
		vnode *vn = NULL;
		vnode *wn = NULL;

		for (int i = 0; i < vertices.size(); i++) {
			if (vertices[i]->elem == v) {
				vn = vertices[i];
			}
			if (vertices[i]->elem == w) {
				wn = vertices[i];
			}
			if (vn != NULL && wn != NULL) {
				break;
			}
		}
		if (vn != NULL && wn != NULL) {
			vn->link = wn;
			wn->link = vn;
		}
		enode* newEdge = new enode(vn, wn, o);
		edges.push_back(newEdge);

		adjacencyList[v].push_back(wn);
		adjacencyList[w].push_back(vn);
	}


	void eraseVertex(int v) {
		for (int i = 0; i < adjacencyList[v].size();) {
			eraseEdge(v, adjacencyList[v][i]->elem);
		}
		for (int i = 0; i < vertices.size(); i++) {
			if (vertices[i]->elem == v) {
				vertices.erase(vertices.begin() + i);
			}
		}
	}


	void eraseEdge(int v, int w) {
		int e = edges.size();
		int a_v = adjacencyList[v].size();
		int a_w = adjacencyList[w].size();
		for (int i = 0; i < e; i++) {
			if ((edges[i]->start->elem == v && edges[i]->end->elem == w) || (edges[i]->start->elem == w && edges[i]->end->elem == v)) {
				edges.erase(edges.begin() + i);
				break;
			}
		}
		for (int i = 0; i < a_v; i++) {
			if (adjacencyList[v][i]->elem == w) {
				adjacencyList[v].erase(adjacencyList[v].begin() + i);
				break;
			}
		}
		for (int i = 0; i < a_w; i++) {
			if (adjacencyList[w][i]->elem == v) {
				adjacencyList[w].erase(adjacencyList[w].begin() + i);
				break;
			}
		}
	}

	vector<enode*> getEdges() {
		return edges;
	}

	vector<vnode*> getVertices() {
		return vertices;
	}

	vector<vnode*> neighbors(int v) {
		return adjacencyList[v];
	}
};

int main() {
	graph mg;

	mg.addVertex(4);
	mg.addVertex(7);
	mg.addVertex(12);
	mg.addVertex(5);
	mg.addVertex(33);


	mg.addEdge(4, 7, 0);
	mg.addEdge(5, 12, 0);
	mg.addEdge(5, 7, 0);
	mg.addEdge(5, 33, 0);
	mg.addEdge(7, 33, 0);

	cout << "adjacency list : \n";
	for (int i = 0; i < MAX_VTXS; i++) {
		if (!mg.adjacencyList[i].empty()) {
			cout << i << " - ";
			for (int j = 0; j < mg.adjacencyList[i].size(); j++) {
				cout << mg.adjacencyList[i][j]->elem << " ";
			}
			cout << endl;
		}
	}
	cout << "\nedges :\n";
	for (unsigned int i = 0; i < mg.getEdges().size(); i++) {
		cout << mg.getEdges()[i]->start->elem << " " << mg.getEdges()[i]->end->elem << endl;
	}

	cout << "\nvertices :\n";
	for (unsigned int i = 0; i < mg.getVertices().size(); i++) {
		cout << mg.getVertices()[i]->elem << " ";
	}
	cout << endl;


	mg.eraseEdge(12, 5);

	cout << "\nedges :\n";
	for (unsigned int i = 0; i < mg.getEdges().size(); i++) {
		cout << mg.getEdges()[i]->start->elem << " " << mg.getEdges()[i]->end->elem << endl;
	}

	mg.eraseVertex(7);

	cout << "\nadjacency list : \n";
	for (int i = 0; i < MAX_VTXS; i++) {
		if (!mg.adjacencyList[i].empty()) {
			cout << i << " - ";
			for (int j = 0; j < mg.adjacencyList[i].size(); j++) {
				cout << mg.adjacencyList[i][j]->elem << " ";
			}
			cout << endl;
		}
	}
	cout << "\nvertices :\n";
	for (unsigned int i = 0; i < mg.getVertices().size(); i++) {
		cout << mg.getVertices()[i]->elem << " ";
	}
	cout << endl;

	return 0;
}

