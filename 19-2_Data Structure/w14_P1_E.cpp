#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define MAX_VERTEX_SIZE 1000

#define NOT_EXPLORED 0
#define DISCOVERY 1
#define BACK 2

#define UNVISITED 0
#define VISITED 1

class vertex {
public:
	vector<vertex*> adj_list;
	int degree;
	int data;
	int flag;
	vertex(int data) {
		this->degree = 0;
		this->data = data;
		this->flag = UNVISITED;
	}
	void increase_degree() {
		this->degree++;
	}
	void decrease_degree() {
		this->degree--;
	}
};

class edge {
public:
	vertex* source;
	vertex* destination;
	string word;
	int edge_stat;
	edge(vertex* src, vertex* dst, string word) {
		this->source = src;
		this->destination = dst;
		this->word = word;
		this->edge_stat = NOT_EXPLORED;
	}
};

class graph {
public:
	vector<vertex*> vertex_list;
	vector<edge*> edge_list;
	int vertex_size;
	int mappingTable[MAX_VERTEX_SIZE];
	edge*** edgeMatrix;

	graph() {
		this->vertex_size = 0;

		for (int i = 0; i < MAX_VERTEX_SIZE; i++) {
			mappingTable[i] = -1;
		}

		edgeMatrix = new edge * *[MAX_VERTEX_SIZE];
		for (int i = 0; i < MAX_VERTEX_SIZE; i++) {
			edgeMatrix[i] = new edge * [MAX_VERTEX_SIZE];
			for (int j = 0; j < MAX_VERTEX_SIZE; j++) {
				edgeMatrix[i][j] = NULL;
			}
		}

	}
	bool isFindVertex(int data) {
		for (int i = 0; i < vertex_size; i++) {
			if (data == mappingTable[i]) {
				return true;
			}
		}
		return false;
	}

	vertex* findVertex(int data) {
		if (!isFindVertex(data)) {
			return NULL;
		}
		for (int i = 0; i < vertex_size;i++) {
			if (vertex_list[i]->data == data) {
				return vertex_list[i];
			}
		}
	}
	bool isFindEdge(int source, int destination) {
		int src_idx = -1;
		int dst_idx = -1;
		for (int i = 0; i < vertex_size; i++) {
			if (mappingTable[i] == source) {
				src_idx = i;
			}
			if (mappingTable[i] == destination) {
				dst_idx = i;
			}
			if (src_idx != -1 && dst_idx != -1) {
				break;
			}
		}

		if (edgeMatrix[src_idx][dst_idx] != NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	edge* findEdge(int source, int destination) {
		if (!isFindEdge(source, destination)) {
			return NULL;
		}
		int src_idx = -1;
		int dst_idx = -1;
		for (int i = 0; i < vertex_size; i++) {
			if (mappingTable[i] == source) {
				src_idx = i;
			}
			if (mappingTable[i] == destination) {
				dst_idx = i;
			}
			if (src_idx != -1 && dst_idx != -1) {
				break;
			}
		}

		return edgeMatrix[src_idx][dst_idx];
	}

	void insert_vertex(int n) {
		if (isFindVertex(n) == true) {
			return;
		}
		else {
			vertex* newVertex = new vertex(n);
			vertex_list.push_back(newVertex);
			mappingTable[vertex_size] = n;
			this->vertex_size++;
		}
	}
	void insert_edge(int source, int destination, string word) {
		if (isFindEdge(source, destination)) {
			cout << -1 << endl;
			return;
		}
		if (isFindVertex(source) == true && isFindVertex(destination) == true) {
			int src_idx = -1;
			int dst_idx = -1;
			vertex* srcVertex = findVertex(source);
			vertex* dstVertex = findVertex(destination);

			srcVertex->adj_list.push_back(dstVertex);
			dstVertex->adj_list.push_back(srcVertex);

			edge* newEdge = new edge(srcVertex, dstVertex, word);		//totaledgelist에 추가될 newedge
			edge_list.push_back(newEdge);

			for (int i = 0; i < vertex_size;i++) {
				if (source == mappingTable[i]) {
					src_idx = i;
				}
				if (destination == mappingTable[i]) {
					dst_idx = i;
				}
				if (src_idx != -1 && dst_idx != -1) {
					break;
				}
			}
			
			edgeMatrix[src_idx][dst_idx] = newEdge;
			edgeMatrix[dst_idx][src_idx] = newEdge;

			edge* tempEdge1 = new edge(srcVertex, dstVertex, word);		//src.incidentedges 에 추가될 new edge
			edge* tempEdge2 = new edge(srcVertex, dstVertex, word);

			srcVertex->increase_degree();
			dstVertex->increase_degree();
		}
		else return;
	}

	void erase_edge(int source, int destination) {
		if (isFindEdge(source, destination) == false) {
			return;
		}
		else {
			edge* delEdge = findEdge(source, destination);

			int src_idx = -1;
			int dst_idx = -1;

			for (int i = 0; i < vertex_size; i++) {
				if (mappingTable[i] == source) {
					src_idx = i;
				}
				if (mappingTable[i] == destination) {
					dst_idx = i;
				}
				if (src_idx != -1 && dst_idx != -1) {
					break;
				}
			}

			edgeMatrix[src_idx][dst_idx] = NULL;
			edgeMatrix[dst_idx][src_idx] = NULL;

			vertex* srcVertex = findVertex(source);
			vertex* dstVertex = findVertex(destination);

			for (int i = 0; i < srcVertex->adj_list.size();i++) {
				if (srcVertex->adj_list[i]->data == destination) {
					srcVertex->adj_list.erase(srcVertex->adj_list.begin() + i);
					break;
				}
			}

			for (int i = 0; i < dstVertex->adj_list.size(); i++) {
				if (dstVertex->adj_list[i]->data == source) {
					dstVertex->adj_list.erase(dstVertex->adj_list.begin() + i);
					break;
				}
			}

			srcVertex->decrease_degree();
			dstVertex->decrease_degree();


			for (int i = 0; i < edge_list.size(); i++) {
				if (edge_list[i] == delEdge) {
					edge_list.erase(edge_list.begin() + i);
				}
			}
		}
	}

	void DFS_Traverse(int v) {
		vertex* start = findVertex(v);
		for (int i = 0; i < vertex_size; i++) {
			vertex_list[i]->flag = UNVISITED;
		}
		DFS(start);
	}

	void DFS(vertex* curV) {
		curV->flag = VISITED;
		cout << curV->data << " ";
		for (int i = 0; i < curV->adj_list.size(); i++) {
			if (curV->adj_list[i]->flag == UNVISITED) {
				DFS(curV->adj_list[i]);
			}
		}
	}
};

int main() {
	int N;
	int M;
	int A;
	int num;
	int S, D;
	graph mg;
	
	cin >> N >> M >> A;

	for (int i = 0; i < N; i++) {
		cin >> num;
		mg.insert_vertex(num);
	}
	for (int i = 0; i < M; i++) {
		cin >> S >> D;
		mg.insert_edge(S, D, "w");
	}

	mg.DFS_Traverse(A);
	cout << endl;
	return 0;
}