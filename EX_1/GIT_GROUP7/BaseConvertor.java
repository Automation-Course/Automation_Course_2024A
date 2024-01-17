import java.util.Scanner;
import java.util.InputMismatchException;

public class BaseConvertor {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean exit = false;

        while (!exit) {

            try {
                // Display menu for conversion options
                System.out.println("Welcome To GROUP 7 Convertor, Please Choose conversion direction:");
                System.out.println("1. Binary to Hexadecimal");
                System.out.println("2. Hexadecimal to Binary");
                System.out.println("3. Exit");

                // Get user choice
                int choice = scanner.nextInt();
                scanner.nextLine();

                switch (choice) {
                    case 1:
                        // Binary to Hexadecimal conversion
                        System.out.println("Enter binary number:");
                        String binaryInput = scanner.nextLine();
                        if (isValidBinary(binaryInput)) {
                            System.out.println("Hexadecimal result: " + binaryToHex(binaryInput));
                        } else {
                            System.out.println("Invalid binary input. Please enter a valid binary number.");
                        }
                        break;
                    case 2:
                        // Hexadecimal to Binary conversion
                        System.out.println("Enter hexadecimal number:");
                        String hexInput = scanner.nextLine();
                        if (isValidHexadecimal(hexInput)) {
                            System.out.println("Binary result: " + hexToBinary(hexInput));
                        } else {
                            System.out.println("Invalid hexadecimal input. Please enter a valid hexadecimal number.");
                        }
                        break;
                    case 3:
                        // User Exit the program
                        exit = true;
                        System.out.println("Exiting the program. Goodbye!");
                        break;
                    default:
                        System.out.println("Invalid choice. Please enter 1, 2, or 3.");
                }
            } catch (InputMismatchException e) {
                // Handle invalid input
                System.out.println("Invalid input. Please enter a valid integer.");
                scanner.nextLine();
            }
        }

        scanner.close();
    }

    // Check if the Binary number is valid
    private static boolean isValidBinary(String binary) {
        return binary.matches("[01]+");
    }

    // Check if the hexadecimal number is valid
    private static boolean isValidHexadecimal(String hex) {
        return hex.matches("[0-9A-F]+");
    }

    // Convert binary to hexadecimal
    private static String binaryToHex(String binary) {
        int decimal = binaryToDecimal(binary);
        return decimalToHex(decimal);
    }

    // Convert hexadecimal to binary
    private static String hexToBinary(String hex) {
        int decimal = hexToDecimal(hex);
        return decimalToBinary(decimal);
    }

    // Convert binary to decimal
    private static int binaryToDecimal(String binary) {
        int decimal = 0;
        int binaryLength = binary.length();

        for (int i = 0; i < binaryLength; i++) {
            int digit = binary.charAt(i) - '0';
            decimal += digit * Math.pow(2, binaryLength - 1 - i);
        }

        return decimal;
    }

    // Convert decimal to hexadecimal
    private static String decimalToHex(int decimal) {
        StringBuilder hex = new StringBuilder();

        while (decimal > 0) {
            int remainder = decimal % 16;
            char hexDigit = (char) (remainder < 10 ? remainder + '0' : remainder - 10 + 'A');
            hex.insert(0, hexDigit);
            decimal /= 16;
        }

        return hex.toString();
    }

    // Convert hexadecimal to decimal
    private static int hexToDecimal(String hex) {
        int decimal = 0;
        int hexLength = hex.length();

        for (int i = 0; i < hexLength; i++) {
            char hexDigit = hex.charAt(i);
            int digitValue = Character.isDigit(hexDigit) ? hexDigit - '0' : hexDigit - 'A' + 10;
            decimal += digitValue * Math.pow(16, hexLength - 1 - i);
        }

        return decimal;
    }

    // Convert decimal to binary
    private static String decimalToBinary(int decimal) {
        StringBuilder binary = new StringBuilder();

        while (decimal > 0) {
            int remainder = decimal % 2;
            binary.insert(0, remainder);
            decimal /= 2;
        }

        return binary.toString();
    }
}
