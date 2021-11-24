package Syntax;

/**
 * This class represents the translation of one variable declaration from C++ to python.
 * It inherits from the Syntax.Syntax base class and implements its abstract methods.
 */
public class Variable extends Syntax {
    private static final String var_path = "./variable.txt";

    public static void main(String[] args) {
        Variable var = new Variable();
        var.digest_string("const char *str = \"hello world\";");
        var.translate();
        var.emit_translation();
    }

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
    @SuppressWarnings("StringConcatenationInLoop")
    @Override
    public boolean translate() {
        if (this.tokens == null)
            return false;

        this.translated = "";
        for (String token : this.tokens) { // convert tokens to their dictionary matches
            String str = this.syntax_dictionary.get_matching(token);
            if (str != null) { // is in the dictionary
                this.translated += str + " ";
            } else { // if a value isn't in the dictionary we just emit it
                this.translated += token + " ";
            }
        }

        // remove last space
        this.tokens[this.tokens.length - 1] = this.tokens[this.tokens.length - 1].split(" ")[0];
        return true;
    }
}
