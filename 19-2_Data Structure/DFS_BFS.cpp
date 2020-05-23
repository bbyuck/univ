#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MappingSize 501
#define VISITED 1
#define UNVISITED 0

class node {
public:
	int data;
	node* next;
	node(int d) {
		data = d;
		next = NULL;
	}
};

class queue {
public:
	node* f;
	node* t;
	int n;

	queue() {
		f = NULL;
		t = NULL;
		n = 0;
	}

	bool isEmpty() {
		return n == 0;
	}
	int size() {
		return n;
	}

	void enqueue(int d) {
		node* newNode = new node(d);
		if (isEmpty()) {
			f = newNode;
			t = newNode;
			n++;
			return;
		}
		t->next = newNode;
		t = newNode;
		n++;
	}

	int dequeue() {
		if (isEmpty()) {
			return -1;
		}
		else {
			int val = f->data;
			node* tmp = f;
			f = f->next;
			delete tmp;
			n--;
			return val;
		}
	}
};

class vertex {
public:
	vertex* prev;
	vertex* next;
	int degree;
	int data;
	int flag;
	vertex(int data) {
		this->degree = 0;
		this->data = data;
		degree = 0;
		this->flag = UNVISITED;
		next = NULL;
		prev = NULL;
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
	edge* prev;
	edge* next;
	vertex* source;
	vertex* destination;
	string data;
	edge(vertex* a, vertex* b, string data) {
		this->source = a;
		this->destination = b;
		this->data = data;
		next = NULL;
		prev = NULL;
	}
};

class DoublyVertexLinkedList {	
public:
	vertex* head;
	vertex* tail;
	int count;
	DoublyVertexLinkedList() {
		this->head = NULL;
		this->tail = NULL;
		count = 0;
	}
	void insert(vertex* insertVertex) {
		if (this->head == NULL) {
			head = insertVertex;
			tail = insertVertex;
		}
		else {
			tail->next = insertVertex;
			insertVertex->prev = tail;
			tail = insertVertex;
		}
		count++;
	}
	void remove(vertex* delVertex) {
		if (delVertex == head || delVertex == tail) {
			if (delVertex == head && delVertex != tail) {
				vertex* temp = head;
				head = head->next;
				head->prev = NULL;
				delete temp;
			}
			else if (delVertex == tail && delVertex != head) {
				vertex* temp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
			}
			else { head = tail = NULL; }
		}
		else {
			delVertex->prev->next = delVertex->next;
			delVertex->next->prev = delVertex->prev;
			delete delVertex;
		}
		count--;
	}
};

class DoublyEdgeLinkedList {		
public:
	edge* head;
	edge* tail;
	int count;

	DoublyEdgeLinkedList() {
		this->head = NULL;
		this->tail = NULL;
		count = 0;
	}
	void insert(edge* insertEdge) {
		if (this->head == NULL) {
			head = insertEdge;
			tail = insertEdge;
		}
		else {
			tail->next = insertEdge;
			insertEdge->prev = tail;
			tail = insertEdge;
		}
		count++;
	}
	void remove(edge* delEdge) {
		if (delEdge == head || delEdge == tail) {
			if (delEdge == head && delEdge != tail) {
				edge* temp = head;
				head = head->next;
				head->prev = NULL;
				delete temp;
			}
			else if (delEdge == tail && delEdge != head) {
				edge* temp = tail;
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
			}
			else { head = tail = NULL; }
		}
		else {
			delEdge->prev->next = delEdge->next;
			delEdge->next->prev = delEdge->prev;
			delete delEdge;
		}
		count--;
	}
};

class graph {
public:
	edge*** edgeMatrix;						
	DoublyVertexLinkedList* VertexList;		
	DoublyEdgeLinkedList* EdgeList;			
	int vertexSize;							
	int mappingTable[MappingSize];			
											
	graph() {
		this->VertexList = new DoublyVertexLinkedList();
		this->EdgeList = new DoublyEdgeLinkedList();
		this->vertexSize = 0;
		for (int i = 0; i < MappingSize; i++)mappingTable[i] = -1;
		this->edgeMatrix = new edge **[1];
		this->edgeMatrix[0] = new edge*[1];
		this->edgeMatrix[0][0] = NULL;
	}
	bool isfindVertex(int n) {		
		bool flag = false;
		vertex* temp = VertexList->head;
		while (temp != NULL) {
			if (temp->data == n) {
				flag = true;
				break;
			}
			temp = temp->next;
		}
		return flag;
	}
	vertex* findVertex(int n) {				
		vertex* temp = VertexList->head;   
		while (temp != NULL) {
			if (temp->data == n) {
				break;
			}
			temp = temp->next;
		}
		return temp;
	}

