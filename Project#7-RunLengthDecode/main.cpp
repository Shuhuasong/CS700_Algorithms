#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int rowCnt;
int colCnt;
//int leftEndPrint;
//int rightEndPrint;
class RunLength{
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;

    int whichMethod;
    string nameEncodeFile;
    string nameDecodeFile;

    RunLength(){
        numRows = 0; numCols = 0; minVal = 0; maxVal = 0;
    }

    RunLength(int numRows, int numCols,int minVal, int maxVal){
        this->numRows = numRows;
        this->numCols = numCols;
        this->minVal = minVal;
        this->maxVal = maxVal;
    }

    void deCodeMethod1(ifstream& inFile, ofstream& outFile){ //with zero, no wrap-around
         rowCnt = 0;
         colCnt = 0;
        while(!inFile.eof() && rowCnt < numRows){
            int startRow, startCol, color, length;
            inFile >> startRow;
            inFile >> startCol;
            inFile >> color;
            inFile >> length;
            for(int i=0; i<length; i++){
                outFile << color << " ";
                colCnt++;
                if(colCnt%numCols==0){
                    outFile << endl;
                    colCnt = 0;
                    rowCnt++;
                }
            }
        }
    }

    void deCodeMethod4(ifstream& inFile, ofstream& outFile){  // no zero and wrap-around
      rowCnt = 0;
      colCnt = 0;
      int newLength = 0;
      int startRow, startCol, color, length;
        inFile >> startRow;
        inFile >> startCol;
        inFile >> color;
        inFile >> length;
      if(startRow != 0 || startCol != 0){
            newLength = startRow*22 + startCol;
            addZero(newLength, outFile);
        }

        while(!inFile.eof() && rowCnt < numRows){
            addNonZero(length, outFile, color);
//            for(int i=0; i<length; i++){
//                outFile << color << " ";
//                colCnt++;
//               // cout << " colCnt:" << colCnt << endl;//
//                if(colCnt%numCols==0){
//                    outFile << endl;
//                    colCnt = 0;
//                    rowCnt++;
//                }
//            }
          inFile >> startRow;
          inFile >> startCol;
          inFile >> color;
          inFile >> length;

          if(rowCnt==startRow && colCnt != startCol){
              newLength = (startCol-colCnt);
              addZero(newLength, outFile);
          }
          if(rowCnt!= startRow || colCnt != startCol){
              newLength = (startRow-rowCnt-1)*22 + (22-colCnt) + startCol;
              addZero(newLength, outFile);
          }
       }
         if(rowCnt<numRows && colCnt!=21){
            newLength = (numRows-rowCnt-1)*22 + (22-colCnt);
            addZero(newLength, outFile);
         }
    }

    void addNonZero(int length, ofstream& outFile, int color){
        for(int i = 0; i<length; i++){
            outFile << color << " ";
            colCnt++;
            if(colCnt%numCols==0){
                outFile << endl;
                colCnt = 0;
                rowCnt++;
            }
        }
    }


    void addZero(int length, ofstream& outFile){
        for(int i = 0; i<length; i++){
            outFile << "0" << " ";
            colCnt++;
            if(colCnt%numCols==0){
                outFile << endl;
                colCnt = 0;
                rowCnt++;
            }
        }
    }

};


int main(int argc, char *argv[]) {

    ifstream inFile1(argv[1]);//input File:  image1_EncodeMethod1
    string nameEncodeFile = argv[1]; //image1_EncodeMethod1_Decoded
    int numRows, numCols, minVal, maxVal, whichMethod;
    inFile1 >> numRows;
    inFile1 >> numCols;
    inFile1 >> minVal;
    inFile1 >> maxVal;
    inFile1 >> whichMethod;
    string substring = nameEncodeFile.substr(0, 0+nameEncodeFile.size()-4);
    string nameDecodeFile = substring + "_Decoded" + ".txt";
    cout << nameDecodeFile;
    ofstream decodeFile(nameDecodeFile);

    RunLength *run = new RunLength(numRows, numCols, minVal,maxVal );
    decodeFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;

    if(whichMethod==1){
        run->deCodeMethod1(inFile1, decodeFile);
    }else if(whichMethod==4){
        run->deCodeMethod4(inFile1, decodeFile);
    }else{
       cout << "Error input!!!!" << endl;
       exit(1);
    }

   inFile1.close();
   decodeFile.close();

    return 0;
}


