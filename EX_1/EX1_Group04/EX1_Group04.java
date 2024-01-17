
import java.util.Scanner;

public class EX1_Group04 {

	public static void main(String[] args) {

		Scanner scanner = new Scanner(System.in);
		boolean flag = false;

		while (!flag) { // a loop that will not end until the user will insert a valid value.
			System.out.println("Please enter 1 for converting binar to hexadecimal \nor enter"
					+ " 2 for converting hexadecimal to binar");
			int input = 0;
			try {
				input = scanner.nextInt();
				scanner.nextLine();
			} catch (Exception e) {
				scanner.next(); // clears scanner
			}
			if (input != 1 && input != 2) { // if the value is not 1 or 2
				System.out.println("unvalid input");
			}
			if (input == 1) { // the user chose binary to hexadecimaly.
				boolean BinFlag = false;
				while (!BinFlag) {
					System.out.println("Please enter your Binar number");
					String inputBin = scanner.nextLine();

					if (CheckBin(inputBin)) {
						try {
							String OutputHexa = BinToHexa(inputBin);
							System.out.println("The number in hexadecimal is: " + OutputHexa);
						} catch (Exception e) {
							System.out.println("unvalid input");
							scanner.next(); // clears scanner
						}
						BinFlag = true;
						flag = true;
					}
				}
			}
			if (input == 2) {// the user chose hexadecimaly to binary
				boolean HexFlag = false;
				while (!HexFlag) {
					System.out.println("Please enter your Hexadecimal number");
					String inputHexa = scanner.nextLine();

					if (CheckHexa(inputHexa)) {
						try {
							String OutputBin = HexaToBin(inputHexa);
							System.out.println("The number in Binar is: " + OutputBin);
						} catch (Exception e) {
							System.out.println("unvalid input");
							scanner.next(); // clears scanner
						}
						HexFlag = true;
						flag = true;
					}
				}
			}
		}
	}

	public static boolean CheckHexa(String Hexa) {
		if (Hexa.isEmpty()) {
			System.out.println("Empty input");
			return false;
		}
		if (Hexa.length() > 32) {
			System.out.println("unvalid input. Hexadecimal can be between 0 to FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
			return false;
		}
		for (int i = 0; i < Hexa.length(); i++) {
			if (!(Hexa.charAt(i) >= '0' && Hexa.charAt(i) <= '9') && !(Hexa.charAt(i) >= 'A' && Hexa.charAt(i) <= 'F')
					&& !(Hexa.charAt(i) >= 'a' && Hexa.charAt(i) <= 'f')) {
				System.out
						.println("unvalid input. Hexadecimal number have letters from A to F and numbers from 0 to 9");
				return false;
			}
		}
		return true;
	}

	public static String HexaToBin(String hexNum) {
		String binNum = "";
		binNum = convert(hexNum, binNum);
		binNum = cutLeadingZeros(binNum);
		return binNum;
	}

	public static String convert(String hexNum, String binNum) { // contains the loop that scan the string and call all
																	// the methods.
		for (int i = 0; i <= hexNum.length() - 1; i++) {
			String subChar = cutIntoSub(hexNum, i);
			String fourDigitsToAdd = "";
			fourDigitsToAdd = conHexCharToBin(subChar);
			binNum += fourDigitsToAdd;
			// addDigitsToBinNum(binNum, fourDigitsToAdd); // maybe we dont need this one
		}
		return binNum;
	}

	public static String cutIntoSub(String hexNum, int i) { // cuts the last char of the hex number to a divided string
		String thisChar = "";
		thisChar = String.valueOf(hexNum.charAt(i));
		return thisChar;
	}

	public static String conHexCharToBin(String thisChar) { // converts one hex char to 4 digits binary number (String)
		String fourDigBin = "";
		String hexPos = "0123456789ABCDEFabcdef";
		int sumOfChar = 0; // holds the decimal value of the char
		for (int i = 0; i < hexPos.length(); i++) { // finds the value of the specipic char in decimal base.
			// if(String.valueOf(hexPos.charAt(i)) == thisChar){
			if (hexPos.charAt(i) == thisChar.charAt(0)) {
				sumOfChar = i;
			}
		}
		int j = 3; // represent the power of 2 we will be using for the convertion
		while (sumOfChar >= 0 && j >= 0) { // converts the decimal value to binary String made by 4 digits
			if (Math.pow(2, j) <= sumOfChar) {
				sumOfChar -= Math.pow(2, j);
				fourDigBin += "1";
			} else {
				fourDigBin += "0";
			}
			j--;
		}
		return fourDigBin;
	}

	public static String addDigitsToBinNum(String originalBinNum, String fourDigToAdd) { // adds the current binary
																							// digits to the main string
		originalBinNum = originalBinNum + fourDigToAdd;
		return originalBinNum;
	}

	public static String cutLeadingZeros(String binNum) { // cutting the leading zeros from the binary number
		while (binNum.charAt(0) == '0') {
			binNum = binNum.substring(1, binNum.length());
		}
		return binNum;
	}

	public static boolean CheckBin(String BinN) {
		if (BinN.isEmpty()) {
			System.out.println("Empty input");
			return false;
		}
		for (int i = 0; i < BinN.length(); i++) {
			if (BinN.charAt(i) != '0' && BinN.charAt(i) != '1') {
				System.out.println("unvalid input. a Binary number have only 1/0");
				return false;
			}
		}
		return true;
	}

	public static String BinToHexa(String binNum) {

		binNum = checkLength(String.valueOf(binNum));

		String hexNum = "";
		hexNum = indexToVal(binNum, hexNum);
		return hexNum;
	}

	public static String checkLength(String binNum) { // check if the bin number length divide by 4 and fix it
		int len = binNum.length();
		while (binNum.length() % 4 != 0) {
			binNum = "0" + binNum;
		}
		return binNum;
	}

	public static String indexToVal(String binNum, String hexNum) { // divide the bin num to small parts of 4 and calc
																	// them
		for (int i = binNum.length(); i > 0; i -= 4) {
			String fourDig = binNum.substring(i - 4, i);
			int currentDig = binToHexCon(fourDig); // call convert calc;
			String add = hexFinder(currentDig);
			hexNum = add + hexNum;
		}
		return hexNum;
	}

	public static Integer binToHexCon(String fourDig) { // calc for every num the value of his index and sum
		int power = 3;
		int sum = 0;
		for (int i = 0; i < 4; i += 1) {
			if (fourDig.charAt(i) == 49) { // one is 49 ascii table
				sum += Math.pow(2, power);
			}
			power -= 1;
		}
		return sum;
	}

	public static String hexFinder(int sum) {
		String hexVals = "0123456789ABCDEF";
		String theHexVal = String.valueOf(hexVals.charAt(sum));
		return theHexVal;
	}

}