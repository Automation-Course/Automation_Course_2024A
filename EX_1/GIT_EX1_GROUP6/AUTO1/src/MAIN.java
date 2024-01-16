import java.util.Scanner;
public class MAIN {

	static Scanner sc = new Scanner (System.in);
	public static void main(String[] args) {

		int input=1;// to begin the program
		while (input!= 48)  {// beginning with asciivalue
			System.out.println("0. End Program");
			System.out.println("1. 2 ->16");
			System.out.println("2. 16->2");
			System.out.println("choose an option");
			String nu= sc.nextLine();// input of number

			char charInput=nu.charAt(0);
			int turnToascii = (int)charInput;
			input=turnToascii; 

			if((input>=48 && input<=57) && nu.length()<=1) { //check that the input is digit with just 1 char

				if ((input >=48)&& (input <=50)) { //check the input is one of the menu's options

					switch (input) {

					case 48 : //if the userInput equal to 0
						System.out.print("End Program. Goodbye!");
						break;//case0

					case 49: // 2->16

						System.out.print("Enter a Binary number: ");
						String binaryInput = sc.nextLine();

						if (isValidBinary(binaryInput)) { // Check if the input is a valid Binary number

							System.out.println("Hex representation: " + BinaryToHex(binaryInput)); // Show the Hex Num
						}
						else { //isn't a valid Binary number
							System.out.println("Error: This is not a binary number.");
						}

						break;//case1


					case 50:
						System.out.println("Enter a hexadecimal number: ");
						String hexInput = sc.nextLine();
						if (isValidHex(hexInput)) { // Check if the input is a valid hexadecimal number
							System.out.println("Binary representation: " + hexToBinary(hexInput)); // Show the binary Num
						}
						else { //isn't a valid hexadecimal number
							System.out.println("Error: This is not a hexadecimal number.");
						}
						break;//case2

					} //switch
				}//if
				else //invalid option (0-2)
					System.out.println("invalid input, try again");
			}
			else
			{
				System.out.println("invalid input, try again");
				input=1; //restart the choice
			}

		}//while


	} //maim

	//////////////////////////////////////////////////////////////////////////


	private static boolean isValidBinary(String input) { // check if the string is a valid Binary number (only 0/1)
		for (char ch : input.toCharArray()) { //running on array to check validation
			if ((ch!='0' && ch!='1')) {
				return false;
			}
		}
		return true; // If all characters are valid, return true
	}



	private static String BinaryToHex(String binary) {
		String hexResult = "";

		int remainingBits = binary.length() % 4; 

		// If there are remaining bits, process them first
		if (remainingBits > 0) {
			String firstSegment = binary.substring(0, remainingBits); //took the char in the first place till the remaining
			int decimalValue = 0;
			for (int j = 0; j < firstSegment.length(); j++) { 
				//loop that take every char change it to digit and multiply it with the pow of the place
				int digit= firstSegment.charAt(j)-'0';//change to int
				decimalValue +=digit* Math.pow(2, (remainingBits-1)-j); 
			}
			hexResult += (char) (decimalValue < 10 ? '0' + decimalValue : 'A' + decimalValue - 10);
			//convert the character to a numeric value
		}

		// Process the rest of the binary digits in sets of 4
		for (int i = remainingBits; i < binary.length(); i += 4) { //jump between 4 char
			String binarySegment = binary.substring(i, i + 4);

			int decimalValue = 0;
			for (int j = 0; j < binarySegment.length(); j++) {
				//loop that take every char change it to digit and multiply it with the pow of the place
				int digit= binarySegment.charAt(j)-'0';
				decimalValue +=digit* Math.pow(2, 3-j);
			}

			hexResult += (char) (decimalValue < 10 ? '0' + decimalValue : 'A' + decimalValue - 10); 
			//check if the value should be a number (0) or a letter (A)
		}

		return hexResult;
	}


	private static boolean isValidHex(String input) { 
		// check if the string is a valid hexadecimal number (digit (0-9) or a letter between A-F)
		for (char ch : input.toCharArray()) {
			if (!(Character.isDigit(ch) ||  (ch >= 'A' && ch <= 'F'))) {
				return false;
			}
		}
		return true; // If all characters are valid, return true
	}//end isValidHex

	private static String hexToBinary(String hexadecimal) {
		String binaryResult = "";

		for (int i = 0; i < hexadecimal.length(); i++) { // Iterate through each character of the hexadecimal input
			char hexDigit = hexadecimal.charAt(i);
			// Convert the hexadecimal digit to decimal value
			int decimalValue;
			if (hexDigit >= '0' && hexDigit <= '9') {
				decimalValue = hexDigit - '0'; //change to int
			} else {
				decimalValue = hexDigit - 'A' + 10;
			}

			String binaryRepresentation = "";

			while (decimalValue > 0) { // Convert the decimal value to binary representation
				int bit = decimalValue % 2; // Get the remainder of the division by 2
				binaryRepresentation = bit + binaryRepresentation;
				decimalValue = decimalValue / 2;
			}
			while (binaryRepresentation.length() < 4) { // add 0 in the begining if needed
				binaryRepresentation = '0' + binaryRepresentation;
			}
			binaryResult =binaryResult+ binaryRepresentation;
		}
		return binaryResult; // Return the final binary representation
	}//end hexToBinary

}//CLASS