public class Node {
    private int data;
    private Node leftChild, rightChild;
    public Node(int data) {
        this.data = data;
        this.leftChild = null;
        this.rightChild = null;
    }
    public int getData() {
        return this.data;
    }
    public Node getLeft() {
        return this.leftChild;
    }
    public Node getRight() {
        return this.rightChild;
    }
    public void modifyLeft(Node newNode) {
        this.leftChild = newNode;
    }
    public void modifyRight(Node newNode) {
        this.rightChild = newNode;
    }
}
