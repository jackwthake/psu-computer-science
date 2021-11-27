package Syntax;

import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Loop extends Conditional {
    private static final String loop_path = "./data/loop.txt";

    public static void main(String[] args) {
        Loop loop = new Loop();
        loop.digest_string("for(int num : numbers) {}");
        loop.translate();
        loop.emit_translation();
    }

    public Loop() {
        super(loop_path);
    }


    @Override
    public void digest_string(String untranslated) {
        this.tokens = untranslated.split("\\(", 2);
        String type = this.tokens[0];

        this.tokens = this.tokens[1].split(" ", 2);
        this.tokens[0] = type;

        this.tokens[1] = this.tokens[1].replaceAll(" ", ""); // remove any spaces in the second token
        this.tokens[1] = this.tokens[1].replaceAll("\\{\\}", ""); // remove ending curly brace
        this.tokens[1] = this.remove_invalid_parens(this.tokens[1]); // remove extra paren
    }


    @Override
    public boolean translate() {
        // *----*------------------------------------------------*----------------------------*
        // | ## | C++ loop Decl                                  | Python loop Decl           |
        // |----|------------------------------------------------|----------------------------|
        // | 1. | for (int i = 0; i < length; ++i) {}            | for i in range(length)     |
        // | 2. | for (type data : array) {}                     | for data in array          |
        // | 3. | while (condition) {}                           | while condition            |
        // *----*------------------------------------------------*----------------------------*

        if (this.tokens == null)
            return false;

        switch(this.tokens[0]) {
            case "for":
                if (this.translate_for_in_loop())
                    return true;
                if (this.translate_for_range_loop())
                    return true;
                break;
            case "while":
                if (this.translate_while_loop())
                    return true;
                break;
            default:
                throw new UnknownError();
        }

        return false;
    }


    private boolean translate_for_range_loop() {
        String iterator_name = "", iterator_starting_val, loop_length = "", search_result;
        Pattern pattern;
        Matcher match;

        this.tokens = this.tokens[1].split(";");
        if (this.tokens.length < 2)
            return false;

        // get the iterator name
        pattern = Pattern.compile(".+?=");
        match = pattern.matcher(this.tokens[0]);
        if (match.find()) {
            iterator_name = match.group();
            iterator_name = iterator_name.replace("=", "");
        }

        // get the starting value of the iterator
        iterator_starting_val = this.tokens[0].replaceAll(".+?=", "");

        // get the loop length
        pattern = Pattern.compile("\\W.+$");
        match = pattern.matcher(this.tokens[1]);
        if (match.find()) {
            loop_length = match.group();
            loop_length = loop_length.replaceAll("[<>=]+", "");
        }

        // get string from dictionary
        search_result = this.syntax_dictionary.get_matching("for()");
        translated = iterator_name + " = " + iterator_starting_val + "\n";
        translated = translated.concat(search_result);

        // substitute values
        translated = translated.replace("*", iterator_name);
        translated = translated.replace("!", loop_length);

        return false;
    }


    private boolean translate_for_in_loop() {
        String search_result;

        this.tokens = this.tokens[1].split(":");
        search_result = this.syntax_dictionary.get_matching("for(:)");
        search_result = search_result.replace("*", this.tokens[0]);
        search_result = search_result.replace("!", this.tokens[1]);

        this.translated = search_result;

        return false;
    }


    private boolean translate_while_loop() {
        // TODO: Implement me
        return false;
    }
}
