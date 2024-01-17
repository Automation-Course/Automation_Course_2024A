import java.util.Scanner;

public class GIT_GROUP11 {

    public static int choice;
    public static String binaryInput;
    public static String hexInput;

    public static void main(String[] args) {
        while (true) {
            menu();

            if (choice == 1) {
                binaryTohexOutput();
            } else if (choice == 2) {
                hexOutputTobinary();}
            else if (choice == 3) {
                break;
            } else {
                System.out.println("Invalid choice. Please enter 1, 2 or 3.");
            }
        }
    }

    private static void hexOutputTobinary() {
        Scanner input = new Scanner(System.in);

        do {
            //get binary input from the user and validate
            System.out.print("\n" + "Enter a hexadecimal number: ");
            hexInput = input.nextLine();

            if (!isValidHex(hexInput)) {
                System.out.println("Invalid hexadecimal input. Please enter a hexadecimal number.");
            }
        }
        while (!isValidHex(hexInput)); //repeat the loop as long as the input is incorrect

        //perform hexadecimal to binary conversion
        String binaryOutput = hexToBinary(hexInput);
        System.out.println(hexInput + " in hexadecimal is " + binaryOutput + " in binary.");
    }

    private static void binaryTohexOutput() {
        Scanner input = new Scanner(System.in);
        do {
            //get binary input from the user and validate
            System.out.print("\n" + "Enter a binary number: ");
            binaryInput = input.nextLine();

            if (!isValidBinary(binaryInput)) {
                System.out.println("Invalid binary input. Please enter a binary number containing only 0s and 1s.");
            }
        } while (!isValidBinary(binaryInput)); //repeat the loop as long as the input is incorrect

        //perform binary to hexadecimal conversion
        String hexOutput = binaryToHex(binaryInput);


        System.out.println(binaryInput + " in binary is " + hexOutput + " in hexadecimal.");
    }

    private static void menu() {
        Scanner input = new Scanner(System.in);
        System.out.println("Choose Conversion:");
        System.out.println("1. Binary to Hexadecimal");
        System.out.println("2. Hexadecimal to Binary");
        System.out.println("3. Exit");
        System.out.print("Enter your choice: ");
        choice = input.nextInt();
        input.nextLine(); //enter for the newline character
    }

    //check if the input is a valid binary number
    private static boolean isValidBinary(String input) {
        return input.matches("[01]+");
    }

    //converting a binary number to its hexadecimal representation
    private static String binaryToHex(String binary) {
        String hex = "";
        int decimal = binaryToDecimal(binary);
        while (decimal > 0) {
            int remainder = decimal % 16;
            char hexDigit = (char) (remainder < 10 ? '0' + remainder : 'A' + remainder - 10);
            hex = hexDigit + hex;
            decimal /= 16;
        }
        if(hex == "")
            return "0";
        return hex;
    }

    //convert binary to decimal
    private static int binaryToDecimal(String binary) {
        int decimal = 0;
        int power = 0;
        for (int i = binary.length() - 1; i >= 0; i--) {
            if (binary.charAt(i) == '1') {
                decimal += Math.pow(2, power);
            }
            power++;
        }
        return decimal;
    }


    //check if the input is a valid hexadecimal number
    private static boolean isValidHex (String input) {
        return input.matches("[0-9A-Fa-f]+");
    }

    //convert hexadecimal to binary
    private static String hexToBinary(String hex) {
        String binary = "";
        for (char hexDigit : hex.toCharArray()) {
            int decimal = hexDigitToDecimal(hexDigit);
            binary += decimalToBinary(decimal); //add to answer
        }
        return binary.replaceFirst("^0+", "");
    }

    //convert hexadecimal digit to decimal
    private static int hexDigitToDecimal(char hexDigit) {
        if (hexDigit >= '0' && hexDigit <= '9') {
            return hexDigit - '0';
        } else if (hexDigit >= 'A' && hexDigit <= 'F') {
            return hexDigit - 'A' + 10;
        }
        return hexDigit - 'a' + 10;
    }

    //convert decimal to binary
    private static String decimalToBinary(int decimal) {
        String binary = "";
        while (decimal > 0) {
            int remainder = decimal % 2;
            binary = remainder + binary; //built string
            decimal /= 2;
        }
        while (binary.length() < 4) { //complete to 4 digit  binary number
            binary = "0" + binary;
        }
        return binary;
    }
}
