
package automation;
import java.util.Scanner;


public class ex1 {

	static Scanner sc = new Scanner(System.in);

	// Base 2 -----> Base 16

	public static void convertBase2ToBase16 () {
		String userInput;

		System.out.println("What would you like to convert from base 2 to base 16?");
		userInput = getBinary(sc.nextLine());

		System.out.println(toBase16(userInput));

	}

	public static String getBinary(String s) //The function Perceiving binary number
	{
		String userInput = s;
		while (!isBinary(userInput)) {
			System.out.println("not binary, please insert a binary number");
			userInput = sc.nextLine();
		}

		return userInput;
	}

	public static boolean isBinary(String s) { //base 2 checking
		boolean isBinary=true;

		for (int i=0 ; i<s.length() ; i++) {

			if (!(s.charAt(i) == '0' || s.charAt(i)== '1')) {
				isBinary=false;	
				break;
			}
		}
		return isBinary;
	}

	public static String toBase16(String input) { //The function gets number in base 2 and returns base 16
		String inputDivide4;
		int numberOfIterations;
		String last4Digits;
		String answer="";


		inputDivide4=divideToFourWithoutModulo(input);
		numberOfIterations=inputDivide4.length()/4 ;


		for( int i=0 ; i<numberOfIterations ; i++)
		{
			last4Digits=inputDivide4.substring(inputDivide4.length()-4);     
			answer=convert4DigitsFromBase2ToBase16(last4Digits)+answer;        
			inputDivide4=inputDivide4.substring(0, inputDivide4.length()-4);  //Remove last 4 digits

		}

		return answer;
	}

	public static String divideToFourWithoutModulo(String s) { //The function gets number and adds 0 in left until it divide to 4 without modulo
		int length = s.length();
		while (length % 4 != 0) {
			s = "0" + s;
			length = s.length(); // Update the length after adding a zero.
		}
		return s; // Return the modified string.
	}


	public static char convert4DigitsFromBase2ToBase16(String number) { 
		int answer;
		answer = 1 * Character.getNumericValue(number.charAt(3)) +
				2 *  Character.getNumericValue(number.charAt(2)) + 
				4 *  Character.getNumericValue(number.charAt(1)) +
				8 *  Character.getNumericValue(number.charAt(0)) ;


		if (answer > 9) {
			if (answer == 10)
				return 'A';
			if (answer == 11)
				return 'B';
			if (answer == 12)
				return 'C';
			if (answer == 13)
				return 'D';
			if (answer == 14)
				return 'E';
			if (answer == 15)
				return 'F';
		} else
			return (char) (answer + '0'); //convert from integer to char

		return 0;
	}  

	// Base 16 -----> Base 2

	public static void convertBase16ToBase2()
	{
		String userInput;
		System.out.println("What would you like to convert from base 16 to base 2?");
		userInput=getBase16(sc.nextLine());
		System.out.println(cutZero(toBase2(userInput)));
	}


	public static String cutZero (String s)// to move from 16 to 2 cut the zero in the start
	{
		int firstOneIndex= s.indexOf("1");
		if (firstOneIndex == -1)
			return "";
		String result = s.substring(firstOneIndex);
		return result;
	}

	public static String toBase2(String input) //The function gets number in base 16 and returns to base 2
	{
		String answer="";
		char lastDigit;
		int numberOfIterations;

		numberOfIterations=input.length();


		for(int i=0 ; i<numberOfIterations; i++)
		{
			lastDigit=input.charAt(input.length()-1);
			answer=convetDigitInBase16ToBase2(lastDigit)+answer;
			input=input.substring(0,input.length()-1);
		}
		return answer;
	}


	public static String getBase16(String s)//The function Perceiving number in Base 16
	{
		String userInput=s;
		while (!isBase16(userInput))
		{
			System.out.println("not base16, please insert a base 16 number");
			userInput=sc.nextLine();
		}
		return userInput;
	}


	public static boolean isBase16(String s)//base 16 checking
	{
		boolean isBase16=true;

		for (int i=0 ; i<s.length() ; i++)
		{
			if (!(s.charAt(i)=='0'||s.charAt(i)=='1'||s.charAt(i)=='2'||s.charAt(i)=='3'||s.charAt(i)=='4'||s.charAt(i)=='5'||s.charAt(i)=='6'||s.charAt(i)=='7'
					||s.charAt(i)=='8'||s.charAt(i)=='9'||s.charAt(i)=='A'||s.charAt(i)=='B'||s.charAt(i)=='C'||s.charAt(i)=='D'||s.charAt(i)=='E'||s.charAt(i)=='F'))
			{
				isBase16=false;
				break;
			}
		}
		return isBase16;
	}


	public static String convetDigitInBase16ToBase2 (char digitInBase16)
	{
		String toBase2="";

		if (digitInBase16=='0')
			toBase2="0000";
		if (digitInBase16=='1')
			toBase2="0001";
		if (digitInBase16=='2')
			toBase2="0010";
		if (digitInBase16=='3')
			toBase2="0011";
		if (digitInBase16=='4')
			toBase2="0100";
		if (digitInBase16=='5')
			toBase2="0101";
		if (digitInBase16=='6')
			toBase2="0110";
		if (digitInBase16=='7')
			toBase2="0111";
		if (digitInBase16=='8')
			toBase2="1000";
		if (digitInBase16=='9')
			toBase2="1001";
		if (digitInBase16=='A')
			toBase2="1010";
		if (digitInBase16=='B')
			toBase2="1011";
		if (digitInBase16=='C')
			toBase2="1100";
		if (digitInBase16=='D')
			toBase2="1101";
		if (digitInBase16=='E')
			toBase2="1110";
		if (digitInBase16=='F')
			toBase2="1111";

		return toBase2;

	}
	public static void whatBaseToConvert ()
	{
		System.out.println("which base you want to convert from?");
		System.out.println("1.Base16---->Base2");
		System.out.println("2.Base2---->Base16");
		int answer = sc.nextInt();
		
		if (answer!=1 && answer!=2) {
			System.out.println("please choose 1 or 2");
			whatBaseToConvert ();
		}
		else {
		if (answer==1)
			convertBase16ToBase2();
		if (answer==2)
			convertBase2ToBase16();
		}
	}



	public static void main(String[] args) {

		whatBaseToConvert();




	}//main
} //class

