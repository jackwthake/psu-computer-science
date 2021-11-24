/**
 * Represents a Node in the list, this list has no LLL class just a node class. Each node contains the functionality
 * to work with itself, or move to the next node by calling the next nodes function.
 */
public class Dictionary_Node {
    private String x, y;
    private Dictionary_Node next;

    /**
     * Default Constructor
     */
    public Dictionary_Node() {
        this.x = this.y = null;
        this.next = null;
    }


    /**
     * Constructs a populated pair in the dictionary
     * @param x
     * X is the first value in the pair
     * @param y
     * Y is the second value in the pair
     */
    public Dictionary_Node(String x, String y) {
        this.x = x;
        this.y = y;
        this.next = null;
    }


    /**
     * Adds a new node onto the end of the list
     * @param x
     * First value in the pair
     * @param y
     * Second value in the pair
     * @return
     * Returns a reference to the resulting list.
     */
    public Dictionary_Node add_node(String x, String y) {
        if (this.next == null) {
            if (this.x == null && this.y == null) { // empty list
                this.x = x;
                this.y = y;

                return this;
            }

            this.next = new Dictionary_Node(x, y);
            return this;
        }

        this.next = this.next.add_node(x, y);
        return this;
    }


    /**
     * Searches the LLL for a matching X value
     * @param x
     * Search key
     * @return
     * Returns the associated Y value if it exists, null otherwise.
     */
    public String get_matching(String x) {
        if (this.x.compareToIgnoreCase(x) == 0) {
            return this.y;
        }

        if (this.next != null)
            return this.next.get_matching(x);

        return null;
    }
}