	void insert_vertex(int n) {			
		if (isfindVertex(n) == true) {
			return;
		}

		else {
			edge*** tempMatrix = new edge **[vertexSize + 1];  //������ 1�� �߰��� ������ 
			for (int i = 0; i < vertexSize + 1; i++) {        //���� matrix���� ����, ���� ���̰� 1��ŭ 
				tempMatrix[i] = new edge * [vertexSize + 1];	  //�� ū tempmatrix ����
				for (int j = 0; j < vertexSize + 1; j++) {
					tempMatrix[i][j] = NULL;
				}
			}

			for (int i = 0; i < vertexSize; i++) {
				for (int j = 0; j < vertexSize; j++) {
					tempMatrix[i][j] = this->edgeMatrix[i][j];	 //element��  copy
				}
			}

			this->edgeMatrix = tempMatrix;

			vertex* newVertex = new vertex(n);
			VertexList->insert(newVertex);						//VertexList�� ������ȣ�� n�� vertex �߰�
			this->vertexSize++;
			mappingTable[vertexSize - 1] = n;					// mappingtable�� vertex �ڽ��� 
		}														//matrix�� ��� index���� ����
	}


	void erase_vertex(int n) {                          // �׷����� ������ ��ȣ�� n�� vertex ����
		if (isfindVertex(n) == false || vertexSize == 0) {
			return;
		}
		else {
			edge*** tempMatrix = new edge * *[vertexSize - 1]; //������ 1�� ������ ������
			for (int i = 0; i < vertexSize - 1; i++) {       //���� matrix���� ����, ���� ���̰� 1��ŭ
				tempMatrix[i] = new edge * [vertexSize - 1];   //�� ���� tempmatrix ����
				for (int j = 0; j < vertexSize - 1; j++) {
					tempMatrix[i][j] = NULL;
				}
			}

			int middleIdx = 0;
			for (int i = 0; i < vertexSize; i++) {
				if (mappingTable[i] == n)middleIdx = i;		//middleidx: ������ vertex�� matrix������ �ε���
			}
			for (int i = middleIdx; i < vertexSize; i++) {	// mappingtable update
				mappingTable[i] = mappingTable[i + 1];
			}


			for (int i = 0; i < vertexSize; i++) {			//EdgeList���� ������ȣ�� n�� vertex�� ����� ��� edge�� ����
				if (this->edgeMatrix[middleIdx][i] != NULL) {
					EdgeList->remove(this->edgeMatrix[middleIdx][i]);
				}
			}

			for (int i = 0; i < vertexSize; i++) {			//middleidx�� �������� element���� ������ copy
				for (int j = 0; j < vertexSize; j++) {
					if (i < middleIdx && j < middleIdx) {
 						tempMatrix[i][j] = this->edgeMatrix[i][j];
					}
					else if (i > middleIdx&& j > middleIdx) {
						tempMatrix[i - 1][j - 1] = this->edgeMatrix[i][j];
					}
					else if (j > middleIdx) {
						tempMatrix[i][j - 1] = this->edgeMatrix[i][j];
					}
					else if (i > middleIdx) {
						tempMatrix[i - 1][j] = this->edgeMatrix[i][j];
					}
				}
			}
			this->edgeMatrix = tempMatrix;
			VertexList->remove(findVertex(n));			//VertexList�� ������ȣ�� n�� vertex ����
			this->vertexSize--;

		}
	}

	void insert_edge(int indirectSource, int IndirectDestination, string data) {
		if (isfindVertex(indirectSource) == false || isfindVertex(IndirectDestination) == false) {
			cout << -1 << endl;
			return;
		}

		int destination = -1;
		int source = -1;
		for (int i = 0; i <= vertexSize; i++) {
			if (mappingTable[i] == IndirectDestination)destination = i;
			if (mappingTable[i] == indirectSource)source = i;
			if (source != -1 && destination != -1)break;
		}

		if (edgeMatrix[source][destination] != NULL || edgeMatrix[destination][source] != NULL) {
			cout << -1 << endl;
			return;
		}

		edge* newEdge = new edge(findVertex(indirectSource), findVertex(IndirectDestination), data);
		edgeMatrix[source][destination] = newEdge;
		edgeMatrix[destination][source] = newEdge;

		findVertex(indirectSource)->increase_degree();
		findVertex(IndirectDestination)->increase_degree();

		EdgeList->insert(newEdge);
	}

	void erase_edge(int indirectSource, int IndirectDestination) {
		int destination = -1;
		int source = -1;
		for (int i = 0; i <= vertexSize; i++) {
			if (mappingTable[i] == IndirectDestination)destination = i;
			if (mappingTable[i] == indirectSource)source = i;
			if (source != -1 && destination != -1)break;
		}

		if (edgeMatrix[source][destination] == NULL || edgeMatrix[destination][source] == NULL)return;
		findVertex(indirectSource)->decrease_degree();
		findVertex(IndirectDestination)->decrease_degree();

		edge* delEdge = edgeMatrix[source][destination];
		EdgeList->remove(delEdge);

		edgeMatrix[source][destination] = NULL;
		edgeMatrix[destination][source] = NULL;
	}

