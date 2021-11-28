import Syntax.Conditional;
import Syntax.Loop;
import Syntax.Syntax;
import Syntax.Variable;

/**
 * Represents one C++ statement, determines which type it is and translates. This class makes use of dynamic binding.
 */
public class Context {
    Syntax syntax;

    public static void main(String[] args) {
        Context con = new Context();
        con.translate("sdfss");
        con.emit_translation();
    }

    /**
     * Default constructor
     */
    public Context() {
        syntax = null;
    }


    /**
     * Translates a given string from the three available syntax types
     * @param untranslated
     * The string of C++ to be translated
     * @return
     * Returns true upon success
     */
    public boolean translate(String untranslated) {
        Context_Type type = this.get_type(untranslated); // get the type of the code
        switch (type) { // create the appropriate syntax object
            case VARIABLE -> this.syntax = new Variable();
            case CONDITIONAL -> this.syntax = new Conditional();
            case LOOP -> this.syntax = new Loop();
            default -> throw new IllegalArgumentException(untranslated + " is not valid.");
        }

        // digest and then translate
        this.syntax.digest_string(untranslated);
        return this.syntax.translate();
    }


    /**
     * Emits the final translation to the console.
     */
    public void emit_translation() {
        if (syntax != null) {
            syntax.emit_translation();
        }
    }


    /**
     * Gets the type of code passed to the function: Variable, Conditional, Loop
     * @param untranslated
     * The untranslated C++ code to check
     * @return
     * Returns the correct type of statement
     */
    public Context_Type get_type(String untranslated) {
        // break down the untranslated code
        untranslated = untranslated.replaceAll(" ", "");
        String type = untranslated.split("\\(", 2)[0];

        switch (type) { // this can catch loops and if statements
            case "if" -> {
                return Context_Type.CONDITIONAL;
            } case "for", "while" -> {
                return Context_Type.LOOP;
            }
        }

        // if we reach out here and there's a '=' and a ';' present in the string, it must be a variable declaration
        if (untranslated.contains("=") && untranslated.contains(";")) {
            return Context_Type.VARIABLE;
        }

        return Context_Type.UNKNOWN;
    }
}
