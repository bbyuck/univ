#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
#include <cstdlib>

using namespace std;

// search 마지막에 찾은 key기준 left로 insert 할지 right로 insert할지 결정
#define INITIAL 0
#define LEFT 1
#define RIGHT 2
#define RIGHT_END 3

#define EXIST 4
#define CREATED 5

class node;
class BPTree;

class node {
  public:
    int BID;
    vector<int> entries;
    int entryCount;
    int depth;
    int totalEntrySize;

    node(int blockSize) {
      BID = 0;
      entryCount = 0;
      depth = 0;
      totalEntrySize = (blockSize - 4) / 8;
      entries.assign(2 * totalEntrySize + 1, 0);
    }
};



class BPTree {
  public:
    int blockSize;
    int rootBID;
    int depth;
    int nextBID;
    int totalEntrySize;

    int insertionStatus;
    int insertionDirection;

    char* indexFileName;
    node* root;
    vector<node*> nodeBuffer;
    vector<node*> commitBuffer; // 업데이트 후 실제 index file에 write연산을 수행하기 위해 node를 저장해두는 buffer


    fstream indexFile;
    fstream outputFile;
    fstream inputFile;

    BPTree(char* _indexFileName) {
      indexFileName = _indexFileName;
      read_header();
      // load_root();
      update_next_bid();
      insertionStatus = EXIST;
      insertionDirection = INITIAL;
      totalEntrySize = 0;
    }

    void commit() {
      indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
      while(!commitBuffer.empty()) {
        node* updateNode = commitBuffer.back();
        commitBuffer.pop_back();
        indexFile.seekp(fileOffset(updateNode->BID), ios::beg);
        for (int i = 0; i < 2 * totalEntrySize + 1; i++)
        {
          indexFile.write((char *)&updateNode->entries[i], sizeof(int));
        }
      }
      indexFile.close();
    }

    void update_header() {
      indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
      // root update
      indexFile.seekp(4, ios::beg);
      indexFile.write((char*)&rootBID, sizeof(int));
      indexFile.seekp(8, ios::beg);
      indexFile.write((char*)&depth, sizeof(int));
      indexFile.close();
    }

    int fileOffset(int BID)
    {
      return 12 + ((BID - 1) * blockSize);
    }

    bool empty() {
      return depth == 0;
    }

    void read_header() {
      indexFile.open(indexFileName, ios::in | ios::binary);
      indexFile.seekg(0, ios::beg);
      indexFile.read((char *)&blockSize, sizeof(int));
      indexFile.read((char *)&rootBID, sizeof(int));
      indexFile.read((char *)&depth, sizeof(int));
      totalEntrySize = (blockSize - 4) / 8;
      indexFile.close();
    }

    void load_root() {
      read_header();
      root = load_node(rootBID);
    }

    node* load_node(int BID) {
      node* loadedNode = new node(blockSize);
      

      indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
      indexFile.seekg(fileOffset(BID), ios::beg);
      

      // 다음 level에 있는 node entries inmemory로 load
      for (int i = 0; i < 2 * totalEntrySize + 1; i++)
      {
        indexFile.read((char *)&loadedNode->entries[i], sizeof(int));
        // cout << loadedNode->entries[i] << " ";  //debug
        if (loadedNode->entries[i] != 0)
        {
          loadedNode->entryCount++;
        }
      }
      loadedNode->entryCount /= 2;
      // cout << endl; // debug
      loadedNode->BID = BID;
      indexFile.close();

      return loadedNode;
    }

