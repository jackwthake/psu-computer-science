package Syntax;


public class Conditional extends Syntax {
    private static final String cond_path = "./data/conditional.txt";

    public static void main(String[] args) {
        Conditional cond = new Conditional();
        cond.digest_string("if(variable > 1 && variable < 6) { }");
        cond.translate();
        cond.emit_translation();
    }

    public Conditional() {
        // load dictionary from file
        super(cond_path);
    }

    @Override
    public void digest_string(String untranslated) {
        untranslated = this.remove_invalid_parens(untranslated);
        this.tokens = untranslated.replace("else if", "elif").split(" ");

        // remove last space
        this.tokens[this.tokens.length - 1] = this.tokens[this.tokens.length - 1].split(" ")[0];
    }

    @Override
    public boolean translate() {
        if (this.tokens == null)
            return false;

        // generate translation with dictionary
        this.translated = "";
        for (String token : this.tokens) {
            String str = this.syntax_dictionary.get_matching(token);
            if (str != null) {
                this.translated = this.translated.concat(str + " ");
            } else {
                this.translated = this.translated.concat(token + " ");
            }
        }

        this.translated = this.translated.replaceAll("\\s+$", ""); // remove trailing white space

        // remove space between last token and colon
        StringBuilder sb = new StringBuilder(this.translated);
        sb.deleteCharAt(sb.length() - 2);

        // apply changes and return
        this.translated = sb.toString();
        return true;
    }


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
