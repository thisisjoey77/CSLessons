import java.util.Scanner;

public class treeSort {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] arr;
        int N;

        N = scanner.nextInt();
        arr = new int[N];

        for(int i=0;i<N;i++) {
            arr[i] = scanner.nextInt();
        }

        BinaryTree BST = new BinaryTree(arr,N);
        BST.printBST();
    }
}
