import java.io.BufferedReader;
import java.io.FileReader;

abstract public class Syntax {
    protected String translated;
    protected String[] tokens;

    protected Dictionary_Node syntax_dictionary;
    private final String dictionary_path;


    // default constructor
    public Syntax() {
        this.translated = this.dictionary_path = null;
        this.syntax_dictionary = null;
        this.tokens = null;
    }


    // load the syntax dictionary from file
    public Syntax(String dictionary_path) {
        this.dictionary_path = dictionary_path;
        this.translated = null;
        this.tokens = null;

        // Create the dictionary for tokens, each node contains the c++ term followed by the python term
        this.syntax_dictionary = new Dictionary_Node();

        // attempt to read the data file
        try(BufferedReader br = new BufferedReader(new FileReader(this.dictionary_path))) {
            for(String line; (line = br.readLine()) != null; ) { // read line by line
                String[] tokens = line.split(","); // format should be {C++ Term},{Python Term}
                this.syntax_dictionary.add_node(tokens[0], tokens[1]);
            }
        } catch (java.io.IOException e) {
            System.out.println("Failed to load data file at path " + this.dictionary_path);
        }
    }


    // print out translated string
    public void emit_translation() {
        if (this.translated != null) System.out.println(this.translated);
    }


    // abstract functions for the children to implement
    abstract public void digest_string(String untranslated);
    abstract public boolean translate();
}
