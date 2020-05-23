//
//  main.cpp
//  700AlgorithmProject1
//
//  Created by Shuhua Song on 2/3/20.
//  Copyright © 2020 Shuhua Song. All rights reserved.
//
#include <iostream>
#include<string>
#include<fstream>
using namespace std;

class listNode{
public:
    int data;
    listNode* next;
    listNode(){
        data = -9999;
        next = nullptr;
    }
    listNode(int data, listNode* next){
        this->data = data;
        this->next = next;
    }
    void printNode(listNode* node, ofstream& outFile){
        //        if(node==nullptr){
        //            outFile << "(" << "NULL" << "," << node << ")->" << endl;
        //        }
        
            outFile << "(" << node->data << ", " << node
            << ", "<< node->next  <<", " << node->next->data << ")" << endl;
    }
};

class LinkedList{
public:
    listNode *listHead;
    
    LinkedList(){
        //creat a dummy node for the linkedlist
        listNode *dummy = new listNode();
        listHead = dummy;
    }
    
    //construct a linkedlist
    void constructLL(ifstream& inFile, ofstream&  outFile){
        
        if(inFile.is_open())
        {
            while(!inFile.eof()){
                int newData;
                inFile >> newData;
                if(inFile.eof()) break;
                listNode *newNode = new listNode(newData, nullptr);
                listInsert(newNode);
                printList(outFile);
            }
        }
        else{
            cout << "Can not open the file" ;
        }
    }
    //Insert a node after the node of spot
    void listInsert(listNode* newNode){
        listNode *spot = findSpot(newNode);
        newNode->next = spot->next;
        spot->next = newNode;
    }
    
    //Find a spot that this new node can be inserted after that
    listNode* findSpot(listNode* newNode){
        listNode *curNode = listHead;
        while(curNode->next != nullptr){
            if(curNode->next->data > newNode->data) break;
            curNode = curNode->next;
        }
        return curNode;
    }
    
    void printList(ofstream& outFile){
        listNode *curNode = new listNode();
        curNode = listHead;
       
        outFile << "listHead->";
        while(curNode->next != nullptr){
            outFile << "(" << curNode->data << "," << curNode << "," <<
            curNode->next << "," << curNode->next->data << ")->" ;
            curNode = curNode->next;
        }
        outFile <<"(" << curNode->data <<"," << "NULL" << ")->";
        outFile << "NULL" << endl;
    }
    
    //using fast-slow strategy to find the middle node of linkedlist
    listNode* findMiddleNode(ofstream& outFile){
        listNode* walk1 = listHead;
        listNode* walk2 = listHead;
        listNode* node = new listNode();
        while(walk2 != nullptr && walk2->next != nullptr ){
            node->printNode(walk1,outFile);
            walk1 = walk1->next;
            walk2 = walk2->next->next;
        }
        return walk1;
    }
};


int main(int argc, const char *argv[]){
    //open and read data from external input file
    ifstream inFile (argv[1]);
    //write the data to output file
    ofstream outFile1 (argv[2]);
    ofstream outFile2 (argv[3]);
    
    LinkedList list;
    
    list.constructLL(inFile, outFile2);
   
    outFile1 << "The Completed Sorted Linked list" << endl;
    list.printList(outFile1);
    listNode* node = new listNode();
    listNode* midNode = list.findMiddleNode(outFile2);
    outFile1 << "Middle Node: "<< endl;
    node->printNode(midNode,outFile1);
    inFile.close();
    outFile1.close();
    outFile2.close();
    return 0;
}
