import java.util.Scanner;

public class git {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            // Display menu
            System.out.println("1. Binary to Hexadecimal");
            System.out.println("2. Hexadecimal to Binary");
            System.out.println("3. Exit");

            // Get user choice
            int choice = getUserChoice(scanner);

            if (choice == 1) {
                // Binary to Hexadecimal
                binaryToHexConversion(scanner);
            } else if (choice == 2) {
                // Hexadecimal to Binary
                hexToBinaryConversion(scanner);
            } else if (choice == 3) {
                // Exit the program
                System.out.println("Goodbye!");
                break;
            } else {
                System.out.println("Invalid choice. Please enter 1, 2, or 3.");
            }
        }

        scanner.close();
    }

    // Function to change Binary to Hexadecimal
    static void binaryToHexConversion(Scanner scanner) {
        System.out.print("Enter binary number: ");
        String binaryInput = scanner.next();

        // Check if the binary input is valid
        if (isValidBinary(binaryInput)) {
            long decimalValue = 0;
            for (int i = 0; i < binaryInput.length(); i++) {
                char digit = binaryInput.charAt(i);
                decimalValue = decimalValue * 2 + (digit - '0');
            }

            // Convert decimal to hexadecimal
            char[] hexDigits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
            char[] hexOutputArray = new char[20]; 
            int index = 0;

            while (decimalValue > 0) {
                long hex = decimalValue % 16;
                char hexDigit = hexDigits[(int) hex];
                hexOutputArray[index++] = hexDigit;
                decimalValue /= 16;
            }

            String hexOutput = new String(hexOutputArray, 0, index);
            System.out.println("The Hexadecimal value is: " + hexOutput);
        } else {
            System.out.println("Invalid binary input. Please enter a valid binary number.");
        }
    }

    // Function to change Hexadecimal to Binary 
    static void hexToBinaryConversion(Scanner scanner) {
        System.out.print("Enter hexadecimal number: ");
        String hexInput = scanner.next().toUpperCase();

        // Check if the hexadecimal input is valid
        if (isValidHex(hexInput)) {
            String binaryResult = convertHexToBinary(scanner, hexInput);
            System.out.println("The Binary value is: " + binaryResult);
        } else {
            System.out.println("Invalid hexadecimal input. Please enter a valid hexadecimal number.");
        }
    }

    // Function to convert a hexadecimal number to a binary number
    static String convertHexToBinary(Scanner scanner, String hexNumber) {
        String binaryNumber = "";

        for (int i = 0; i < hexNumber.length(); i++) {
            char hexChar = hexNumber.charAt(i);
            int decimalValue = hexDigitToDecimal(hexChar);

            // Convert each hexadecimal digit to 4-bit binary representation
            for (int j = 3; j >= 0; j--) {
                int bit = (decimalValue / (int) Math.pow(2, j)) % 2;
                binaryNumber += bit;
            }
        }

        return binaryNumber;
    }

    // Function to convert a hexadecimal digit to decimal
    static int hexDigitToDecimal(char hexDigit) {
        if (hexDigit >= '0' && hexDigit <= '9') {
            return hexDigit - '0';
        } else if (hexDigit >= 'A' && hexDigit <= 'F') {
            return hexDigit - 'A' + 10;
        } else {
            throw new IllegalArgumentException("Invalid hexadecimal digit: " + hexDigit);
        }
    }
    
    
    // Function to check if a string is a valid binary number
    static boolean isValidBinary(String binaryStr) {
        // Regular expression to check if the input is a valid binary number
        for (char digit : binaryStr.toCharArray()) {
            if (digit != '0' && digit != '1') {
                return false;
            }
        }
        return true;
    }

    // Function to check if a string is a valid hexadecimal number
    static boolean isValidHex(String hexStr) {
        // Regular expression to check if the input is a valid hexadecimal number
        for (char digit : hexStr.toCharArray()) {
            if (!Character.isDigit(digit) && (digit < 'A' || digit > 'F')) {
                return false;
            }
        }
        return true;
    }

    // Function to safely get an integer choice from the user
    static int getUserChoice(Scanner scanner) {
        while (true) {
            System.out.print("Enter your choice (1, 2, or 3): ");
            try {
                return scanner.nextInt();
            } catch (java.util.InputMismatchException e) {
                // Consume the invalid input and prompt the user again
                scanner.next();
                System.out.println("Invalid input. Please enter a valid integer choice.");
            }
        }
    }
}