import java.util.Scanner;

public class Calcu16To2 {

	public static String From16To2(String num)
	{
		if(num.length() == 0)
			throw new invalidInput("Please insert valid input");

		boolean flag = true; //  true if num is positive
		if(num.charAt(0) == '-' && num.length() > 1) {
			flag = false;
			num = num.substring(1);
		}
		else
			if(num.charAt(0) == '-')
				throw new invalidInput("Please insert valid input");

		for(int i=0 ; i<num.length(); i++)
		{
			if( !    ((num.charAt(i)>='0' && num.charAt(i)<='9')  ||  (num.charAt(i)>='A' && num.charAt(i)<='F')) )
				throw new invalidInput("Please insert valid input");
		}

		 String result = "";
		 
		 if (num.equals("0")) 
	            return "0000";
	         else 
	            num = num.replaceFirst("^0+", ""); // trim zeros from start
	        
		 
		    while (num.length() > 0) {
		        char current = num.charAt(0);
		        String binaryRepresentation = "";

		        if (current == '0')
		            binaryRepresentation = "0000";
		        else if (current == '1')
		            binaryRepresentation = "0001";
		        else if (current == '2')
		            binaryRepresentation = "0010";
		        else if (current == '3')
		            binaryRepresentation = "0011";
		        else if (current == '4')
		            binaryRepresentation = "0100";
		        else if (current == '5')
		            binaryRepresentation = "0101";
		        else if (current == '6')
		            binaryRepresentation = "0110";
		        else if (current == '7')
		            binaryRepresentation = "0111";
		        else if (current == '8')
		            binaryRepresentation = "1000";
		        else if (current == '9')
		            binaryRepresentation = "1001";
		        else if (current == 'A')
		            binaryRepresentation = "1010";
		        else if (current == 'B')
		            binaryRepresentation = "1011";
		        else if (current == 'C')
		            binaryRepresentation = "1100";
		        else if (current == 'D')
		            binaryRepresentation = "1101";
		        else if (current == 'E')
		            binaryRepresentation = "1110";
		        else if (current == 'F')
		            binaryRepresentation = "1111";

		        result += binaryRepresentation;
		        num = num.substring(1);
	
		    }

		    if (flag)
		        return result;
		    else
		        return "-" + result;
		}
	public static void main(String[] args) {
		System.out.println("Please insert a value:");
		Scanner sc = new Scanner(System.in);
		String userInput = sc.nextLine();
		userInput = userInput.toUpperCase();	
		System.out.println("Result: " + From16To2(userInput));
	}

}
