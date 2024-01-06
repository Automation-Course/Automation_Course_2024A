import java.math.BigInteger;
import java.util.Scanner;

public class Calcu2To16 {


	public static String From2To16(BigInteger num){

		boolean flag = true; // true if num is positive

		if (num.compareTo(BigInteger.ZERO) < 0) {
			num = num.abs();
			flag = false;
		}

		BigInteger x = num;
		while (x.compareTo(BigInteger.ZERO) > 0) {
			BigInteger digit = x.mod(BigInteger.TEN); // Get the last digit
			if (!(digit.equals(BigInteger.ZERO) || digit.equals(BigInteger.ONE))) {
				return "Invalid Input";
			}
			x = x.divide(BigInteger.TEN);
		}

		String result ="";

		if (num.equals(BigInteger.ZERO))
			return "0";

		while( (num.compareTo(BigInteger.ZERO) > 0))
		{

			int sum = 0;
			sum += num.mod(BigInteger.TEN).intValue();
			num = num.divide(BigInteger.TEN);

			sum += 2 * num.mod(BigInteger.TEN).intValue();
			num = num.divide(BigInteger.TEN);

			sum += 4 * num.mod(BigInteger.TEN).intValue();
			num = num.divide(BigInteger.TEN);

			sum += 8 * num.mod(BigInteger.TEN).intValue();
			num = num.divide(BigInteger.TEN);

			if(sum == 10)
				result = 'A' + result ;
			else if (sum == 11)
				result = 'B' + result;
			else if (sum == 12)
				result = 'C' + result;
			else if (sum == 13)
				result = 'D' + result;
			else if (sum == 14)
				result = 'E' + result;
			else if (sum == 15)
				result = 'F' + result;
			else result = String.valueOf(sum) + result;

		}
		if(flag)
			return result;
		else
			return "-" + result;
	}

	private static boolean isValidBinaryNumber(String num) {
		if(num.length() == 0)
			return false;

		if(num.charAt(0) == '-' && num.length() > 1) {
			num = num.substring(1);
		}
		else
			if(num.charAt(0) == '-')
				return false;

		for(int i=0 ; i<num.length(); i++)
		{
			if( !    ( num.charAt(i)=='0' || num.charAt(i)=='1')  )
				return false;
		}
		return true;
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Please insert a value:");
		String userInput = scanner.nextLine();
		if(!isValidBinaryNumber(userInput))
			System.out.println("Invalid input");
		else {
			BigInteger bigIntegerValue = new BigInteger(userInput);
			System.out.println("Result: " + From2To16(bigIntegerValue));


		}

	}
}