	int getVertexCnt() {
		return VertexList->count;
	}
	int getEdgeCnt() {
		return EdgeList->count;
	}

	int isAdjacent(int v, int w) {
		vertex* B = findVertex(w);
		vertex* A = findVertex(v);
		edge* tmp = EdgeList->head;
		if (A == NULL || B == NULL) {
			return -1;
		}

		for (int i = 0; i < EdgeList->count; i++) {
			if ((tmp->source == A && tmp->destination == B) || (tmp->source == B && tmp->destination == A)) {
				return 1;
			}
			tmp = tmp->next;
		}
		return -1;
	}

	vector<int> neighbors(int v) {
		vector<int> n;
		edge* tmp;
		int idx = 0;
		for (int i = 0; i < vertexSize; i++) {
			if (mappingTable[i] == v) {
				idx = i;
				break;
			}
		}

		for (int i = 0; i < vertexSize; i++) {
			tmp = edgeMatrix[idx][i];
			if (tmp != NULL) {
				n.push_back(i);
			}
		}
		return n;
	}
};

void _BFS(graph G, int v) {
	vector<vector<int>> L;
	vector<int> L0;
	L0.push_back(v);

	vertex* w = G.findVertex(v);
	w->flag = VISITED;

	int i = 0;
	cout << "L" << i << ": [ " << v << " ]" << endl;

	L.push_back(L0);
	while (!L[i].empty()) {
		vector<int> Lp;
		cout << "L" << i + 1 << ": [ ";
		for (int j = 0; j < L[i].size(); j++) {
			for (int k = 0; k < G.neighbors(L[i][j]).size(); k++) {
				w = G.findVertex(G.mappingTable[G.neighbors(L[i][j])[k]]);
				if (w->flag == UNVISITED) {
					w->flag = VISITED;
					cout << G.mappingTable[G.neighbors(L[i][j])[k]] << " ";
					Lp.push_back(G.mappingTable[G.neighbors(L[i][j])[k]]);
				}
			}
		}
		cout << "]" << endl;
		L.push_back(Lp);
		i++;
	}
}

void BFS(graph G, int v) {
	queue Q;
	Q.enqueue(v);
	int u;
	vertex* w = G.findVertex(v);
	w->flag = VISITED;
	
	while (!Q.isEmpty()) {
		u = Q.dequeue();
		cout << u << " ";
		for (int i = 0; i < G.neighbors(u).size(); i++) {
			w = G.findVertex(G.mappingTable[G.neighbors(u)[i]]);
			if (w->flag == UNVISITED) {
				w->flag = VISITED;
				Q.enqueue(G.mappingTable[G.neighbors(u)[i]]);
			}
		}
	}
	cout << endl;
}

void BFS_Traverse(graph G, int v) {
	vertex* tar = G.VertexList->head;
	while (tar != NULL) {
		tar->flag = UNVISITED;
		tar = tar->next;
	}
	tar = G.VertexList->head;
	while (tar != NULL) {
		if (tar->flag == UNVISITED) {
			_BFS(G, v);
		}
		tar = tar->next;
	}
}

void DFS(graph G, int v) {
	vertex* tar = G.findVertex(v);
	tar->flag = VISITED;
	cout << v << " ";
	vertex* w;
	for (unsigned int i = 0; i < G.neighbors(v).size(); i++) {
		w = G.findVertex(G.mappingTable[G.neighbors(v)[i]]);
		if (w->flag == UNVISITED) {
			DFS(G, w->data);
		}
	}

}

void DFS_Traverse(graph G, int v) {
	vertex* tar = G.VertexList->head;;
	while(tar != NULL) {
		tar->flag = UNVISITED;
		tar = tar->next;
	}
	tar = G.VertexList->head;
	while(tar != NULL) {
		if (tar->flag == UNVISITED) {
			DFS(G, v);
		}
		tar = tar->next;
	}
}



int main() {
	graph mg;
	int N;
	int M;
	int K;

	int I;
	int S, D;
	int start;
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		cin >> I;
		mg.insert_vertex(I);
	}
	for (int i = 0; i < M; i++) {
		cin >> S >> D;
		mg.insert_edge(S, D, "e");
	}
	cout << mg.getVertexCnt() << " " << mg.getEdgeCnt() << endl;
	for (int i = 0; i < K; i++) {
		cin >> S >> D;
		cout << mg.isAdjacent(S, D) << endl;
	}
	cin >> start;
	BFS_Traverse(mg, start);
	return 0;
}