    void leaf_node_split(node* leafNode){
      // cout << "leaf node split 발생" << endl; //debug
      // cout << leafNode->BID << endl;
      node* newLeafNode = new node(blockSize);
      node* parentNode;
      parentNode = nodeBuffer.back();

      update_next_bid();
      newLeafNode->BID = nextBID++;
      newLeafNode->depth = leafNode->depth;
      int newIdx = 0;
      int originalIdx;

      // 홀수 차수
      if(totalEntrySize % 2 == 1) {
        originalIdx = totalEntrySize - 1;
      } else {
        // 짝수 차수
        originalIdx = totalEntrySize;
      }
      // entry split
      while(originalIdx < 2 * totalEntrySize) {
        newLeafNode->entries[newIdx] = leafNode->entries[originalIdx];
        leafNode->entries[originalIdx] = 0;
        if (newIdx % 2 == 0) {
          leafNode->entryCount--;
          newLeafNode->entryCount++;
        }
        newIdx++;
        originalIdx++;
      }

      int parentNewEntryIdx = 0;
      // parent node 업데이트
      for (int i = 0; i < 2 * parentNode->entryCount + 1; i++) {
        // key 일경우
        if(i % 2 == 1) {
          if(parentNode->entries[i] >= newLeafNode->entries[0]) {
            parentNewEntryIdx = i;
            break;
          }
        }
      }
      parentNode->entryCount++;

      if (parentNewEntryIdx == 0)
      {
        parentNewEntryIdx = 2 * parentNode->entryCount - 1;
      }

      for(int i =  2 * parentNode->entryCount; i >= parentNewEntryIdx + 2; i--) {
        parentNode->entries[i] = parentNode->entries[i - 2];
      }
      parentNode->entries[parentNewEntryIdx] = newLeafNode->entries[0];
      parentNode->entries[parentNewEntryIdx + 1] = newLeafNode->BID;
      
      // split된 leaf node간 ptr 업데이트
      newLeafNode->entries[2 * totalEntrySize] = leafNode->entries[2 * totalEntrySize];
      leafNode->entries[2 * totalEntrySize] = newLeafNode->BID;
      

      // write는 모든 root까지의 모든 split 과정을 수행한 후 순차적으로 write 수행 -> block I/O 횟수 최소화

      // parent node와 leaf node 모두 index file에 write
      indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
      
      // parent node write
      indexFile.seekp(fileOffset(parentNode->BID), ios::beg);
      for(int i = 0; i < 2 * totalEntrySize + 1; i++) {
        indexFile.write((char*)&parentNode->entries[i], sizeof(int));
      }

      // new leaf node write
      indexFile.seekp(fileOffset(newLeafNode->BID), ios::beg);
      for (int i = 0; i < 2 * totalEntrySize + 1; i++) {
        indexFile.write((char *)&newLeafNode->entries[i], sizeof(int));
      }

      // leaf node write
      indexFile.seekp(fileOffset(leafNode->BID), ios::beg);
      for (int i = 0; i < 2 * totalEntrySize + 1; i++) {
        indexFile.write((char *)&leafNode->entries[i], sizeof(int));
      }
      indexFile.close();

      // 다음 단계로 split이 propagation 되는지 체크하기 위해 parent node return
    }

