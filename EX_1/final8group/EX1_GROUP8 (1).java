import java.util.Scanner;

public class EX1_GROUP8 {
	public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int choice;  

        do {
            // ask the user for conversion choice
            System.out.println("\nChoose number base to convert:");
            System.out.println("1. Binary to Hexadecimal");
            System.out.println("2. Hexadecimal to Binary");
            System.out.println("0. Exit");
            System.out.print("Enter your choice (0, 1, or 2): ");

            choice = scanner.nextInt();
            scanner.nextLine(); 

            switch (choice) {// ask the user for conversion choice
                case 1:
                    // Convert from Binary to Hexadecimal number
                    System.out.print("Enter a binary number: ");
                    String binaryNumber = scanner.nextLine(); // ask from the user to enter an binary number
                    // Validate binary input
                    while  (!isValidBinary(binaryNumber)) { // check if the binary number is invalid
                        System.out.println( "Invalid binary input \nEnter a binary number: ");
                        binaryNumber = scanner.nextLine();
                       
                    }
                    
                    System.out.println("Hexadecimal: " + convertBinaryToHex(binaryNumber)); // convert and print
                    System.out.print("Do you want to convert another number? (1 for yes/ 0 for no): ");

                    	break ;

                case 2:
                    // Convert from Hexadecimal to Binary
                    System.out.print("Enter a hexadecimal number: ");
                    String hexadecimalInput = scanner.nextLine(); // ask from the user to enter an hexadecimal number
                    // Validate hexadecimal input
                    while (!isValidHex(hexadecimalInput)) {
                        System.out.println("Invalid hexadecimal input \nEnter a hexadecimal number:"); 
                        hexadecimalInput = scanner.nextLine();
                    }
                    
                    System.out.println("Binary: " + convertHexToBinary(hexadecimalInput)); // convert and print
                    System.out.print("Do you want to convert another number? (1 for yes/ 0 for no): ");
                  	break;

                    
                case 0:// don't convert- exit
                    System.out.println("you chose to exit, Goodbye <3 ");
                    break;

                default:
                    System.out.println("Invalid choice. Please enter 0, 1, or 2.");
            }

            // Ask the user if they want to calculate another conversion
            if (choice != 0) {
                int continueChoice = scanner.nextInt();
                while (continueChoice != 1 && continueChoice != 0 ) {
                		System.out.print("Enter a valid choise ");
                    	continueChoice = scanner.nextInt();
                    	}
                if (continueChoice == 0) {
                    System.out.println("you chose to exit, Goodbye <3 ");
                    break;
                }                	
                
            }
            

        } while (choice != 0);     
        scanner.close();
    }

    public static String convertBinaryToHex(String binaryNumber) {
       

        // make sure the length of the binary number is a multiple of 4 by converting to X4 digits
        binaryNumber = putZeroBinary(binaryNumber);

    
     // Convert binary to hexadecimal
        String hexadecimalNumber = ""; // Change the binary number to string number
        for (int i = 0; i < binaryNumber.length(); i += 4) {
            String bin = binaryNumber.substring(i, i + 4); // For every 4 binary digits - convert to decimal
            int decimalValue = binaryToDecimal(bin);
            hexadecimalNumber += decimalToHex(decimalValue); // Add all converts of all 4 digits groups to one string
        }
        
        
        return hexadecimalNumber.toString();
    }

    public static String convertHexToBinary(String hexNumber) {

        // Convert each hex digit to binary 
        String binaryNumber = "";
        for (int i = 0; i < hexNumber.length(); i++) {
            // Get the current hex digit
            char hexDigit = hexNumber.charAt(i);
            // Calculate decimal value based on a digit or a letter
            int decimalValue;
            if (Character.isDigit(hexDigit)) {
                // If it's a digit, convert directly to decimal
                decimalValue = hexDigit - '0'; // ASCII
            } else {
                // If it's a letter (A-F), convert after making sure it is an uppercase letter
                decimalValue = Character.toUpperCase(hexDigit) - 'A' + 10; // and then convert from hexadecimal to decimal
            }
            // Convert decimal value to binary
            String binaryValue = convertDecimalToBinary(decimalValue);
            binaryValue = putZeroBinary(binaryValue);
            // Add the binary value to the string result
            binaryNumber += binaryValue;
        }

        return binaryNumber;
    }

    public static String convertDecimalToBinary(int decimal) {
        // Convert decimal to binary
        if (decimal == 0) {
            return "0";
        }

        String binary = "";
        while (decimal > 0) {
            int remainder = decimal % 2;
            binary = remainder + binary; //take all the remainders. add the current reminder to the left every time
            decimal /= 2;
        }
        return binary;
    }

    public static boolean isValidBinary(String binaryNumber) {
    	if (binaryNumber=="") {
    		return false;
    	}
        // Check if the input contains only 0s and 1s
        for (char c : binaryNumber.toCharArray()) {
            if (c != '0' && c != '1') {
                return false;
            }
        }
        return true;
    }

    static boolean isValidHex(String hexNumber) {
    	if (hexNumber=="") {
    		return false;
    	}
        // Check if the input contains valid hexadecimal char ( 0-9 and A-F)
        for (char c : hexNumber.toCharArray()) {
            if (!Character.isDigit(c) && (Character.toUpperCase(c) < 'A' || Character.toUpperCase(c) > 'F')) {
                return false;
            }
        }
        return true;
    }

    public static String putZeroBinary(String binaryNumber) {
    	// Ensure the binary number has a length that is a multiple of 4
        int extraBinaryDigits = binaryNumber.length() % 4; // Represents the extra binary digits when dividing binaryNumber length by 4
        if (extraBinaryDigits != 0) {
            int DigitsNeedToAdd = 4 - extraBinaryDigits;
            String FitedBinary = "";  // Initialize as an empty string
            for (int i = 0; i < DigitsNeedToAdd; i++) {
            	FitedBinary += '0';  // Concatenate '0' to the string
            }
            FitedBinary += binaryNumber;  // Concatenate binaryNumber to the string
            binaryNumber = FitedBinary;  // Assign the concatenated string back to binaryNumber
        }
        return binaryNumber;
    }
    

    public static int binaryToDecimal(String binary) {
        // Convert binary to decimal
        int decimal = 0;
        for (int i = binary.length() - 1, j = 0; i >= 0; i--, j++) { //run on the binary number
            int bit = binary.charAt(i) - '0'; // convert char to Int in ASCII
            decimal += bit * Math.pow(2, j); //<---looks the digits from the RIGHT (digit1)*2^(j)+(digit2)*2^(j+1)....
        }
        return decimal;
    }

    public static char decimalToHex(int decimal) {
        // Convert decimal to hexadecimal
        if (decimal >= 0 && decimal <= 9) {
            return (char) (decimal + '0'); //casting from int to char
        } else {
            return (char) (decimal - 10 + 'A'); // casting digits that more than 9 from int to char.
        }
    }

}
