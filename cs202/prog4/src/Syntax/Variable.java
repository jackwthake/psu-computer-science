package Syntax;

/*
 * Jack Thake
 * CS 202
 * Variable.java
 *
 * Represents the translation of a C++ variable declaration to a Python declaration. This class is derived from the
 * Syntax class.
 */

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * This class represents the translation of one variable declaration from C++ to python.
 * It inherits from the Syntax.Syntax base class and implements its abstract methods.
 */
public class Variable extends Syntax {
    private static final String var_path = "./data/variable.txt";

    /**
     * Default constructor
     */
    public Variable() {
        // load the dictionary from file
        super(var_path);
    }


    /**
     * This method is responsible for in-taking a piece of untranslated C++ code, splitting it into tokens
     * and refining the contents of the tokens to more easily translate.
     *
     * @param untranslated
     * Raw C++ code to be translated
     */
    @Override
    public void digest_string(String untranslated) {
        if (is_array(untranslated)) { // digest an array declaration
            this.tokens = untranslated.split(" ", 2); // split datatype from rest of statement
            this.tokens[1] = this.tokens[1].replaceAll(" ", ""); // remove all spaces in the second portion
            this.tokens[1] = this.tokens[1].replace(";", ""); // remove ending semi-colon

        } else { // digest a normal variable declaration
            this.tokens = untranslated.split(" ");
            this.tokens[this.tokens.length - 1] = this.tokens[this.tokens.length - 1].replace(";", ""); // remove semi colon

            if (this.tokens[0].compareToIgnoreCase("const") == 0) { // remove const qualifier
                String[] old_tokens = this.tokens;
                this.tokens = new String[old_tokens.length - 1];

                // remove the const qualifier
                System.arraycopy(old_tokens, 1, this.tokens, 0, old_tokens.length - 1);
            }

            // remove any asterisks
            for (int i = 0; i < this.tokens.length; ++i) {
                this.tokens[i] = this.tokens[i].replace("*", "");
            }
        }
    }


    /**
     * This method is responsible for translating the currently untranslated string given by the digest_string method
     * @return
     * Returns true upon success, false otherwise
     */
    @Override
    public boolean translate() {
        if (this.tokens == null)
            return false;

        // remove last space
        this.tokens[this.tokens.length - 1] = this.tokens[this.tokens.length - 1].split(" ")[0];
        this.translated = "";

        // check if we're translating an array declaration or a normal variable
        if (this.is_array()) {
            if (!this.translate_array()) {
                return false;
            }
        } else {
            if (!this.translate_normal_var()) {
                return false;
            }
        }

        this.translated = this.translated.replaceAll("\\s+$", ""); // remove trailing white space
        return true;
    }


    /**
     * Translate a C++ variable declaration to python
     * @return
     * Returns true upon success, false otherwise.
     */
    private boolean translate_normal_var() {
        String[] old_tokens = this.tokens;
        this.tokens = new String[old_tokens.length - 1];

        // remove data type token
        System.arraycopy(old_tokens, 1, this.tokens, 0, this.tokens.length);

        for (String token : this.tokens) { // For a normal variable we don't need the dictionary
            this.translated = this.translated.concat(token + " ");
        }

        return true;
    }


    /* Translate arrays */


    /**
     * Translate a C++ array declaration to python
     * @return
     * Returns true upon success, false otherwise.
     */
    private boolean translate_array() {
        // *----*------------------------------------------------*----------------------------*------------------*
        // | ## | C++ Array Decl                                 | Python Array Decl          | Translation Type |
        // |----|------------------------------------------------|----------------------------|------------------|
        // | 1. | data_type name[length];                        | name = [None] * length;    | Empty array      |
        // | 2. | data_type name[length] = { };                  | name = [None] * length;    | Empty array      |
        // | 3. | data_type name[length] = { array contents };   | name = [ array contents ]  | Populated array  |
        // | 4. | data_type name[] = { array contents };         | name = [ array contents ]  | Populated array  |
        // *----*------------------------------------------------*----------------------------*------------------*

        if (this.translate_empty_array_decl()) // first check for an empty array declaration
            return true;
        else
            return this.translate_populated_array_decl();
    }