    void non_leaf_node_split(node* nonLeafNode){
      // cout << "non leaf node split 발생" << endl;
      int originalIdx;
      int newIdx = 0;
      int parentKey;
      node *newNode = new node(blockSize);  // sibling
      node *parentNode;
      if(!nodeBuffer.empty()) {
        parentNode = nodeBuffer.back();
      } else {
        parentNode = new node(blockSize);
      }
      

      // 짝수 차수
      if (totalEntrySize % 2 == 0) {
        originalIdx = totalEntrySize + 1;
      } else {
      // 홀수 차수
        originalIdx = totalEntrySize;
      }

      // parent로 보낼 key
      parentKey = nonLeafNode->entries[originalIdx]; 
      nonLeafNode->entries[originalIdx++] = 0;
      while(originalIdx < 2 * totalEntrySize + 1) {
        newNode->entries[newIdx] = nonLeafNode->entries[originalIdx];
        nonLeafNode->entries[originalIdx] = 0;
        if (newIdx % 2 == 1)
        {
          nonLeafNode->entryCount--;
          newNode->entryCount++;
        }
        originalIdx++;
        newIdx++;
      }
      update_next_bid();
      newNode->BID = nextBID;
      newNode->depth = nonLeafNode->depth;
      
      // new node는 바로 write해야 됨
      indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
      indexFile.seekp(fileOffset(newNode->BID), ios::beg);

      for(int i = 0; i < 2 * totalEntrySize + 1; i++) {
        indexFile.write((char*)&newNode->entries[i], sizeof(int));
      }
      indexFile.close();

      // newNode, non leaf node update 완료

      commitBuffer.push_back(nonLeafNode);
      // nodeBuffer가 아직 남아있다면 propagation 단순 업데이트만
      if(!nodeBuffer.empty()) {
        int parentKeyIdx = 0;
        parentNode->entryCount++;
        for(int i = 0; i < 2 * parentNode->entryCount + 1; i++) {
          if(i % 2 == 1) {
            //key값
            if(parentNode->entries[i] >= parentKey) {
              parentKeyIdx = i;
              break;
            }
          }
        }
        if(parentKeyIdx == 0) {
          parentKeyIdx = 2 * parentNode->entryCount - 1;
        }

        for(int i = 2 * parentNode->entryCount; i >= parentKeyIdx; i--) {
          parentNode->entries[i] = parentNode->entries[i - 2];
        }
        parentNode->entries[parentKeyIdx] = parentKey;
        parentNode->entries[parentKeyIdx + 1] = newNode->BID;
        commitBuffer.push_back(parentNode);
      } else {
        // 스플릿된 노드는 root가 됨
        update_next_bid();
        parentNode->BID = nextBID;
        parentNode->depth = 0;
        parentNode->entryCount++;
        parentNode->entries[0] = nonLeafNode->BID;
        parentNode->entries[1] = parentKey;
        parentNode->entries[2] = newNode->BID;
        read_header();
        rootBID = parentNode->BID;
        depth++;
        update_header();
        commitBuffer.push_back(parentNode);
      }
    }


