public class Dictionary_Node {
    private String x, y;
    private Dictionary_Node next;

    // default constructor
    public Dictionary_Node() {
        this.x = this.y = null;
        this.next = null;
    }


    // normal constructor
    public Dictionary_Node(String x, String y) {
        this.x = x;
        this.y = y;
        this.next = null;
    }


    // recursively add a node to the list
    public Dictionary_Node add_node(String x, String y) {
        if (this.next == null) {
            if (this.x == null && this.y == null) {
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


    // Search the dictionary for a matching node
    public String get_matching(String x) {
        if (this.x.compareToIgnoreCase(x) == 0) {
            return this.y;
        }

        if (this.next != null)
            return this.next.get_matching(x);

        return null;
    }
}
