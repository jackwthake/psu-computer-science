/*
 * Jack Thake
 * Node.java
 *
 */

public class Node {
    private final int[] data;
    private final Node[] children;
    private final Node parent;

    // constants
    public static final int UNUSED = Integer.MAX_VALUE;

    public enum traversal_dir {
        LEFT,
        MIDDLE,
        RIGHT,
    }

    public Node(Node parent) {
        this.data = new int[] { UNUSED, UNUSED };
        this.children = new Node[3];
        this.parent = parent;
    }

    public void insert(int to_add) {
        if (this.data[1] == Node.UNUSED) { // if the leaf won't overflow
            if (to_add < this.data[0]) {
                this.data[1] = this.data[0];
                this.data[0] = to_add;
            } else {
                this.data[1] = to_add;
            }
        } else if (this.data[0] < to_add && this.data[1] > to_add && this.children[1] == null) { // if it's a full leaf, and we can insert a middle
            this.children[1] = new Node(this);
            this.children[1].data[0] = to_add;
        } else {
            this.split_leaf(to_add);
        }
    }

    private void push_to_parent(int to_push) {
        this.parent.insert(to_push);
    }

    private void split_leaf(int to_add) {
        if (this.num_children() < 3) { // node with two children
            if (this.parent == null) { // we are the root
                this.split_root(to_add);
            } else {
                int mid = this.get_mid_point(to_add);
                if (mid == -1) { // midpoint is the value we're trying to add
                    this.push_to_parent(to_add);
                } else {
                    this.push_to_parent(this.data[mid == 0 ? 1 : 0]);
                }
            }
        } else { // node with three children

        }
    }

    private void split_root(int to_add) {
        int mid = this.get_mid_point(to_add);

        if (mid == -1) { // midpoint is the value we're trying to add
            this.children[0] = new Node(this);
            this.children[2] = new Node(this);
            this.children[0].data[0] = this.data[0];
            this.children[2].data[0] = this.data[1];

            this.data[0] = to_add;
        } else { // midpoint is one of our current keys
            int to_push = this.data[mid];
            int to_split = this.data[mid == 0 ? 1 : 0];

            this.children[0] = new Node(this);
            this.children[2] = new Node(this);

            if (to_add < to_split) {
                this.children[0].data[0] = to_add;
                this.children[2].data[0] = to_split;
            } else {
                this.children[0].data[0] = to_split;
                this.children[2].data[0] = to_add;
            }

            this.data[0] = to_push;
        }

        this.data[1] = UNUSED;
    }

    public traversal_dir get_traversal_direction(int to_add) {
        if (to_add < this.data[0]) // less than left
            return traversal_dir.LEFT;
        else if (this.data[1] == UNUSED && to_add > this.data[0]) // only one value in the node behave like BST
            return  traversal_dir.RIGHT;
        else if (this.data[1] != UNUSED && to_add < this.data[1]) // if both exist check for middle
            return traversal_dir.MIDDLE;
        else // has to be right now
            return traversal_dir.RIGHT;
    }

    public Node get_left_child() {
        return this.children[0];
    }

    public Node get_middle_child() {
        return this.children[1];
    }

    public Node get_right_child() {
        return this.children[2];
    }

    private int get_mid_point(int to_add) {
        if (to_add < this.data[0])
            return 0;
        else if (this.data[1] < to_add)
            return 1;

        return -1; // will return -1 if the middle point is the value to be inserted
    }

    private int num_children() {
        int count = 0;
        for (int i = 0; i < 3; ++i) {
            if (this.children[i] != null)
                ++count;
        }

        return count;
    }
}
