#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
#include <random>
#include <unordered_set>
using namespace std;

class Kmean {
public:
    class Point {
    public:
        double Xcoord;//convert to int when plotting onto 2D displayAry
        double Ycoord;
        int label;
        double distance;

        Point(){
            Xcoord = 0;
            Ycoord = 0;
            label = 0;
            distance = 99999.00; //the distance to its own cluster centroid.
        }
        Point(double Xcoord, double Ycoord, int label, double distance){
            this->Xcoord = Xcoord;
            this->Ycoord = Ycoord;
            this->label = label;
            this->distance = distance;
        }
    };

    int K; // K clusters given in argv[2]
    int numPts; //The total number of points
    int numRows;
    int numCols;
    Point* KcentroidAry;//No 0 as cluster label, cluster label from 1 to K

    Kmean(){
        int K = 0;
        int numPts = 0;
        int numRows = 0;
        int numCols = 0;
    }

    Kmean(int K, int numPts, int numRows, int numCols){
        this->K = K;
        this->numPts = numPts;
        this->numRows = numRows;
        this->numCols = numCols;
        KcentroidAry = new Point[K+1];
    }

    //Methods

    void loadPointSet(ifstream& inFile, Point* pointSet){
        int index = 0;
        while(!inFile.eof()){
            int x, y;
            inFile >> x;
            inFile >> y;
            pointSet[index].Xcoord = (double) x;
            pointSet[index].Ycoord = (double) y;
            pointSet[index].label = 0; //meaning there is no lable yet
            //pointSet[index].label = rand() % K + 1;
            pointSet[index].distance = 99999.00;
            index++;
        }
    }
     void KMeansClustering(Point* pointSet, int K, int** displayAry, ofstream& outFile){
            int iteration = 0;
            int *choosedIndex = new int[K]{-1}; //store the centroid index that already choosed
            iniDisplay(displayAry);
            selectKcentroids(pointSet, K, choosedIndex);
            int change = 4;
             while(change > 2){
                 int index = 0;
                 iteration++;
                 change = 0;
                 while(index < numPts){
                     Point *pt = &pointSet[index];
                     double minDist = pointSet[index].distance;//pt's distance
                     int minLabel = distanceMinLable(pt, KcentroidAry,minDist);
                     if(pointSet[index].label != minLabel){
                         pointSet[index].label = minLabel;
                         change++;
                     }
                     index++;
                 }
                 plotDisplayAry(pointSet, displayAry);
                 prettyPrint(displayAry, outFile, iteration);
                 computeCentroids(pointSet, KcentroidAry);
           }
    }
    bool checkRepeat(int index, int* choosedIndex){ //returns true is the index has been generated prior
        for(int i=0; i<K; i++){
            if(choosedIndex[i] == index){
                return true;//the index has been generated
            }
        }
        return false;
    }
    void selectKcentroids(Point* pointSet, int K, int* choosedIndex) {

        int Kcnt = 0;
        bool repeatYN = true;
        int index = 0;

        while(Kcnt < K) {//Kcentroid's size is K+1, so we don't need Kcnt<=K

            index = rand() % numPts;
            while(repeatYN){
                repeatYN = checkRepeat(index, choosedIndex);
                index = rand() % numPts;
            }
            choosedIndex[Kcnt] = index;
            Kcnt++;
            KcentroidAry[Kcnt].Xcoord = pointSet[index].Xcoord;
            KcentroidAry[Kcnt].Ycoord = pointSet[index].Ycoord;
            KcentroidAry[Kcnt].label = Kcnt;
            KcentroidAry[Kcnt].distance = 0.0;
        }
    }

    void  iniDisplay(int** displayAry){
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
               displayAry[i][j] = 0;
            }
        }
    }

    int  distanceMinLable(Point* pt, Point* KcentroidAry, double minDist) {
        minDist = 99999.00;
        int minLabel = 0;
        int label = 1;
        while(label<=K){
            Point* whichCentroid = &KcentroidAry[label];
            double dist = computeDist(pt, whichCentroid);
            if(dist < minDist){
                minLabel = label;
                minDist = dist;
            }
            label++;
            pt->distance = minDist;
        }
        return minLabel;
    }
    int computeCentroids(Point* pointSet, Point* KcentroidAry){

      double *sumX = new double[K+1]{0.0};
      double *sumY = new double[K+1]{0.0};
      int    *totalPt = new int[K+1]{0};
      int index = 0;
      while(index < numPts){
          int label = pointSet[index].label;
          sumX[label] += pointSet[index].Xcoord;
          sumY[label] += pointSet[index].Ycoord;
          totalPt[label]++;
          index++;
      }
      int label = 1;
      while(label <= K){
          if(totalPt[label]>0){
              KcentroidAry[label].Xcoord = sumX[label]/totalPt[label];
              KcentroidAry[label].Ycoord = sumY[label]/totalPt[label];
              label++;
          }
      }
    }
    double computeDist(Point* pt, Point* whichCentroid){
        double x1 = pt->Xcoord;
        double y1 = pt->Ycoord;
        double x2 = whichCentroid->Xcoord;
        double y2 = whichCentroid->Ycoord;
        return sqrt(pow(x2-x1,2)+ pow(y2-y1,2) * 1.0);
    }


    void plotDisplayAry(Point* pointSet, int** displayAry){
        for(int i=0; i<numPts; i++){
            int x = (int) pointSet[i].Xcoord;
            int y = (int) pointSet[i].Ycoord;
            displayAry[x][y] = pointSet[i].label;
        }
    }
    void prettyPrint(int** displayAry, ofstream& outFile, int iteration){
      outFile << " K : " << K  << " iteration :" << iteration;
      for(int i=0; i<numRows; i++){
          for(int j=0; j<numCols; j++){
              if(displayAry[i][j] > 0){
                  outFile << displayAry[i][j];
              }else{
                  outFile << " ";
              }
          }
          outFile << endl;
       }
    }
   void printResult(Point* pointSet, ofstream& outFile){
        outFile << numRows << " " << numCols << endl;
        outFile << numPts << endl;
        int i = 0;
        while(i<numPts){
            outFile << pointSet[i].Xcoord << " " << pointSet[i].Ycoord <<  " " <<  pointSet[i].label  <<  endl;
            i++;
        }
    }


};

int main(int argc, char *argv[]) {
    srand((unsigned)time(0));

    ifstream inFile1(argv[1]);
    int K = stoi(argv[2]);

    ofstream outFile1(argv[3]);
    ofstream outFile2(argv[4]);

    int numRows, numCols, numPts;
    inFile1 >> numRows;
    inFile1 >> numCols;
    inFile1 >> numPts;
    cout << "numRows:" << numRows << " numCols:" << numCols << endl;
    cout << numPts << endl;

    Kmean::Point *pointSet = new Kmean::Point[numPts]; //1D array of Point class of size numPts

    int** displayAry = new int*[numRows]; //a 2D array, size of numRows by numCols for displaying purposes
    for(int i=0; i<numRows; i++){
        displayAry[i] = new int[numCols];
    }

    int change = 0;
    Kmean *kmean = new Kmean(K, numPts, numRows, numCols);

    kmean->loadPointSet(inFile1, pointSet);
    kmean->KMeansClustering(pointSet, K, displayAry , outFile1);

    kmean->printResult(pointSet, outFile2);
    inFile1.close();
    outFile1.close();
    outFile2.close();
    return 0;







}
