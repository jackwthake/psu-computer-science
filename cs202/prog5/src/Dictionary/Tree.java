package Dictionary;

/*
 * Jack Thake
 * Tree.java
 *
 */

public class Tree {
    private Node root;


    /**
     * Default constructor
     */
    public Tree() {
        this.root = null;
    }


    /**
     * Insert an item into the tree
     * @param data
     * THe entry to be inserted
     */
    public void insert(Entry data) {
        Node[] nodes = this.insert(this.root, null, data);
        this.root = nodes[0];
        this.check_and_fix_colors(nodes[1]);
    }


    /**
     * Recursively display the tree
     */
    public void display() {
        this.display(this.root);
    }


    /**
     * Recursively search the tree for a result
     * @param key
     * The key to search for
     * @return
     * Returns either a matching entry or a null reference
     */
    public Entry search(String key) {
        return this.search(this.root, key);
    }


    /**
     * Clears the tree
     */
    public void clear_tree() {
        this.root = null;
    }
    

    /**
     * Inserts a node recursively into the list, not checking for color errors
     * @param root
     * the current node in the recursive function
     * @param parent
     * the parent of the current node
     * @param data
     * the data to be inserted
     * @return
     * Returns an array where the first index is the root, the second being a reference to the added node
     */
    private Node[] insert(Node root, Node parent, Entry data) {
        Node[] arr;

        if (root == null) {
            Node tmp = new Node(data, parent);
            return new Node[]{tmp, tmp};
        }

        if (data.less_than(root.data)) {
            arr = insert(root.left, root, data);
            root.left = arr[0];
        } else {
            arr = insert(root.right, root, data);
            root.right = arr[0];
        }

        arr[0] = root;
        return arr;
    }


    /**
     * Rotates right from a given node
     * @param root
     * The node to act as the origin of the rotation
     */
    private void rotate_right(Node root) {
        Node parent = root.parent;
        Node leftChild = root.left;

        root.left = leftChild.right;
        if (leftChild.right != null) {
            leftChild.right.parent = root;
        }

        leftChild.right = root;
        root.parent = leftChild;

        this.replace_parents_child(parent, root, leftChild);
    }


    /**
     * Rotates left from a given node
     * @param root
     * The node to act as the origin of the rotation
     */
    private void rotate_left(Node root) {
        Node parent = root.parent;
        Node rightChild = root.right;

        root.right = rightChild.left;
        if (rightChild.left != null) {
            rightChild.left.parent = root;
        }

        rightChild.left = root;
        root.parent = rightChild;

        this.replace_parents_child(parent, root, rightChild);
    }


    /**
     * Replace a parent's child after rotation
     * @param parent
     * The parent
     * @param old_child
     * The previous child
     * @param new_child
     * The new child
     */
    private void replace_parents_child(Node parent, Node old_child, Node new_child) {
        if (parent == null) { // we are the root node
            this.root = new_child;
        } else if (parent.left == old_child) { // the child to replace is left
            parent.left = new_child;
        } else if (parent.right == old_child) { // the child to replace is right
            parent.right = new_child;
        } else { // not in the hierarchy
            throw new IllegalStateException("Node is not a child of its parent");
        }

        if (new_child != null) { // change parent
            new_child.parent = parent;
        }
    }


    /**
     * Check colors in the region of a newly inserted node
     * @param root
     * THe newly inserted node
     */
    private void check_and_fix_colors(Node root) {
        if (root.parent == null) { // the root is always black
            root.color = Node.Color.BLACK;
            return;
        }

        if (root.parent.color == Node.Color.BLACK) { // no rule is violated if our parent is black
            return;
        }

        Node grandparent = root.parent.parent;
        if (grandparent == null) {
            root.parent.color = Node.Color.BLACK;
            return;
        }

        Node uncle = root.get_uncle();
        if (uncle != null && uncle.color == Node.Color.RED) {
            root.parent.color = Node.Color.BLACK;
            uncle.color = Node.Color.BLACK;
            grandparent.color = Node.Color.RED;

            check_and_fix_colors(grandparent);
        } else if (root.parent == grandparent.left) {
            if (root == root.parent.right) {
                rotate_left(root.parent);
                root.parent = root;
            }

            rotate_right(grandparent);
            root.parent.color = Node.Color.BLACK; // FIXME Sometimes we reach here and parent is null?
            grandparent.color = Node.Color.RED;
        } else {
            if (root == root.parent.left) {
                rotate_right(root.parent);
                root.parent = root;
            }

            rotate_left(grandparent);
            root.parent.color = Node.Color.BLACK;
            grandparent.color = Node.Color.RED;
        }
    }


    /**
     * Recursively display the tree
     * @param root
     * The current node to display
     */
    private void display(Node root) {
        if (root == null) return;

        this.display(root.left);
        System.out.println(root.data.get_key());
        System.out.println(root.data.get_value());
        this.display(root.right);
    }


    /**
     * Recursively search the tree
     * @param root
     * The current node to search
     * @param key
     * The key to search for
     * @return
     * Returns a matching result or a null reference
     */
    private Entry search(Node root, String key) {
        if (root == null) return null;

        if (root.data.isEqual(key)) {
            return root.data;
        } else if (root.data.greater_than(key)) {
            return this.search(root.left, key);
        }

        return this.search(root.right, key);
    }
}
