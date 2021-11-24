import java.util.Arrays;

public class Variable extends Syntax {
    private static final String var_path = "./variable.txt";

    public static void main(String[] args) {
        Variable var = new Variable();
        var.digest_string("const int val = 15;");
        var.translate();
        var.emit_translation();
    }

    Variable() {
        super(var_path);
    }

    @Override
    public void digest_string(String untranslated) {
        this.tokens = untranslated.split(" ");

        if (this.tokens[0].compareToIgnoreCase("const") == 0) { // remove const qualifier
            String[] old_tokens = this.tokens;
            this.tokens = new String[old_tokens.length - 1];

            // remove the const qualifier
            System.arraycopy(old_tokens, 1, this.tokens, 0, old_tokens.length - 1);
        }

        // remove semi colon
        if (this.tokens[this.tokens.length - 1].contains(";")) {
            this.tokens[this.tokens.length - 1] = this.tokens[this.tokens.length - 1].split(";")[0];
        }
    }

    @Override
    public boolean translate() {
        if (this.tokens == null)
            return false;

        this.translated = "";
        for (String token : this.tokens) {
            String str = this.syntax_dictionary.get_matching(token);
            if (str != null) {
                this.translated += str + " ";
            } else {
                this.translated += token + " ";
            }
        }

        // remove last space
        if (this.tokens[this.tokens.length - 1].contains(" ")) {
            this.tokens[this.tokens.length - 1] = this.tokens[this.tokens.length - 1].split(" ")[0];
        }

        return true;
    }
}