    void insert(int key, int value){
      // 첫 insert
      if (nextBID == 1) {
        indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
        int init_root = 0;

        indexFile.seekp(12, ios::beg);
        for(int i = 0; i < blockSize / 4; i++) {
          indexFile.write((char *)&init_root, sizeof(int));
        }
        indexFile.close();

        load_root();
        indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
        indexFile.seekp(fileOffset(rootBID), ios::beg);
        // node 삽입
        root->entries[++root->entryCount] = key;
        root->entries[root->entryCount + 1] = ++nextBID;
        for (int i = 0; i < 2 * totalEntrySize + 1; i++) {
          indexFile.write((char*)&root->entries[i], sizeof(int));
        }
        indexFile.close();

        update_next_bid();
        indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
        indexFile.seekp(fileOffset(nextBID), ios::beg);
        node* newRecord = new node(blockSize);
        newRecord->BID = nextBID;
        newRecord->depth = 1;
        newRecord->entries[0] = key;
        newRecord->entries[1] = value;
        //record 삽입
        indexFile.seekp(fileOffset(newRecord->BID), ios::beg);
        for(int i = 0; i < 2 * totalEntrySize + 1; i++) {
          indexFile.write((char*)&newRecord->entries[i], sizeof(int));
        }
        
        indexFile.close();
        return;
      }

      // targetBID를 search
      int targetBID = search(key);

      // cout << "입력 Key : " << key << endl; // debug

      // TODO LIST
      // 1   새로 생성된 리프노드 -> 부모 노드 ptr 업데이트, 리프노드 업데이트 -> insert시 
      // 1-1 리프노드 업데이트시 왼쪽에 새로 생겼다면   -> 부모노드의 다음 엔트리로 가서 리프노드 BID를 가져온 후 현재 리프노드 포인터 업데이트
      // 2   이미 존재하는 리프노드 
      // 2-1 일단 record insert
      // 2-2 full 여부 체크
      // 2-3 full이 아니라면 return
      // 2-4 full 이라면 split 수행
      // 3   스플릿을 root 노드까지 검사

      // 1. 새로 생성된 리프노드 -> 부모 노드 ptr 업데이트, 리프노드 업데이트

      node *targetLeafNode = nodeBuffer.back();
      nodeBuffer.pop_back();
      if (insertionStatus == CREATED) {
        indexFile.open(indexFileName, ios::in | ios::out | ios::binary);

        targetLeafNode->entries[0] = key;
        targetLeafNode->entries[1] = value;

        node *targetParentNode = nodeBuffer.back();

        // 1-1 리프노드 업데이트시 왼쪽에 새로 생겼다면   -> 부모노드 ptr 업데이트
        // 다음 엔트리로 가서 리프노드 BID를 가져온 후 현재 리프노드 포인터 업데이트
        int nextLeafBID = targetParentNode->entries[2];
        targetLeafNode->entries[2 * totalEntrySize] = nextLeafBID;
          
        // parent update
        targetParentNode->entries[0] = targetLeafNode->BID;
        indexFile.seekp(fileOffset(targetParentNode->BID), ios::beg);
        for (int i = 0; i < 2 * totalEntrySize + 1; i++)
        {
          indexFile.write((char *)&targetParentNode->entries[i], sizeof(int));
        }

        // leaf update
        indexFile.seekp(fileOffset(targetLeafNode->BID), ios::beg);
        for (int i = 0; i < 2 * totalEntrySize + 1; i++)
        {
          indexFile.write((char *)&targetLeafNode->entries[i], sizeof(int));
        }
        indexFile.close();
      } 
      else if(insertionStatus == EXIST)
      { 
        // 2. 이미 존재하는 리프노드 -> 일단 오름차순으로 record insert
        indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
        targetLeafNode->entryCount++;

        int sortingIdx = 2 * targetLeafNode->entryCount - 2;

        // key값따라 record가 insert 될 위치를 찾는다
        for (int i = 0; i < 2 * targetLeafNode->entryCount; i++) {
          if(i % 2 == 0) {
            if(targetLeafNode->entries[i] >= key) {
              sortingIdx = i;
              break;
            }
          }
        }
        // insert될 위치를 찾으면 그 위치로부터 우측으로 shift
        for (int i = 2 * targetLeafNode->entryCount - 1; i > sortingIdx; i--) {
          targetLeafNode->entries[i] = targetLeafNode->entries[i - 2];
        }
        // record insert
        targetLeafNode->entries[sortingIdx] = key;
        targetLeafNode->entries[sortingIdx + 1] = value;


        // cout << "현재 리프노드 BID : " << targetLeafNode->BID << endl;
        // 2-2, 2-3 full이 아니라면 return       
        if (targetLeafNode->entryCount < totalEntrySize) {
          indexFile.seekp(fileOffset(targetLeafNode->BID), ios::beg);
          for (int i = 0; i < 2 * totalEntrySize + 1; i++)
          {
            indexFile.write((char *)&targetLeafNode->entries[i], sizeof(int));
          }
          indexFile.close();
          return;
        }
        indexFile.close();
        // 2-4. full이라면 split 수행
        if (targetLeafNode->entryCount == totalEntrySize)
        {
          leaf_node_split(targetLeafNode);
        }
        // 2-5. root까지 split이 발생하는지 buffer stack을 pop하면서 검사
        while(!nodeBuffer.empty()){
          node* nonLeafNode = nodeBuffer.back();
          nodeBuffer.pop_back();
          // cout << "non leaf node entryCount : " << nonLeafNode->entryCount << endl;
          // split 할 필요없으면 검사 종료
          if(nonLeafNode->entryCount < totalEntrySize) {
            break;
          }
          non_leaf_node_split(nonLeafNode);
        }

        commit();
      }
    }
    void update_next_bid() {
      indexFile.open(indexFileName, ios::in | ios::out | ios::binary);
      indexFile.seekg(0, ios::end);
      nextBID = indexFile.tellg();
      nextBID = ((nextBID - 12) / blockSize) + 1;
      indexFile.close();
    }

    //BID return;
    int search(int key) {
      // search연산 실행시 다음 BID(file의 끝 offset) update
      update_next_bid();
      // root node load
      load_root();
      // nodeBuffer 클리어
      nodeBuffer.clear();

      node* searched = tree_search(key, root);
      if(searched == NULL) {
        return 0;
      }

      return searched->BID;
    }

