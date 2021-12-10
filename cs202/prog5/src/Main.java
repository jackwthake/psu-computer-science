import Dictionary.*;
import java.util.Scanner;

/*
 * Jack Thake
 * CS 202
 * Main.java
 * Created Monday, Nov 29th, 2021
 *
 * This class is meant to be the interface between the user and the underlying system. Combination of both program 4
 * and program 5. Program 5 is under the dictionary package while program 4 is under the syntax package
 */

/**
 * Main class for the translator program, handles input and output with the user and interacts with the context class.
 */
public class Main {
    private final Context context;
    private final Tree tree;
    private final Scanner scanner;

    /**
     * Main entry point of the program
     * @param args
     * Terminal arguments
     */
    public static void main(String[] args) {
        Main main = new Main();
        main.input_loop();
    }


    /**
     * Default constructor
     */
    public Main() {
        this.context = new Context();
        this.tree = new Tree();
        this.scanner = new Scanner(System.in);
    }


    /**
     * Main input loop with the user
     */
    public void input_loop() {
        char conf;
        int choice;

        do {
            System.out.println("What would you like to:");
            System.out.println("1. Translate C++ to python");
            System.out.println("2. lookup python dictionary");
            System.out.println("Please enter 1 or 2: ");
            choice = this.scanner.nextInt();
            this.scanner.nextLine();

            if (choice == 1) {
                if (this.get_translator_input()) {
                    System.out.println("Successful.");

                    System.out.print("Would you like to view the translation? (y/n): ");
                    conf = this.scanner.next().charAt(0);
                    this.scanner.nextLine();
                    if (Character.toLowerCase(conf) == 'y') {
                        this.context.emit_translation();
                    }
                } else {
                    System.out.println("Translation failed.");
                }
            } else if (choice == 2){
                dictionary_tree_interaction();
            } else {
                System.out.println("Unknown input: " + choice);
            }

            System.out.print("Would you like to do more? (y/n): ");
            conf = this.scanner.next().charAt(0);
            this.scanner.nextLine();
        } while (Character.toLowerCase(conf) != 'n');
    }


    /**
     * Enters a line of code into the context
     */
    private boolean get_translator_input() {
        System.out.println("Please limit variable declarations to one line i.e. 'char *name = \"Jack\";'");
        System.out.println("Please include any curly braces present in a conditional or loop statement");
        System.out.println("Please enter a valid line of C++ code:");
        return this.context.translate(scanner.nextLine());
    }

    private void dictionary_tree_interaction() {
        int choice;

        System.out.println("What would you like to:");
        System.out.println("1. Insert an item into the tree");
        System.out.println("2. Search the tree");
        System.out.println("3. Clear the tree");
        System.out.println("4. Display the tree");
        System.out.println("Please enter 1 or 4: ");
        choice = this.scanner.nextInt();
        this.scanner.nextLine();

        switch (choice) {
            case 1 -> { // insert
                String key, value;
                System.out.print("Please enter the name of the term: ");
                key = scanner.nextLine();
                System.out.println("Please enter the definition of the term:");
                value = scanner.nextLine();
                this.tree.insert(new Entry(key, value));
            }
            case 2 -> { // search
                String search_key;
                System.out.print("Please enter the name to search: ");
                search_key = scanner.nextLine();
                Entry result = this.tree.search(search_key);
                if (result != null) {
                    System.out.println(result.to_String());
                } else {
                    System.out.println("No matching entry found.");
                }
            }
            case 3 -> // clear
                    this.tree.clear_tree();
            case 4 -> // display
                    this.tree.display();
            default -> System.out.println("Unknown input option: " + choice);
        }
    }
}
