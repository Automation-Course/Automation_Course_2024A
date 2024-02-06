import java.util.Scanner;
public class Ex1 {
	static Scanner sc = new Scanner(System.in);
	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		PrintMenu();
		String inputUser=sc.next();
		if(inputUser.equals("3"))
		{
			System.out.println("Bye, Thank you next");
		}
		while(!inputUser.equals("3")) 
		{
			if(inputUser.equals("1") || inputUser.equals("2") || inputUser.equals("3"))
			{
				if (inputUser.equals("1")) 
					//Convert hexadecimal to binary base
				{
					System.out.print("Enter an hexadecimal number\r\n");
					String hexInput=sc.next();
					while(!CheckHexInput(hexInput))
					{
						System.out.print("Invalid input\r\n"
								+ "please enter an hexadecimal number\r\n");
						hexInput=sc.next();
					}
					System.out.print(ConvertHexToBin(hexInput)+"\n");
					PrintMenu();
					inputUser=sc.next();
				}

				if (inputUser.equals("2")) 
					//Convert binary to hexadecimal base
				{
					System.out.print("Enter an binary number\r\n");
					String binInput=sc.next();
					while(!CheckBinInput(binInput))
					{
						System.out.print("Invalid input\r\n"
								+ "please enter a binary number\r\n");
						binInput=sc.next();
					}
					System.out.print(ConvertBinToHex(PrepToBin(binInput))+"\n");
					PrintMenu();
					inputUser=sc.next();	
				}
				if(inputUser.equals("3"))
				{
					System.out.println("Bye, Thank you next");
				}
			}
			else 
			{
				System.out.println("Please enter a number between 1-3");
				PrintMenu();
				inputUser=sc.next();	

			}
		}

	}//End main

	public static void PrintMenu()
	{
		System.out.print("What would you like to do?\r\n"
				+ "1.Convert hexadecimal to binary base\r\n"
				+ "2.Convert binary to hexadecimal base\r\n"
				+ "3.End program \r\n"
				+ "Please pick an option (1/2/3)\r\n");
	}

	public static String TableHexToBin(char input)
	{
		if (input == '0')
		{
			return "0000";
		}
		if (input == '1')
		{
			return "0001";
		}
		if (input == '2')
		{
			return "0010";
		}
		if (input == '3')
		{
			return "0011";
		}
		if (input == '4')
		{
			return "0100";
		}
		if (input == '5')
		{
			return "0101";
		}
		if (input == '6')
		{
			return "0110";
		}
		if (input == '7')
		{
			return "0111";
		}
		if (input == '8')
		{
			return "1000";
		}
		if (input == '9')
		{
			return "1001";
		}
		if (input == 'A')
		{
			return "1010";
		}
		if (input == 'B')
		{
			return "1011";
		}
		if (input == 'C')
		{
			return "1100";
		}
		if (input == 'D')
		{
			return "1101";
		}
		if (input == 'E')
		{
			return "1110";
		}

		return "1111";//if F
	}


	public static String TableBinToHex(String input)
	{
		if (input.equals("0000"))
		{
			return "0";
		}
		if (input.equals("0001"))
		{
			return "1";
		}
		if (input.equals("0010"))
		{
			return "2";
		}
		if (input.equals("0011"))
		{
			return "3";
		}
		if (input.equals("0100"))
		{
			return "4";
		}
		if (input.equals("0101"))
		{
			return "5";
		}
		if (input.equals("0110"))
		{
			return "6";
		}
		if (input.equals("0111"))
		{
			return "7";
		}
		if (input.equals("1000"))
		{
			return "8";
		}
		if (input.equals("1001"))
		{
			return "9";
		}
		if (input.equals("1010"))
		{
			return "A";
		}
		if (input.equals("1011"))
		{
			return "B";
		}
		if (input.equals("1100"))
		{
			return "C";
		}
		if (input.equals("1101"))
		{
			return "D";
		}
		if (input.equals("1110"))
		{
			return "E";
		}
		return "F";//if 1111
	}
	public static Boolean CheckHexInput (String input) 
	{
		for( int i=0; i<input.length(); i++)
		{
			if ((input.charAt(i) < '0' || input.charAt(i) > '9' ) && 
					(input.charAt(i) < 'A' || input.charAt(i) > 'F'))
				return false;
		}
		return true;
	}


	public static Boolean CheckBinInput (String input) 
	{
		for( int i=0; i<input.length(); i++)
		{
			if (!(input.charAt(i) == '0' || input.charAt(i) == '1' )) 
				return false;
		}
		return true;
	}

	public static String ConvertHexToBin(String input)
	{
		String ans ="";
		for (int i = 0; i < input.length(); i++)
		{
			ans = ans + TableHexToBin(input.charAt(i));
		}
		return ans;
	}

	public static String ConvertBinToHex(String input)
	{
		String ans ="";
		for (int i = 0, j=0; j < input.length()/4; i=i+4, j++)
		{
			ans = ans + TableBinToHex(input.substring(i,i+4));
		}
		return ans;
	}


	public static String PrepToBin(String input) 
	{
		String ans ="";
		if (input.length()%4 == 0)
		{
			ans = input;
		}
		if (input.length()%4 == 1)
		{
			ans = "000"+input;
		}
		if (input.length()%4 == 2)
		{
			ans = "00"+input;
		}
		if (input.length()%4 == 3)
		{
			ans = "0"+input;
		}
		return ans;		
	}

}


