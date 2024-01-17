import java.util.Scanner;

public class GIT_GROUP10 {

	   public static void main(String[] args) {

	        Scanner scanner = new Scanner(System.in);
	        boolean restart = true;
	        while (restart) {
	            System.out.println("Choose Conversion Direction:");
	            System.out.println("1. Binary to Hexadecimal");
	            System.out.println("2. Hexadecimal to Binary");
	            System.out.println("3. Exit");
	            
	            int choice = getValidChoice(scanner);
	            
	            while(choice<1 || choice>3){
	            	 System.out.println("Invalid choice. Please choose 1, 2, or 3.");
	            	 choice = getValidChoice(scanner);
	            }

	            switch (choice) {
				case 1:
                   handleBinaryToHexConversion(scanner);
                   break;
               case 2:
                   handleHexToBinaryConversion(scanner);
                   break;

               case 3:
                   System.out.println("Exiting the program. Goodbye!");
                   restart = false;
                   break;

	            }
	        }
	    }
	           
		private static int getValidChoice(Scanner scanner) {
			while (!scanner.hasNextInt()) {
				System.out.println("Invalid input. Please enter a number.");
				scanner.next();
			}
			return scanner.nextInt();
		}
	    private static void handleBinaryToHexConversion(Scanner scanner) {
	        System.out.print("Enter binary number: ");
	        String binaryInput = scanner.next();
	        while (!isValidBinary(binaryInput)) {
	        	System.out.println("Invalid binary input. Please try again.");
	        	binaryInput = scanner.next();
	        }
	            String hexadecimalOutput = binaryToHex(binaryInput);
	            System.out.println("Hexadecimal: " + hexadecimalOutput);
	        
	    }

	    private static void handleHexToBinaryConversion(Scanner scanner) {
	        System.out.print("Enter hexadecimal number: ");
	        String hexInput = scanner.next();
	        while (!isValidHexadecimal(hexInput)) {
	        	System.out.println("Invalid hexadecimal input. Please try again.");
	        	hexInput = scanner.next();
	        }
	            String binaryOutput = hexToBinary(hexInput);
	            System.out.println("Binary: " + binaryOutput);
	        
	    }

	    private static boolean isValidBinary(String binary) {
	        return binary.matches("[01]+");
	    }

	    private static boolean isValidHexadecimal(String hex) {
	        return hex.matches("[0-9A-F]+");
	    }

	    private static String binaryToHex(String binary) {
	        StringBuilder hexBuilder = new StringBuilder();
	        int length = binary.length();

	        // Pad the binary number with zeros to make its length a multiple of 4
	        while (length % 4 != 0) {
	            binary = "0" + binary;
	            length++;
	        }

	        // Convert each group of 4 bits to hexadecimal
	        for (int i = 0; i < length; i += 4) {
	            String fourBits = binary.substring(i, i + 4);
	            int decimalValue = 0;
	            for (int j = 3; j >= 0; j --) {
	            if (Character.getNumericValue(fourBits.charAt(j))==1)
	            	decimalValue += Math.pow(2, 3 - j);
	            }
	            char hexDigit = (char) (decimalValue < 10 ? '0' + decimalValue : 'A' + (decimalValue - 10));	
	            hexBuilder.append(hexDigit);
	        }

	        return hexBuilder.toString();
	    }

	    private static String hexToBinary(String hex) {
	        StringBuilder binaryBuilder = new StringBuilder();

	        // Convert each hexadecimal digit to 4 bits
	        for (int i = 0; i < hex.length(); i++) {
	            char hexDigit = hex.charAt(i);
	            // Convert each hexadecimal digit to 4 bits
	            int decimalValue = Character.isDigit(hexDigit) ? hexDigit - '0' : Character.toUpperCase(hexDigit) - 'A' + 10;
	            for (int j = 3; j >= 0; j--) {
	                if ((decimalValue - Math.pow(2, j)) >= 0) {
	                    binaryBuilder.append(1);
	                    decimalValue -= Math.pow(2, j);
	                } else {
	                    binaryBuilder.append(0);
	                }
	            }
	        }
	        return binaryBuilder.toString();
	    }  

}
