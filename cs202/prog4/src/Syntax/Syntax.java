package Syntax;

import java.io.BufferedReader;
import java.io.FileReader;

/**
 * This abstract base class represents one of my three chosen scopes for translating C++ to Python
 * This class is responsible for loading a dictionary from file. This dictionary is a linear linked list
 * of pairs, with each pair representing a C++ term and its equivalent term in Python.
 */
abstract public class Syntax {
    protected String translated;
    protected String[] tokens;

    protected Dictionary syntax_dictionary;
    private final String dictionary_path;


    /**
     * Default constructor
     */
    public Syntax() {
        this.translated = this.dictionary_path = null;
        this.syntax_dictionary = null;
        this.tokens = null;
    }


    /**
     * Constructs a Syntax.Syntax object, loading its internal dictionary from file
     * @param dictionary_path
     * The path to the dictionary file, the data file should be formatted as {C++ Term},{Equivalent Python Term}
     */
    public Syntax(String dictionary_path) {
        this.dictionary_path = dictionary_path;
        this.translated = null;
        this.tokens = null;

        // Create the dictionary for tokens, each node contains the c++ term followed by the python term
        this.syntax_dictionary = new Dictionary();

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


    /**
     * Prints the final translation if it exists
     */
    public void emit_translation() {
        if (this.translated != null) System.out.println(this.translated);
    }


    // abstract functions for the children to implement
    abstract public void digest_string(String untranslated); // tokenize the string
    abstract public boolean translate(); // translate the string
}
