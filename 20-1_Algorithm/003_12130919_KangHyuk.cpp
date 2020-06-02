/*
���� : �˰���
�й� : 003�й�
�й� : 12130919
�̸� : ����
���� : �˰��� ������� 1
*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Mapping ���̺� �ʱ� ������
#define MAX_CITY_NO 1000000
class disjoint_set;

class vertex {
public:
    // linked list�� ���
    vertex* next;
    disjoint_set* mySet; // �ش� vertex�� ���� disjoint set�� �ּ� -> �ʱⰪ NULL

    int city_no;
    string city_name;
    int pop_count;

    int mappingIdx;

    //���̻����� �ʿ��� �⺻������
    vertex() {
        next = NULL;
        mySet = NULL;

        mappingIdx = -1;
        city_no = 0;
        city_name = "";
        pop_count = 0;
    }

    vertex(int _city_no, string _city_name, int _pop_count) {
        next = NULL;
        mySet = NULL;

        mappingIdx = -1;
        city_no = _city_no;
        city_name = _city_name;
        pop_count = _pop_count;
    }

};
class edge {
public:
    vertex* source;
    vertex* dest;
    int distance;

    //���̻����� �ʿ��� �⺻������
    edge() {
        source = NULL;
        dest = NULL;
        distance = 0;
    }

    edge(vertex* _source, vertex* _dest, int _distance) {
        source = _source;
        dest = _dest;
        distance = _distance;
    }

};

class graph {
public:
    vector<vertex*> vertexList;
    vector<edge*> edgeList;
    int vertexSize;
    int max_vertex;
    vector<int> mappingTable;   // vertexList���� city_no�� �����ϱ� ���� �����ϴ� table

    graph(int _max_vertex) {
        vertexSize = 0;
        max_vertex = _max_vertex;
        vertexList.assign(MAX_CITY_NO, NULL);
        mappingTable.assign(50001, -1);
    }

    vertex* findVertex(int key) {
        return vertexList[key];
    }

    void insertVertex(int _city_no, string _city_name, int _pop_count) {
        if (findVertex(_city_no) != NULL) {
            return;
        }
        else {
            vertex* newVertex = new vertex(_city_no, _city_name, _pop_count);
            vertexList[_city_no] = newVertex;
            vertexList[newVertex->city_no] = newVertex;

            newVertex->mappingIdx = vertexSize;
            mappingTable[vertexSize] = newVertex->city_no;

            this->vertexSize++;
        }
    }

    void insertEdge(int _source, int _dest, int _distance) {
        vertex* source = findVertex(_source);
        vertex* dest = findVertex(_dest);

        if (source == NULL || dest == NULL) {
            return;
        }

        edge* newEdge = new edge(source, dest, _distance);

        edgeList.push_back(newEdge);
    }
};


class disjoint_set {
public:
    vertex* head;
    vertex* tail;
    int count;
    int set_id;
    long int set_total_distance;

    disjoint_set() {
        head = NULL;
        tail = NULL;

        count = 0;
        set_id = 0;
        set_total_distance = 0;
    }

    void init(vertex* v, int _set_id) {
        v->mySet = this;
        v->next = NULL;
        head = v;
        tail = v;

        set_id = _set_id;
        count++;
    }
};


// union-find, make-set�Լ� �� sort ���� ������ min, compare�Լ� ������Ÿ��
int min(int, int);
bool compare(edge*, edge*);
disjoint_set* setUnion(edge*);
disjoint_set* find(vertex*);
void makeSet(graph*);

int main() {
    int N, M, q;
    int city_no, pop_count;
    int source, dest, distance;

    int v, k;   // N ������ �̿�

    // �߰������� �̿��� ������ ����
    disjoint_set* setCursor = NULL;
    vertex* vertexCursor = NULL;
    edge* edgeCursor = NULL;
    vertex* v1 = NULL;
    vertex* v2 = NULL;
    disjoint_set* s1 = NULL;
    disjoint_set* s2 = NULL;

    int V1, V2;

    string city_name;
    string query;

    vector<edge*> R;
    vector<edge*> F;

    cin >> N >> M >> q;
    graph* G = new graph(N);


    /*
     Graph construction
     */

    for (int i = 0; i < N; i++) {
        cin >> city_no >> city_name >> pop_count;
        G->insertVertex(city_no, city_name, pop_count);
    }

    for (int i = 0; i < M; i++) {
        cin >> source >> dest >> distance;
        G->insertEdge(source, dest, distance);
    }


    //�������� ���� -> vector back, pop_back() �̿�

    R.assign(G->edgeList.begin(), G->edgeList.end());
    sort(R.begin(), R.end(), compare);

    makeSet(G);

    for (int i = 0; i < q; i++) {
        cin >> query;
        if (query == "N") {
            cin >> v >> k;
            vertexCursor = G->findVertex(v);
            setCursor = find(vertexCursor);
            vertexCursor = setCursor->head;

            for (int j = 0; j < k; j++) {
                if (vertexCursor == NULL) {
                    break;
                }
                vertexCursor = vertexCursor->next;
            }
            if (vertexCursor == NULL) {
                cout << "no exist" << endl;
            }
            else {
                cout << vertexCursor->city_no << " " << vertexCursor->city_name << endl;
            }
            vertexCursor = NULL;
            setCursor = NULL;
        }
        else if (query == "L") {
            cin >> v;
            vertexCursor = G->findVertex(v);
            setCursor = find(vertexCursor);

            cout << setCursor->count << endl;
            vertexCursor = NULL;
            setCursor = NULL;
        }
        else if (query == "I") {
            if (R.empty()) break;
            edgeCursor = R.back();
            R.pop_back();

            setCursor = setUnion(edgeCursor);

            if (setCursor == NULL) {
                cout << "not union" << endl;
                vertexCursor = NULL;
                edgeCursor = NULL;
            }
            else {
                F.push_back(edgeCursor);
                if (F.size() == N - 1 || R.empty()) {
                    cout << setCursor->set_id << " " << setCursor->count << " " << setCursor->head->city_no << " " << setCursor->set_total_distance;

                    // ������ ���� �ʱ�ȭ
                    vertexCursor = NULL;
                    edgeCursor = NULL;
                    setCursor = NULL;
                    break;
                }
                else {
                    cout << setCursor->set_id << " " << setCursor->count << " " << endl;

                    // ������ ���� �ʱ�ȭ
                    vertexCursor = NULL;
                    edgeCursor = NULL;
                    setCursor = NULL;
                }
            }
        }
        else if (query == "F") {
            cin >> V1 >> V2;
            v1 = G->findVertex(V1);
            v2 = G->findVertex(V2);
            s1 = find(v1);
            s2 = find(v2);

            if (s1 == s2) {
                cout << "True " << s1->set_id << endl;
            }
            else {
                cout << "False " << s1->set_id << " " << s2->set_id << endl;
            }
            // ������ ���� �ʱ�ȭ
            v1 = NULL;
            v2 = NULL;
            s1 = NULL;
            s2 = NULL;
        }
        else if (query == "W") {
            cin >> v;
            vertexCursor = G->findVertex(v);
            setCursor = find(vertexCursor);

            cout << setCursor->set_total_distance << endl;


            // ������ ���� �ʱ�ȭ

            vertexCursor = NULL;
            setCursor = NULL;
        }
        else if (query == "Q") {
            while (!R.empty()) {
                edgeCursor = R.back();
                R.pop_back();

                setCursor = setUnion(edgeCursor);

                if (setCursor != NULL) {
                    F.push_back(edgeCursor);    // F�� insertion
                    if (F.size() == N - 1) {
                        vertexCursor = NULL;
                        edgeCursor = NULL;
                        break;
                    }
                    else {
                        edgeCursor = NULL;  //not union
                    }
                }
            }
            cout << setCursor->set_id << " " << setCursor->set_total_distance;
            break;
        }
        if (F.size() == N - 1) {
            break;
        }
    }
    return 0;
}