    node* tree_search(int key, node* b){
      //if node is a leaf
      nodeBuffer.push_back(b);
      if(b->depth == depth) {
        return b;
      }
      // inmemory로 load한 현재 entry 탐색
      for(int i = 0; i < 2 * b->entryCount + 1; i++) {
        // i % 2 == 1 -> key || i % 2 == 0 -> ptr
        if(i % 2 == 1) {
          if(key < b->entries[i]) {
            //현재 탐색중인 entry의 왼쪽
            node *intermediateNode;
            if (b->entries[i - 1] == 0) {
              intermediateNode = load_node(nextBID);
              insertionStatus = CREATED;
            } 
            else {
              intermediateNode = load_node(b->entries[i - 1]);
              insertionStatus = EXIST;
            }
            intermediateNode->depth = b->depth + 1;
          
            insertionDirection = LEFT;
            return tree_search(key, intermediateNode);
          }
          else if (b->entries[i] <= key && key < b->entries[i + 2])
          {
            //현재 탐색중인 entry의 오른쪽
            node* intermediateNode;
            if (b->entries[i + 1] == 0) {
              intermediateNode = load_node(nextBID);
              insertionStatus = CREATED;
            }
            else {
              intermediateNode = load_node(b->entries[i + 1]);
              insertionStatus = EXIST;
            }
            intermediateNode->depth = b->depth + 1;

            insertionDirection = RIGHT;
            return tree_search(key, intermediateNode);
          }
          else if (b->entries[(2 * b->entryCount) - 1] <= key)
          {
            // entry 끝의 오른쪽
            node *intermediateNode; 

            if (b->entries[2 * b->entryCount] == 0)
            {
              intermediateNode = load_node(nextBID);
              insertionStatus = CREATED;
            }
            else {
              intermediateNode = load_node(b->entries[2 * b->entryCount]);
              insertionStatus = EXIST;
            }

            intermediateNode->depth = b->depth + 1;
            intermediateNode->BID = b->entries[2 * b->entryCount];
            indexFile.close();

            insertionDirection = RIGHT_END;
            return tree_search(key, intermediateNode);
          }
        }
      }
      return NULL;
    }
};

