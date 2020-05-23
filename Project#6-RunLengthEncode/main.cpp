#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int rowS;
int colS;
int zeroCnt;
class RunLength {
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;

    RunLength(){
        numRows = 0;
        numCols = 0;
        minVal = 0;
        maxVal = 0;
    }

    RunLength(int numRows, int numCols, int minVals, int maxVal){
        this->numRows = numRows;
        this->numCols = numCols;
        this->minVal = minVals;
        this->maxVal = maxVal;
    }
    int whichMethod(int numMethod){
     return numMethod;
    }

    string nameEncodeFile(string name,int numMethod){
     string substring = name.substr(0, 0 + name.size()-4);
     string res = substring +  "_EncodeMethod" +  to_string(numMethod) + ".txt";
     return res;
    }

    void encodeMethod1(ifstream& inFile, ofstream& encodeFile){
        int row = 0;
        while(row < numRows){
            int col = 0;
            int length = 1;
            int curVal;
            inFile >> curVal;
            encodeFile << row << " " << col <<  " " << curVal << " ";
                while(col < numCols){
                    col = col + 1;
                    if(col < numCols){
                        int nextVal;
                        inFile >> nextVal;
                        if(nextVal == curVal){
                            length++;
                        }else{
                            encodeFile << length << endl;
                            curVal = nextVal;
                            length = 1;
                            encodeFile << row << " " << col <<  " " << curVal << " ";
                        }
                    }
                }
            row = row + 1;
            encodeFile << length << endl;
        }
    }
   void encodeMethod4(ifstream& inFile, ofstream& encodeFile){
       rowS = 0;
       colS = 0;
       int length = 0;
       int nextVal;
       inFile >> nextVal;
       while(!inFile.eof()){
           int lastVal = skipZeros(inFile, nextVal, zeroCnt);
           encodeFile << rowS << " " << colS << " " << lastVal << " ";
           length++;
           inFile >> nextVal;
           while(nextVal == lastVal){
               length++;
               colS++;
               if(colS >= numCols){
                   colS = 0;
                   rowS++;
               }
               inFile >> nextVal;
           }
           encodeFile << length << endl;
           length = 0;
           colS++;
           if(colS >= numCols){
               colS = 0;
               rowS++;
           }
           lastVal = nextVal;

       }
       encodeFile << length << endl;
    }

    int skipZeros(ifstream& inFile, int pixelVal,int zeroCnt) {
        while (pixelVal == 0) {
            colS++;
            if (colS >= numCols) {
                colS = 0;
                rowS++;
            }
            zeroCnt++;
            inFile >> pixelVal;
        }
        return pixelVal; //non-zero
    }
   /* int skipZeros(ifstream& inFile, int pixelVal) {

        while (pixelVal == 0) {
            colS++;
            inFile >> pixelVal;
            if (colS >= numCols) {
                colS = 0;
                rowS++;
            }
        }
        return pixelVal; //non-zero
    }
    */
};

int main(int argc, char *argv[]){
    ifstream inFile1(argv[1]);

    int numRows, numCols, minVal, maxVal;
    inFile1 >> numRows;
    inFile1 >> numCols;
    inFile1 >> minVal;
    inFile1 >> maxVal;
    RunLength *run = new RunLength(numRows, numCols, minVal, maxVal);

    cout << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;

    int numMethod = stoi(argv[2]) ;
    string name = argv[1];
    string nameEncodeFile = run->nameEncodeFile(name,numMethod);
    ofstream encodeFile(nameEncodeFile);

    encodeFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
    encodeFile << numMethod << endl;

    if(numMethod==1){
        run->encodeMethod1(inFile1, encodeFile);
    }
    else if(numMethod==4){
        run->encodeMethod4(inFile1, encodeFile);
    }else {
        cout << "Error";
    }


     inFile1.close();
     encodeFile.close();

     return 0;
}