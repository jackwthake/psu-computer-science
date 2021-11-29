package Syntax;

/**
 * Represents the translation of one C++ conditional statement to the equivalent python conditional statement
 */
public class Conditional extends Syntax {
    private static final String cond_path = "./data/conditional.txt";

    /**
     * Default constructor
     */
    public Conditional() {
        // load dictionary from file
        super(cond_path);
    }


    /**
     * Constructor for conditionals children
     * @param path
     * Path to the dictionary file
     */
    protected Conditional(String path) {
        super(path);
    }


    /**
     * Tokenizes the passed piece of untranslated C++ code in preparation of the full translation
     * @param untranslated
     * The untranslated piece of C++ code
     */
    @Override
    public void digest_string(String untranslated) {
        untranslated = this.remove_invalid_parens(untranslated);
        untranslated = untranslated.replaceAll("\\{|\\}", "");
        this.tokens = untranslated.replace("else if", "elif").split(" ");

        // remove last space
        this.tokens[this.tokens.length - 1] = this.tokens[this.tokens.length - 1].split(" ")[0];
    }


    /**
     * This function is responsible for the actual translation from C++ to python
     * @return
     * Returns true if the translation was successful, false otherwise.
     */
    @Override
    public boolean translate() {
        if (this.tokens == null)
            return false;

        // generate translation with dictionary
        this.translated = "";
        for (String token : this.tokens) {
            String str = this.syntax_dictionary.get_matching(token);
            if (str != null) { // FIXME: Not finding relational operator substitutions in dictionary
                this.translated = this.translated.concat(str + " ");
            } else {
                this.translated = this.translated.concat(token + " ");
            }
        }

        this.translated = this.translated.replaceAll("\\s+$", ""); // remove trailing white space
        this.translated = this.translated.concat(":");

        return true;
    }


    /**
     * Removes out-most opening and closing parenthesis for the python translation. `if(condition)` -> `if condition`,
     * Doing this makes the tokenization easier to perform. This process preserves any parenthesis nested in the if
     * statement.
     * @param untranslated
     * The untranslated piece of C++ code
     * @return
     * Returns a string containing the result of removing the out-most parenthesis
     */
    protected String remove_invalid_parens(String untranslated) {
        int paren_count = 0;
        int last_paren_position = 0;

        StringBuilder sb = new StringBuilder(untranslated);

        for (int i = 0; i < sb.length(); ++i) {
            if (sb.charAt(i) == '(' && paren_count == 0) { // capture the first opening parenthesis
                ++paren_count;

                if (i >= 1) {
                    if (sb.charAt(i - 1) == ' ') { // if the last character was a space, just remove the paren
                        sb.deleteCharAt(i);
                    } else {
                        sb.setCharAt(i, ' '); // otherwise, replace the paren with a space
                    }
                }
            } else if (sb.charAt(i) == ')') { // keep updating the closing paren position to capture the last one
                ++paren_count;
                last_paren_position = i;
            }
        }

        // delete the last paren before returning the resulting string
        sb.deleteCharAt(last_paren_position);
        return sb.toString();
    }
}
