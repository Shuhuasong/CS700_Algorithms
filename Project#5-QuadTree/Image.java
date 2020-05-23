import java.io.*;
import java.util.Scanner;

public class Image {
    private static int numRows;
    private static int numCols;
    private static int minVal;
    private static int maxVal;

    int squareSize;
    int[][] imgAry;
    //Scanner inFile;
    Image(){
     numRows = 0;
     numCols = 0;
     minVal = 0;
     maxVal = 0;
     squareSize=0;
     imgAry = new int[numRows][numCols];
    }

    Image(int numRows, int numCols, int minval, int maxVal, int squareSize, int[][] imgAry){
        this.numRows = numRows;
        this.numCols = numCols;
        this.minVal = minVal;
        this.maxVal = maxVal;
        this.squareSize = squareSize;
        this.imgAry = imgAry;
    }

    public static int computeSquare(int numRows, int numCols) {
        int square = Math.max(numRows, numCols);
        int power2 = 2;
        while(power2 < square){
            power2 = power2 * 2;
        }
        return power2;
    }

    public static void loadImage(int[][] imgAry, Scanner inFile){

        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                imgAry[i][j] = inFile.nextInt();
               // System.out.println(imgAry[i][j]);
            }
           // System.out.println();
        }
    }

    public void zero2DAry(int[][] imgAry){
      // squareSize = computeSquare(numRows, numCols);
       //imgAry = new int[squareSize][squareSize];
       for(int i=0; i<squareSize; i++){
           for(int j=0; j<squareSize; j++){
               imgAry[i][j] = 0;
           }
       }
    }

    public static void main(String[] args) throws IOException {
        Scanner inFile = new Scanner(new FileReader(args[0]));
        BufferedWriter outFile1 = new BufferedWriter(new FileWriter(new File(args[1])));
        BufferedWriter outFile2 = new BufferedWriter(new FileWriter(new File(args[2])));

       // int numRows, numCols, minVal, maxVal;
        numRows = inFile.nextInt();
        numCols = inFile.nextInt();
        minVal = inFile.nextInt();
        maxVal = inFile.nextInt();
        //System.out.println("numRows: " + numRows + ", numCols: " + numCols + ", minVal: " + minVal + ", maxVal: " + maxVal)

       // Image image = new Image(numRows, numCols, minVal, maxVal, 0, imgAry);
        int squareSize = computeSquare(numRows, numCols);
       // System.out.println("squareSize: " + squareSize);
        int[][] imgAry = new int[squareSize][squareSize];
        //image.zero2DAry(imgAry);
       /* for(int i=0; i<squareSize; i++){
            for(int j=0; j<squareSize; j++){
                System.out.println(imgAry[i][j]);
            }
        }

        */

        //load image
        loadImage(imgAry, inFile);


            QuadTree Qtree = new QuadTree();
            QtTreeNode qtRoot = Qtree.buildQuadTree(imgAry, 0, 0, squareSize);

            outFile1.write("PreOrder: \n");
            Qtree.preOrderTraversal(qtRoot, outFile1);
            outFile1.write("PostOrder: \n");
            Qtree.postOrderTraversal(qtRoot, outFile1);

        inFile.close();
        outFile1.close();
        outFile2.close();
    }

}
