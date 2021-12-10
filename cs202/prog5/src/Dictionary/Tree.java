package Dictionary;

/*
 * Jack Thake
 * Tree.java
 * CS202
 *
 * Represents one Red-Black tree, using the node class.
 */

public class Tree {
    private Tree_node root;

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
        Tree_node[] nodes = this.insert(this.root, null, data);
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
    private Tree_node[] insert(Tree_node root, Tree_node parent, Entry data) {
        Tree_node[] arr;

        if (root == null) {
            Tree_node tmp = new Tree_node(data, parent);
            return new Tree_node[]{tmp, tmp};
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
    private void rotate_right(Tree_node root) {
        Tree_node parent = root.parent;
        Tree_node left = root.left;

        // perform the rotation if possible
        root.left = left.right;
        if (left.right != null) {
            left.right.parent = root;
        }

        left.right = root;
        root.parent = left;

        // reset the parent child relationships after the rotation
        this.replace_parents_child(parent, root, left);
    }


    /**
     * Rotates left from a given node
     * @param root
     * The node to act as the origin of the rotation
     */
    private void rotate_left(Tree_node root) {
        Tree_node parent = root.parent;
        Tree_node right = root.right;

        // perform the rotation if possible
        root.right = right.left;
        if (right.left != null) {
            right.left.parent = root;
        }

        right.left = root;
        root.parent = right;

        // Reset the parent child relationships after the rotation
        this.replace_parents_child(parent, root, right);
    }


    /**
     * Replace a parent's child after rotation
     * @param parent
     * The parent
     * @param old_c
     * The previous child
     * @param new_c
     * The new child
     */
    private void replace_parents_child(Tree_node parent, Tree_node old_c, Tree_node new_c) {
        if (parent == null) { // we are the root node
            this.root = new_c;
        } else if (parent.left == old_c) { // the child to replace is left
            parent.left = new_c;
        } else if (parent.right == old_c) { // the child to replace is right
            parent.right = new_c;
        } else // not in the hierarchy
            return;

        if (new_c != null) { // change parent
            new_c.parent = parent;
        }
    }


    /**
     * Check colors in the region of a newly inserted node
     * @param root
     * THe newly inserted node
     */
    private void check_and_fix_colors(Tree_node root) {
        if (root.parent == null) { // the root is always black
            root.color = Tree_node.Color.BLACK;
            return;
        }

        if (root.parent.color == Tree_node.Color.BLACK) { // no rule is violated if our parent is black
            return;
        }

        // check if we have a gp
        Tree_node gp = root.parent.parent;
        if (gp == null) { // if we don't have a grandparent, then our parent has to be the root.
            root.parent.color = Tree_node.Color.BLACK; // ensure the root is black
            return;
        }

        // get the uncle of our current node, check it's color
        Tree_node uncle = root.get_uncle();
        if (uncle != null && uncle.color == Tree_node.Color.RED) {
            // if uncle is red, then we need to recolor our parent and grandparent
            root.parent.color = Tree_node.Color.BLACK;
            uncle.color = Tree_node.Color.BLACK;
            gp.color = Tree_node.Color.RED;

            // since we recolored our grandparent we now need to check if that new color is correct
            check_and_fix_colors(gp);
        } else if (root.parent == gp.left) { // determine which type of rotation is necessary
            if (root == root.parent.right) {
                rotate_left(root.parent);
                root.parent = root;
            }

            rotate_right(gp); // we always center the rotation around our grandparent
            root.parent.color = Tree_node.Color.BLACK;
            gp.color = Tree_node.Color.RED;
        } else {
            if (root == root.parent.left) {
                rotate_right(root.parent);
                root.parent = root;
            }

            rotate_left(gp); // we always center the rotation around our grandparent
            root.parent.color = Tree_node.Color.BLACK;
            gp.color = Tree_node.Color.RED;
        }
    }


    /**
     * Recursively display the tree
     * @param root
     * The current node to display
     */
    private void display(Tree_node root) {
        if (root == null) return;

        // in order traversal

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
    private Entry search(Tree_node root, String key) {
        if (root == null) return null;

        // just traverse as if it were a BST

        if (root.data.isEqual(key)) {
            return root.data;
        } else if (root.data.greater_than(key)) {
            return this.search(root.left, key);
        }

        return this.search(root.right, key);
    }
}
