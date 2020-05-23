#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class listNode {
public:
    string data;
    int count;
    listNode *next;

    listNode() {
        data = "dummy";
        count = 0;
        next = nullptr;
    }

    listNode(string data, int count, listNode *next) {
        this->data = data;
        this->count = count;
        this->next = next;
    }

    void printNode(ofstream &outFile) {
        outFile << "->(" << this->data << ", " << this->count << ", " << this->next->data << ")";
    }
};

class HashTable {
private:
    int bucketSize;
    listNode **hashTableAry;

public:

    HashTable() {
        bucketSize = 29;
        hashTableAry = new listNode *[bucketSize];
        //hashTableAry = new listNode*[bucketSize];
        for (int i = 0; i < bucketSize; i++) {
            hashTableAry[i] = new listNode();
        }
    }

    void storeDataIntoHashTable(ifstream &inFile, ofstream &outFile) {
        if (inFile.is_open()) {
            while (!inFile.eof()) {
                string newData;
                inFile >> newData;
                if (inFile.eof()) break;
                int index = Doit(newData);
                listNode *listHead = hashTableAry[index];
                listNode *newNode = new listNode(newData, 1, nullptr); //count: ???

                listInsert(listHead, newNode);

                printList(index, outFile);
            }
        }
    }

   
    int Doit(string data) {
        unsigned int val = 1;
        for (int i = 0; i < data.length(); i++) {
            val = val * 32 + (int) data[i];
        }
        int index = val % 29;
        return index;
    }

    void listInsert(listNode *listHead, listNode *newNode) {//this already include the case of listHead->
        listNode *spot = findSpot(newNode, listHead);
        if (spot != nullptr) {
            newNode->next = spot->next;
            spot->next = newNode;
        }
    }

    listNode *findSpot(listNode *newNode, listNode *listHead) {
        listNode *Spot = listHead;
        while (Spot->next != nullptr && Spot->next->data.compare(newNode->data) < 0) {//need to check if Spot->next is nullptr
            Spot = Spot->next;
        }
        if (Spot->next != nullptr && Spot->next->data.compare(newNode->data) == 0) {
            Spot->next->count++;
            return nullptr;
        }
        return Spot;
    }

    void printHashTable(ofstream &outFile) {
        int index = 0;
        while (index < bucketSize) {
            printList(index, outFile);
            index++;
        }
    }

    void printList(int index, ofstream &outFile) {
        outFile << "hashTable[" << index << "]" ;
        listNode *printSpot = hashTableAry[index];
        while (printSpot->next != nullptr) { //remember the dummy node is null, so we can't add printSpot!=null
            printSpot->printNode(outFile); //
            printSpot = printSpot->next;
        }
        outFile << "->(" << printSpot->data << ", " << printSpot->count << ", " << "NUll" << ")";
        outFile << "->NULL\n";
    }

    /*  ~HashTable(){
            delete[] hashTableAry;
        }
        */
};


int main(int argc, char *argv[]) {
    ifstream inFile(argv[1]);
    ofstream outFile1(argv[2]);
    ofstream outFile2(argv[3]);

    HashTable *myHashTable = new HashTable();
    outFile2 << "Debug the HashTable: " << endl;

    myHashTable->storeDataIntoHashTable(inFile, outFile2);
//    outFile1 << "The Completed HashTable: " << endl;
    myHashTable->printHashTable(outFile1);


    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}
