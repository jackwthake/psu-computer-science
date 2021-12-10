package Dictionary;

/*
 * Jack Thake
 * Tree_node.java
 * CS202
 *
 * Represents one node in the redblack tree, uses an entry as its data.
 */

public class Tree_node {
    public Entry data;
    public Tree_node left, right, parent;
    public Color color;

    public enum Color {
        RED,
        BLACK
    }

    /**
     * Normal constructor for a node
     * @param data
     * The data to be contained in the node
     * @param parent
     * A reference to the node's parent
     */
    public Tree_node(Entry data, Tree_node parent) {
        this.data = data;
        this.parent = parent;
        this.color = Color.RED;
    }

    /**
     * Get the uncle of the node
     * @return
     * Returns the node's uncle
     */
    public Tree_node get_uncle() {
        Tree_node gp = parent.parent;
        if (gp.left == parent) {
            return gp.right;
        } else if (gp.right == parent) {
            return gp.left;
        } else {
            return null;
        }
    }
}
