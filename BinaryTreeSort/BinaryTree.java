public class BinaryTree {
    private int arrSize;
    private int[] unsortedArr;
    private Node root;

    public BinaryTree(int[] arr, int arrSize) {
        this.root = null;
        this.unsortedArr = arr;
        this.arrSize = arrSize;
        for(int i=0;i<this.arrSize;i++) {
            if(i==0) System.out.print(this.unsortedArr[i] + " is put under the first node.");
            else System.out.print(this.unsortedArr[i] + " is put under the ");
            this.root = insert(this.root,this.unsortedArr[i]);
            System.out.println();
        }
    }

    public Node insert(Node root, int data) {
        if(root==null) {
            return root = new Node(data);
        }
        else if(data<=root.getData()) {
            root.modifyLeft(insert(root.getLeft(),data));
            System.out.print("Left child of " + root.getData() + "...");
        }
        else if(data>root.getData()) {
            root.modifyRight(insert(root.getRight(),data));
            System.out.print("Right child of " + root.getData() + "...");
        }
        return root;
    }

    public void printBST() {
        inorderTraverse(this.root);
    }

    public void inorderTraverse(Node root) {
        if(root!=null) {
            inorderTraverse(root.getLeft());
            System.out.print(root.getData() + " ");
            inorderTraverse(root.getRight());
        }
    }
}
