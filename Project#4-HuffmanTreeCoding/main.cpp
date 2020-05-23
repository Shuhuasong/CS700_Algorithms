#include <iostream>
#include <string>
#include <fstream>

using namespace std;

  class HtreeNode {
  public:
      string chStr;
      int prob;
      string code;
      HtreeNode *next;
      HtreeNode *left;
      HtreeNode *right;
      HtreeNode(){
          chStr = "dummy";
          prob = 0;
          code = "";
          next = nullptr;
          left = nullptr;
          right = nullptr;
      }
//      HtreeNode(string chStr, int prob){
//          this->chStr = chStr;
//          this->prob = 0;
//          this->next = nullptr;
//      }
      HtreeNode(string chStr, int prob, string code, HtreeNode *next, HtreeNode *left, HtreeNode *right){
          this->chStr = chStr;
          this->prob = prob;
          this->code = code;
          this->left = left;
          this->right = right;
          this->next = next;
      }
      void printNode( ofstream& outFile){
          if(this->left != nullptr || this->right != nullptr){
              outFile << "(" << this->chStr << "," << this->prob  << "," << this->code  << "," << "NULL" //there is next in the Tree
                      << "," << this->left->chStr  << "," << this->right->chStr  << "," << ")->";

          }
      }
  };

  class linkedList {
  public:
      HtreeNode *listHead;
      linkedList(){
          listHead = new HtreeNode(); }

      void listInsert( HtreeNode *listHead, HtreeNode *newNode){
          HtreeNode *spot = findSpot(listHead,newNode);
          newNode->next = spot->next;
          spot->next = newNode;
      }

      HtreeNode *findSpot(HtreeNode *listHead, HtreeNode *newNode){
          HtreeNode *spot = listHead;
          while(spot->next != nullptr && spot->next->prob <= newNode->prob){
              spot = spot->next;
          }
          return spot;
      }

      void printList(HtreeNode *listHead, ofstream& outFile){
          outFile << "listHead-> " ;
          HtreeNode *cur = listHead;

          while(cur != nullptr && cur->next != nullptr) {
              outFile << "(" << cur->chStr << "," << cur->prob  << "," << cur->code  << "," << cur->next->chStr
                      << "," << "NULL"  << "," << "NULL)->";
              cur = cur->next;
          }
          outFile << "(" << cur->chStr << "," << cur->prob  << "," << cur->code  << "," << "NULL"
                  << "," << "NULL" << "," << "NULL)->";
          outFile << "NULL\n";
      }
  };

  class HuffmanBinaryTree {
  public:

      HtreeNode *root;
      //linkedList *list;
      HtreeNode *listHead;
      HuffmanBinaryTree(){
          root = new HtreeNode();
          //list = new linkedList();
      }

      HtreeNode *constructHuffmanLList(ifstream& inFile, ofstream& outFile){
        linkedList *list = new linkedList();
        //HtreeNode *listHead = new HtreeNode();
        //listHead = list->listHead;
        if(inFile.is_open()){
            while(!inFile.eof()){
                string chr;
                int prob = 0;
                inFile >> chr;
                inFile >> prob;
                if(inFile.eof()) break;
                HtreeNode *newNode = new HtreeNode(chr, prob,"" ,nullptr, nullptr, nullptr);
                list->listInsert(list->listHead,newNode);
                list->printList(list->listHead, outFile) ;
            }
         }
        return list->listHead;
      }

      HtreeNode *constructHuffmanBinTree(HtreeNode *listHead, ofstream& outFile){
        linkedList *list = new linkedList();
        //cout<<list->listHead->chStr<<endl;
        //HtreeNode *listHead = list->listHead;
        while(listHead->next != nullptr && listHead->next->next != nullptr){

            HtreeNode *newNode = new HtreeNode();
            newNode->prob = listHead->next->prob + listHead->next->next->prob;
            newNode->chStr = listHead->next->chStr + listHead->next->next->chStr;
            newNode->left = listHead->next;
            newNode->right = listHead->next->next;
            newNode->next = nullptr;
            listHead->next = listHead->next->next->next;
            list->listInsert( listHead, newNode);

            list->printList(listHead, outFile);
        }
        //root = list->listHead->next;
        return listHead->next;
      }

      void preOrderTraversal(HtreeNode *root, ofstream& outFile){
        if(isLeaf(root)){
           //outFile << root->chStr;
           return;
        }else{
            root->printNode(outFile);
            preOrderTraversal(root->left, outFile);
            preOrderTraversal(root->right, outFile);
        }
      }


      void inOrderTraversal(HtreeNode *root, ofstream& outFile){
        if(root==nullptr) return;
        if(isLeaf(root)){
            return;
        }else{
            preOrderTraversal(root->left, outFile);
            root->printNode(outFile);
            preOrderTraversal(root->right, outFile);
        }
      }
      void postOrderTraversal(HtreeNode *root, ofstream& outFile){
        if(root==nullptr) return;
        if(isLeaf(root)){
            return;
        }else{
            preOrderTraversal(root->left, outFile);
            preOrderTraversal(root->right, outFile);
            root->printNode(outFile);
        }
      }

      void constructCharCode(HtreeNode *root, string code, ofstream& outFile){

          if(isLeaf(root)){
              root->code = code;
              outFile << root->chStr << " " << root->code << endl;
              cout << root->chStr << " " << root->code << endl;
          }else{
              root->code = code;
              constructCharCode(root->left, root->code+ "0", outFile);
              constructCharCode(root->right, root->code+ "1", outFile);
          }
      }

      bool isLeaf(HtreeNode *root){
          if(root->left==nullptr && root->right==nullptr)
              return true;
          return false;
      }

  };

  int main(int argc, char *argv[]){
      ifstream inFile(argv[1]);
      ofstream outFile1(argv[2]); //contain Huffman <char, code> pairs
      ofstream outFile2(argv[3]); //
      ofstream outFile3(argv[4]);
      HuffmanBinaryTree  *tree = new HuffmanBinaryTree();
      linkedList *list = new linkedList();

       list->listHead = tree->constructHuffmanLList(inFile,outFile3);
       list->printList(list->listHead,outFile2);
       tree->root = tree->constructHuffmanBinTree(list->listHead, outFile3);
       outFile2 << "PreOrder: " ;
      tree->preOrderTraversal(tree->root, outFile2);
      outFile2 << "\ninOrder: " ;
      tree->inOrderTraversal(tree->root, outFile2);
      outFile2 << "\npostOrder: " ;
      tree->postOrderTraversal(tree->root, outFile2);
      //outFile2 << "\npostOrder: " ;
      tree->constructCharCode(tree->root, "", outFile1);

      inFile.close();
      outFile1.close();
      outFile2.close();
      outFile3.close();

      return 0;
  }