    /**
     * Translate an empty C++ array declaration, ie int array[10]; or int array[10] = {};
     * @return
     * Returns true upon a successful translation, false otherwise.
     */
    private boolean translate_empty_array_decl() {
        Pattern pattern;
        Matcher match;
        String identifier, length, search_key, search_result;

        // Get the array name
        pattern = Pattern.compile("(.+)\\[");
        match = pattern.matcher(this.tokens[1]);
        if (match.find()) {
            identifier = match.group(1);
        } else {
            throw new IllegalArgumentException();
        }

        // get the array length
        pattern = Pattern.compile("\\[(.*?)\\]");
        match = pattern.matcher(this.tokens[1]);
        if (match.find()) {
            length = match.group(1);
        } else {
            throw new IllegalArgumentException();
        }

        // start refining search key
        search_key = this.tokens[1].replaceAll(".*\\[", "["); // remove array identifier
        search_key = search_key.replaceAll("\\[[^\\[]*\\]", "[!]"); // reduce to generic search term
        search_key = search_key.replaceAll("=\\{\\}", ""); // remove set initialization, if it exists

        // search the dictionary
        search_result = this.syntax_dictionary.get_matching(search_key);
        if (search_result != null) { // if a result is found
            this.translated = identifier + " " + search_result; // construct translation
            this.translated = this.translated.replaceAll("!", length); // substitute ! with array length

            return true;
        }

        // if we reach here then this was not an empty array declaration
        return false;
    }


    /**
     * Translates a populated C++ array declaration. ie int nums[3] = { 1, 2, 3 }; or int nums[] = { 1, 2, 3 };
     * @return
     * Returns true upon a successful translation, false otherwise.
     */
    private boolean translate_populated_array_decl() {
        Pattern pattern;
        Matcher match;
        String identifier, array_contents, search_key, search_result;

        // Get the array name
        pattern = Pattern.compile("(.+)\\[");
        match = pattern.matcher(this.tokens[1]);
        if (match.find()) {
            identifier = match.group(1);
        } else {
            throw new IllegalArgumentException();
        }

        // Get the array contents
        pattern = Pattern.compile("\\{.+\\}");
        match = pattern.matcher(this.tokens[1]);
        if (match.find()) {
            array_contents = match.group();
            array_contents = array_contents.replaceAll("(\\{|\\})", "");
        } else {
            throw new IllegalArgumentException();
        }

        // Refine search key
        search_key = this.tokens[1].replaceAll(".*\\[", "["); // remove array identifier
        search_key = search_key.replaceAll("\\[[^\\[]*\\]", "[]"); // reduce to generic search term
        search_key = search_key.replaceAll("=\\{.+\\}", "={!}"); // remove set initialization, if it exists

        // search the dictionary
        search_result = this.syntax_dictionary.get_matching(search_key);
        if (search_result != null) { // if a result is found
            this.translated = identifier + " " + search_result; // construct translation
            this.translated = this.translated.replaceAll("!", array_contents); // substitute ! with array length

            return true;
        }

        return false;
    }


    /* Helper Functions */


    /**
     * Helper function to determine whether a string contains an array
     * @param str
     * The string to check
     * @return
     * Returns true if the passed string contains a C++ array declaration
     */
    private boolean is_array(String str) {
        return str.contains("[");
    }


    /**
     * Helper function to check if the current token array contains an array declaration
     * @return
     * Returns true if the passed string contains a C++ array declaration
     */
    private boolean is_array() {
        for (String token : this.tokens) {
            if (token.contains("[")) return true;
        }

        return false;
    }
}
