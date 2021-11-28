import java.util.Scanner;


/**
 * Main class for the translator program, handles input and output with the user and interacts with the context class.
 */
public class Translator {
    private final Context context;
    private final Scanner scanner;

    /**
     * Main entry point of the program
     * @param args
     * Terminal arguments
     */
    public static void main(String[] args) {
        Translator translator = new Translator();
        translator.input_loop();
    }


    /**
     * Default constructor
     */
    public Translator() {
        this.context = new Context();
        this.scanner = new Scanner(System.in);
    }


    /**
     * Main input loop with the user
     */
    public void input_loop() {
        char conf;

        do {
            if (this.get_input()) {
                System.out.println("Successful.");

                System.out.print("Would you like to view the translation? (y/n): ");
                conf = this.scanner.next().charAt(0);
                if (Character.toLowerCase(conf) == 'y') {
                    this.context.emit_translation();
                }
            } else {
                System.out.println("Translation failed.");
            }

            System.out.print("Would you like to translate another line? (y/n): ");
            conf = this.scanner.next().charAt(0);
        } while (Character.toLowerCase(conf) != 'n');
    }


    /**
     * Enters a line of code into the context
     */
    private boolean get_input() {
        System.out.println("Please enter a valid line of C++ code:");
        return this.context.translate(scanner.nextLine());
    }
}
