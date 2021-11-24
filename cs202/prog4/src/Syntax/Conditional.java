package Syntax;


public class Conditional extends Syntax {
    private static final String cond_path = "./data/conditional.txt";

    public static void main(String[] args) {
        Conditional cond = new Conditional();
        cond.digest_string("if (var > 1 && var < 6) { }");
        cond.translate();
        cond.emit_translation();
    }

    public Conditional() {
        // load dictionary from file
        super(cond_path);
    }

    @Override
    public void digest_string(String untranslated) {
        this.tokens = untranslated.replace("else if", "elif").split(" ");
        this.remove_invalid_parens();

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


    protected void remove_invalid_parens() {
        int paren_count = 0;
        int first_paren_position = 0;
        int last_paren_position = 0;

        for (int i = 0; i < this.tokens.length; ++i) {
            if (this.tokens[i].contains("(") && paren_count == 0) {
                ++paren_count;
                first_paren_position = i;
            }

            if (this.tokens[i].contains(")")) {
                ++paren_count;
                last_paren_position = i;
            }
        }

        this.tokens[first_paren_position] = this.tokens[first_paren_position].replace("(", "");
        this.tokens[last_paren_position] = this.tokens[last_paren_position].replace(")", "");
    }
}
