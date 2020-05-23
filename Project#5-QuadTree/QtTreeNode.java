import java.io.BufferedWriter;
import java.io.IOException;

public class QtTreeNode {

   int color; //  0/1/2
   int upperR;
   int upperC;
   int squareSize;

   QtTreeNode NWkid;
   QtTreeNode NEkid;
   QtTreeNode SWkid;
   QtTreeNode SEkid;

   QtTreeNode(){
//      color = 1;
//      upperR = 0;
//      upperC = 0;
//
//      squareSize = 1; //?????
//      NWkid = null;
//      NEkid = null;
//      SWkid = null;
//      SEkid = null;
   }

   QtTreeNode(int color, int upperR, int upperC,  int squareSize, QtTreeNode NWkid, QtTreeNode NEkid, QtTreeNode SWkid, QtTreeNode SEkid){
       this.color = color;
       this.upperR = upperR;
       this.upperC = upperC;
       this.squareSize = squareSize;
       this.NWkid = NWkid;
       this.NEkid = NEkid;
       this.SWkid = SWkid;
       this.SEkid = SEkid;
   }

   public void printQtNode(QtTreeNode node, BufferedWriter outFile) throws IOException {
       //outFile.write("Nodes Output: \n");
       if(node.NWkid!=null && node.NEkid != null && node.SWkid != null && node.SEkid != null){
           outFile.write(node.color + " " + node.upperR +" " + node.upperC + " " + node.NWkid.color + " "
                   + node.NEkid.color + " " + node.SWkid.color + " " + node.SEkid.color + "\n");
       }else{
           outFile.write(node.color + " " + node.upperR +" " + node.upperC + " " + null + " " + null + " "+ null + " " + null +"\n");
       }
   }

}
