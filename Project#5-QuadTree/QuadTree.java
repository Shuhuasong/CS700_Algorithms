import java.io.*;
import java.util.Scanner;

public class QuadTree {
    QtTreeNode Qtroot;
    //Image image;

    QuadTree(){
        Qtroot = new QtTreeNode();
    }


    public QtTreeNode buildQuadTree(int[][] imgAry, int upR, int upC, int size) {
        QtTreeNode newQtNode = new QtTreeNode(-1, upR, upC, size, null, null, null, null);
        if (size == 1) {
            newQtNode.color = imgAry[upR][upC];//1 or 0
            //System.out.println("( " + upR + ", " + upC + " )\n");
        } else {
            int halfSize = size/2;
            newQtNode.NWkid = buildQuadTree(imgAry, upR, upC, halfSize);
            newQtNode.NEkid = buildQuadTree(imgAry, upR, upC+halfSize, halfSize);
            newQtNode.SWkid = buildQuadTree(imgAry, upR+halfSize, upC, halfSize);
            newQtNode.SEkid = buildQuadTree(imgAry, upR+halfSize, upC+halfSize, halfSize);
            int sumColor = newQtNode.NWkid.color + newQtNode.NEkid.color + newQtNode.SWkid.color + newQtNode.SEkid.color;
            if (sumColor == 0) {
                newQtNode.color = 0;
                newQtNode.NWkid = null;
                newQtNode.NEkid = null;
                newQtNode.SWkid = null;
                newQtNode.SEkid = null;
            } else if (sumColor == 4) {
                newQtNode.color = 1;
                newQtNode.NWkid = null;
                newQtNode.NEkid = null;
                newQtNode.SWkid = null;
                newQtNode.SEkid = null;
            } else {
                newQtNode.color = 5;
            }
        }
        return newQtNode;
    }

    public void preOrderTraversal(QtTreeNode Qt, BufferedWriter outFile) throws IOException {
        if (Qt.SWkid == null & Qt.NEkid == null && Qt.SWkid == null && Qt.SEkid == null) {
            Qt.printQtNode(Qtroot, outFile);
        } else {
            Qt.printQtNode(Qt, outFile);
            preOrderTraversal(Qt.NWkid, outFile);
            preOrderTraversal(Qt.NEkid, outFile);
            preOrderTraversal(Qt.SWkid, outFile);
            preOrderTraversal(Qt.SEkid, outFile);
        }
    }

    public void postOrderTraversal(QtTreeNode Qt, BufferedWriter outFile) throws IOException {
        if (Qt.SWkid == null & Qt.NEkid == null && Qt.SWkid == null && Qt.SEkid == null) {
            Qt.printQtNode(Qt, outFile);
            //return;
        } else {

            postOrderTraversal(Qt.NWkid, outFile);
            postOrderTraversal(Qt.NEkid, outFile);
            postOrderTraversal(Qt.SWkid, outFile);
            postOrderTraversal(Qt.SEkid, outFile);
            Qt.printQtNode(Qt, outFile);
        }
    }

}

