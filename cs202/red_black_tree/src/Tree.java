/*
 * Jack Thake
 * Tree.java
 *
 */

public class Tree {
    private Node root;

    public static void main(String[] args) {
        Tree t = new Tree();

        t.insert( 10);
        t.insert(12);
        t.insert(30);
        t.insert(38);
        t.insert(45);
        t.insert(15);
        System.out.println();
    }


    public void insert(int to_add) {
        if (this.root == null) {
            this.root = new Node(null);
            this.root.insert(to_add);
        } else {
            this.insert(this.root, to_add);
        }
    }


    private boolean insert(Node root, int to_add) {
        boolean ret = false;
        if (root == null) return false;

        // traverse through the list
        switch (root.get_traversal_direction(to_add)) {
            case LEFT -> ret = this.insert(root.get_left_child(), to_add);
            case MIDDLE -> ret = this.insert(root.get_middle_child(), to_add);
            case RIGHT -> ret = this.insert(root.get_right_child(), to_add);
        }

        // make sure we haven't already inserted
        if (!ret) {
            root.insert(to_add);
            ret = true;
        }

        return ret;
    }
}
