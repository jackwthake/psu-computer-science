package Dictionary;

/*
 * Jack Thake
 * Node.java
 *
 */

public class Node {
    public Entry data;
    public Node left, right, parent;
    public Color color;

    enum Color {
        RED,
        BLACK
    }

    public Node(Entry data, Node parent) {
        this.data = data;
        this.parent = parent;
        this.color = Color.RED;
    }

    public Node get_uncle() {
        Node grandparent = parent.parent;
        if (grandparent.left == parent) {
            return grandparent.right;
        } else if (grandparent.right == parent) {
            return grandparent.left;
        } else {
            throw new IllegalStateException("Parent is not a child of its grandparent");
        }
    }
}