int main(int argc, char *argv[])
{
  char command = argv[1][0];

  char buf[100];

  switch (command)
  {
  case 'c':
  {
    char *outputFile = argv[2];
    ofstream out;
    out.open(outputFile, ios::out | ios::binary | ios::trunc);

    int init = 1;
    // int init_root = 0;
    int input_block_size = atoi(argv[3]);

    out.write((char *)&input_block_size, sizeof(int)); // 블록사이즈 header에 write
    out.write((char *)&init, sizeof(int));             // 루트 노드초기화
    out.write((char *)&init, sizeof(int));             // depth 초기화

    out.close();
    break;
  }
  case 'i':
  {
    char *indexFileName = argv[2];
    char *inputFileName = argv[3];
    fstream insertion;

    BPTree* indexInterface = new BPTree(indexFileName);

    insertion.open(inputFileName, ios::in | ios::out | ios::binary);
    insertion.seekg(0, ios::end);
    int insertion_size = insertion.tellg();
    insertion.seekg(0, ios::beg);
    char *tok;
    int key;
    int val;

    while (insertion.peek() != EOF) {
    	insertion.getline(buf, insertion_size);

    	tok = strtok(buf, ",");
    	key = atoi(tok);
    	tok = strtok(NULL, "\n");
    	val = atoi(tok);

      indexInterface->insert(key, val);
    }
    insertion.close();

    break;
  }
  case 's':
  {
    char *indexFileName = argv[2];
    char *inputFileName = argv[3];
    char *outputFileName = argv[4];
    fstream in;
    fstream out;
    BPTree *indexInterface = new BPTree(indexFileName);

    out.open(outputFileName, ios::out | ios::binary | ios::trunc);
    out.seekp(0, ios::beg);
    in.open(inputFileName, ios::in | ios::out | ios::binary);
    in.seekg(0, ios::end);
    int in_size = in.tellg();
    in.seekg(0, ios::beg);
    char *tok;
    int input_key;
    int output_key, output_val;

    while (in.peek() != EOF)
    {
      in.getline(buf, in_size);
      tok = strtok(buf, "\n");
      input_key = atoi(tok);
      node* searchedNode = indexInterface->load_node(indexInterface->search(input_key));
      for (int i = 0; i < 2 * searchedNode->entryCount; i++) {
        if(input_key == searchedNode->entries[i]) {
          output_key = input_key;
          output_val = searchedNode->entries[i + 1];
          break;
        }
      }
      out << output_key << "," << output_val << "\n";
    }
    out.close();
    in.close();
    break;
  }
  case 'r':
  {
    char *indexFileName = argv[2];
    char *inputFileName = argv[3];
    char *outputFileName = argv[4];
    fstream in;
    fstream out;
    BPTree *indexInterface = new BPTree(indexFileName);

    out.open(outputFileName, ios::out | ios::binary | ios::trunc);
    out.seekp(0, ios::beg);
    in.open(inputFileName, ios::in | ios::out | ios::binary);
    in.seekg(0, ios::end);
    int in_size = in.tellg();
    in.seekg(0, ios::beg);
    char *tok;
    int range_start, range_end;
    int key, val;

    while (in.peek() != EOF)
    {
      in.getline(buf, in_size);

      tok = strtok(buf, ",");
      range_start = atoi(tok);
      tok = strtok(NULL, "\n");
      range_end = atoi(tok);
      // cout << range_start << "," << range_end << endl;

      node *nodePtr = indexInterface->load_node(indexInterface->search(range_start));
      int i = 0;
      while (1) {
        if (i % 2 == 0 && nodePtr->entries[i] > range_end){
          break;
        }
        if(i > 2 * nodePtr->entryCount - 2) {
          nodePtr = indexInterface->load_node(nodePtr->entries[2 * indexInterface->totalEntrySize]);
          i = 0;
        }
        if(i % 2 == 0 && nodePtr->entries[i] >= range_start && nodePtr->entries[i] <= range_end) {
          out << nodePtr->entries[i] << "," << nodePtr->entries[i + 1] << "\t";
        }
        i++;
      }
      out << "\n";
    }
    out.close();
    in.close();
    break;
  }
    
  case 'p':
  {
    char *indexFileName = argv[2];
    char *outputFileName = argv[3];
    fstream out;
    BPTree *indexInterface = new BPTree(indexFileName);
    indexInterface->load_root();
    node *root = indexInterface->root;
    out.open(outputFileName, ios::out | ios::binary | ios::trunc);
    out.seekp(0, ios::beg);

    // 레벨 1, 2가 모두 non leaf node 일 때

    out << "<0>\n";
    for (int i = 1; i < 2 * root->entryCount; i++) {
      if(i % 2 == 1) {
        out << root->entries[i] << ", ";
      }
    }
    out.seekp(-2, ios::end);
    out << " ";
    out.seekp(-1, ios::end);
    out << "\n<1>\n";

    node* nodePtr;

    for (int i = 0; i < 2 * root->entryCount + 1; i++) {
      if(i % 2 == 0) {
        nodePtr = indexInterface->load_node(root->entries[i]);
        if (nodePtr->depth == indexInterface->depth){
          // non leaf node
          for (int j = 1; j < 2 * nodePtr->entryCount; j++)
          {
            if (j % 2 == 1)
            {
              out << nodePtr->entries[j] << ", ";
            }
          }
        } else if(nodePtr->depth < indexInterface->depth) {
          // leaf node
          for (int j = 0; j < 2 * nodePtr->entryCount; j++)
          {
            if (j % 2 == 0)
            {
              out << nodePtr->entries[j] << ", ";
            }
          }
        }
      } 
    }
    out.seekp(-2, ios::end);
    out << " ";
    out.seekp(-1, ios::end);

    out.close();

    break;
  }
  default:
    break;
  }

  return 0;
}