package Syntax;

/**
 * This class represents the translation of one variable declaration from C++ to python.
 * It inherits from the Syntax.Syntax base class and implements its abstract methods.
 */
public class Variable extends Syntax {
    private static final String var_path = "./data/variable.txt";

    /**
     * Default constructor
     */
    Variable() {
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
        this.tokens = untranslated.split(" "); // split into tokens
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
        for (String token : this.tokens) { // convert tokens to their dictionary matches
            String str = this.syntax_dictionary.get_matching(token);
            if (str != null) {
                this.translated = this.translated.concat(str + " ");
            } else {
                this.translated = this.translated.concat(token + " ");
            }
        }

        this.translated = this.translated.replaceAll("\\s+$", ""); // remove trailing white space
        return true;
    }

    // TODO: Implement the ability to declare arrays
}
