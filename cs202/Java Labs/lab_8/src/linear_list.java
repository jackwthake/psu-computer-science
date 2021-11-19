import java.util.Random;

public class linear_list {
    private Node head;
    private final Random rand;

    /* Embedded node */
    public static class Node {
        public Node next;
        public int data;
    }


    public static void main(String[] args) {
        linear_list list = new linear_list();

        list.build();
        System.out.println("last node appears " + list.num_times() + " time(s)");
        list.display();
        list.remove_first_and_last();
        list.display();
        list.remove_all_but_last_two();
        list.display();

        linear_list copy = list.copy_self();
        copy.display();

        if (list.find(2)) System.out.println("2 is in the list");
        else System.out.println("2 is not in the list");
    }


    /* constructor */
    public linear_list() {
        this.head = null;
        rand = new Random();
    }


    /* create a list of random length, with random data */
    public void build() {
        int length = rand.nextInt(10, 20);

        for (int i = 0; i < length; ++ i) {
            int data = rand.nextInt(0, 9);

            this.head = this.add_node(this.head, data);
        }
    }


    /* wrapper function to print the list */
    public void display() {
        this.display(this.head);
    }


    /* find an int in the list */
    public boolean find(final int match) {
        return this.find(this.head, match);
    }


    /* return the amount of the times the last node appears in the list */
    public int num_times() {
        int old_head = this.head.data;
        int ret = this.num_times(this.head);

        if (old_head != this.head.data) {
            this.head.data = old_head;
            --ret;
        }

        return ret;
    }


    /* remove the first and last list element */
    public void remove_first_and_last() {
        this.head = this.head.next;
        this.head = this.remove_last(this.head);
    }


    /* remove everything except the last two nodes */
    public void remove_all_but_last_two() {
        this.remove_all_but_last_two(this.head);
    }


    /* make a copy of the list */
    public linear_list copy_self() {
        linear_list copy = new linear_list();
        copy.head = this.copy_list(this.head);

        return copy;
    }


    /* recursively add a list */
    private Node add_node(Node head, final int to_add) {
        if (head == null) { // last node in the list
            head = new Node();
            head.data = to_add;
            return head;
        }

        head.next = add_node(head.next, to_add);
        return head;
    }


    /* display a list recursively */
    private void display(final Node head) {
        if (head.next == null) { // last node in the list
            System.out.println(head.data);
            return;
        }

        System.out.print(head.data + " -> ");
        display(head.next);
    }


    /* find a node */
    private boolean find(final Node head, final int key) {
        if (head == null) { // last node
            return false;
        } else if (head.data == key) { // match
            return true;
        }

        return find(head.next, key);
    }


    /* count the amount of times the last node appears in the list in one pass */
    private int num_times(final Node head) {
        if (head.next == null)  {
            this.head.data = head.data;
            return 1;
        }

        int ret = num_times(head.next);
        if (head.data == this.head.data) ++ret;

        return ret;
    }


    /* remove the last node */
    private Node remove_last(Node head) {
        if (head.next == null) {
            return null;
        }

        head.next = remove_last(head.next);
        return head;
    }


    /* remove everything but the last two */
    private Node remove_all_but_last_two(Node head) {
        if (head.next.next == null) {
            return null;
        }

        head.next = remove_all_but_last_two(head.next);
        return head;
    }


    /* copy the list */
    private Node copy_list(final Node src) {
        if (src == null) {
            return null;
        }

        Node dest = new Node();
        dest.data = src.data;
        dest.next = copy_list(src.next);

        return dest;
    }
}