// compare ������ ���� �߰�
int min(int a, int b) {
    if (a <= b) {
        return a;
    }
    else {
        return b;
    }
}

// vector pop_back �̿����� �������� ����
bool compare(edge* A, edge* B) {
    if (A->distance == B->distance) {
        if ((A->source->pop_count + A->dest->pop_count) == (B->source->pop_count + B->dest->pop_count)) {
            return min(A->source->city_no, A->dest->city_no) > min(B->source->city_no, B->dest->city_no);
        }
        else {
            return (A->source->pop_count + A->dest->pop_count) < (B->source->pop_count + B->dest->pop_count);
        }
    }
    else {
        return A->distance > B->distance;
    }
}

// parameter�� ���� vertex�� ���� disjoint set�� ����Ű�� ������ ����
disjoint_set* find(vertex* v) {
    return v->mySet;
}

// set union -> edge�� �޾� source, dest�� �����ϰ� distance�� �����ϱ�
disjoint_set* setUnion(edge* e) {
    vertex* v = e->source;
    vertex* w = e->dest;

    if (v->mySet == w->mySet) {
        return NULL;
    }

    disjoint_set* S1 = find(v);
    disjoint_set* S2 = find(w);
    int additional = 0;

    additional = e->distance;

    if (S1->count > S2->count) {
        while (S2->count != 0) {
            S1->tail->next = S2->head;
            S1->tail = S2->head;
            S1->tail->mySet = S1;

            S2->head = S1->tail->next;
            S1->tail->next = NULL;
            S1->count++;
            S2->count--;
        }
        S1->set_total_distance += S2->set_total_distance;
        S1->set_total_distance += additional;
        delete S2;
        return S1;
    }
    else if (S2->count > S1->count) {
        while (S1->count != 0) {
            S2->tail->next = S1->head;
            S2->tail = S1->head;
            S2->tail->mySet = S2;

            S1->head = S2->tail->next;
            S2->tail->next = NULL;
            S2->count++;
            S1->count--;
        }
        S2->set_total_distance += S1->set_total_distance;
        S2->set_total_distance += additional;
        delete S1;
        return S2;
    }
    else {
        if (S1->set_id >= S2->set_id) {
            while (S1->count != 0) {
                S2->tail->next = S1->head;
                S2->tail = S1->head;
                S2->tail->mySet = S2;

                S1->head = S2->tail->next;
                S2->tail->next = NULL;
                S2->count++;
                S1->count--;
            }
            S2->set_total_distance += S1->set_total_distance;
            S2->set_total_distance += additional;
            delete S1;
            return S2;
        }
        else {
            while (S2->count != 0) {
                S1->tail->next = S2->head;
                S1->tail = S2->head;
                S1->tail->mySet = S1;

                S2->head = S1->tail->next;
                S1->tail->next = NULL;
                S1->count++;
                S2->count--;
            }
            S1->set_total_distance += S2->set_total_distance;
            S1->set_total_distance += additional;
            delete S2;
            return S1;
        }
    }
    return NULL;
}

// mapping table�̿��� vertex ������ ����
void makeSet(graph* G) {
    for (unsigned int i = 0; i < G->vertexSize; i++) {
        disjoint_set* newSet = new disjoint_set();
        newSet->init(G->vertexList[G->mappingTable[i]], G->mappingTable[i]);
    }
}