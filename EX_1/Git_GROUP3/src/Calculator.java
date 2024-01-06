
import java.util.Scanner;
import java.math.BigInteger;

public class Calculator {

	 public static void main(String[] args) {
	        Scanner scanner = new Scanner(System.in);

	        boolean continueProgram = true;

	        while (continueProgram) {
	            printMenu();

	            try {
	                int choice = scanner.nextInt();
	                scanner.nextLine(); // Consume the newline character

	                switch (choice) {
	                    case 1:
	                        binaryToHexadecimal();
	                        break;
	                    case 2:
	                        hexadecimalToBinary();
	                        break;
	                    case 3:
	                        System.out.println("Exiting the program. Goodbye!");
	                        continueProgram = false;
	                        break;
	                    default:
	                        System.out.println("Invalid choice. Please choose a valid option.");
	                }
	            } catch (java.util.InputMismatchException e) {
	                // Handle the exception
	                System.out.println("Invalid input. Please enter a number.");
	                scanner.nextLine(); // Consume the invalid input to avoid an infinite loop
	            }
	        }
	        scanner.close();
	    }

	private static void hexadecimalToBinary() { //General pr
		System.out.println("Please insert a value:");
		Scanner sc = new Scanner(System.in);
		String userInput = sc.nextLine();
		userInput = userInput.toUpperCase();
		System.out.println("Result: " + hexadecimalToBinaryCul(userInput));
	}

	private static String hexadecimalToBinaryCul(String num) { // Function to convert hexadecimal to binary
		if (num.length() == 0)
			throw new invalidInput("Please insert valid input");

		boolean flag = true; // true if num is positive
		if (isNegativeHex(num)) {
			flag = false;
			num = num.substring(1);
		} else if (num.charAt(0) == '-')
			System.out.println("Invalid input");
		checkInput(num);

		String result = "";

		if (num.equals("0"))
			return "0000";
		else
			num = num.replaceFirst("^0+", ""); // trim zeros from start
		while (num.length() > 0) {
			char current = num.charAt(0);
			String binaryRepresentation = "";
			binaryRepresentation = hexToBinIîter(current);
			result += binaryRepresentation;
			num = num.substring(1);
		}
		if (flag)
			return result;
		else
			return "-" + result;
	}

	private static String hexToBinIîter(char current) { //convert hex value to binaty number
		if (current == '0')
			return "0000";
		else if (current == '1')
			return "0001";
		else if (current == '2')
			return "0010";
		else if (current == '3')
			return "0011";
		else if (current == '4')
			return "0100";
		else if (current == '5')
			return "0101";
		else if (current == '6')
			return "0110";
		else if (current == '7')
			return "0111";
		else if (current == '8')
			return "1000";
		else if (current == '9')
			return "1001";
		else if (current == 'A')
			return "1010";
		else if (current == 'B')
			return "1011";
		else if (current == 'C')
			return "1100";
		else if (current == 'D')
			return "1101";
		else if (current == 'E')
			return "1110";
		else if (current == 'F')
			return "1111";
		return "";

	}


	private static void checkInput(String num) {
		for (int i = 0; i < num.length(); i++) {
			if (!((num.charAt(i) >= '0' && num.charAt(i) <= '9') || (num.charAt(i) >= 'A' && num.charAt(i) <= 'F')))
				throw new invalidInput("Please insert valid input");
		}

	}

	private static boolean isNegativeHex(String num) {
		return (num.charAt(0) == '-' && num.length() > 1);
	}

	private static void binaryToHexadecimal() { // Function to convert binary to hexadecimal
		Scanner scanner = new Scanner(System.in);
		System.out.println("Please insert a value:");
		String userInput = scanner.nextLine();
		if (!isValidBinaryNumber(userInput))
			throw new invalidInput("Please insert valid input");
		else {
			BigInteger bigIntegerValue = new BigInteger(userInput);
			System.out.println("Result: " + binaryToHexadecimalCul(bigIntegerValue));
		}
	}

	private static String binaryToHexadecimalCul(BigInteger num) {
		boolean flag = true; // true if num is positive

		if (isNegativeBin(num)) {
			num = num.abs();
			flag = false;
		}
		BigInteger x = num;
		while (isPositiveBin(x)) {
			BigInteger digit = lastDigit(x); // Get the last digit
			if (!isBinDigit(digit)) {
				return "Invalid Input";
			}
			x = x.divide(BigInteger.TEN);
		}

		String result = "";

		if (num.equals(BigInteger.ZERO))
			return "0";

		while ((num.compareTo(BigInteger.ZERO) > 0)) {

			int sum = 0;
			sum += num.mod(BigInteger.TEN).intValue();
			num = num.divide(BigInteger.TEN);

			sum += 2 * num.mod(BigInteger.TEN).intValue();
			num = num.divide(BigInteger.TEN);

			sum += 4 * num.mod(BigInteger.TEN).intValue();
			num = num.divide(BigInteger.TEN);

			sum += 8 * num.mod(BigInteger.TEN).intValue();
			num = num.divide(BigInteger.TEN);

			result = convertSumToHex(sum) + result;
		}
		if (flag)
			return result;
		else
			return "-" + result;
	}

	private static String convertSumToHex(int sum) { //convert num to hex value
		// TODO Auto-generated method stub
		if (sum == 10)
			return "A";
		else if (sum == 11)
			return "B";
		else if (sum == 12)
			return "C";
		else if (sum == 13)
			return "D";
		else if (sum == 14)
			return "E";
		else if (sum == 15)
			return "F";
		else
			return String.valueOf(sum);
	}

	private static boolean isBinDigit(BigInteger digit) {
		// TODO Auto-generated method stub
		return (digit.equals(BigInteger.ZERO) || digit.equals(BigInteger.ONE));
	}

	private static BigInteger lastDigit(BigInteger x) { //returns last digit
		// TODO Auto-generated method stub
		return x.mod(BigInteger.TEN);
	}

	private static boolean isPositiveBin(BigInteger x) {
		// TODO Auto-generated method stub
		return (x.compareTo(BigInteger.ZERO) > 0);
	}

	private static boolean isNegativeBin(BigInteger num) { 
		return (num.compareTo(BigInteger.ZERO) < 0);
	}

	private static boolean isValidBinaryNumber(String num) {  //Function to check if the input is a valid binary number
		if (num.length() == 0)
			return false;

		if (num.charAt(0) == '-' && num.length() > 1) {
			num = num.substring(1);
		} else if (num.charAt(0) == '-')
			return false;

		for (int i = 0; i < num.length(); i++) {
			if (!(num.charAt(i) == '0' || num.charAt(i) == '1'))
				return false;
		}
		return true;
	}

	public static void printMenu() { // Function to print the conversion menu
		System.out.println("Welcome to the Base Converter!");
		System.out.println("Choose conversion direction:");
		System.out.println("1. Binary to Hexadecimal");
		System.out.println("2. Hexadecimal to Binary");
		System.out.println("3. Finish");
	}
}
