package Dictionary;

/*
 * Jack Thake
 * Entry.java
 * CS202
 *
 * This class represents one entry in the dictionary of python terms, used in the Tree_node class.
 */

public class Entry {
    private final String key;
    private final String value;

    public Entry(String key, String value) {
        this.key = key;
        this.value = value;
    }

    public final String get_value() {
        return this.value;
    }
    public final String get_key() {
        return this.key;
    }

    public boolean isEqual(String key) {
        return this.key.compareToIgnoreCase(key) == 0;
    }

    public boolean greater_than(String key) {
        return this.key.compareToIgnoreCase(key) > 0;
    }

    public boolean less_than(Entry key) {
        return this.key.compareToIgnoreCase(key.key) < 0;
    }

    public String to_String() {
        return this.key + "\n" + this.value;
    }
}
