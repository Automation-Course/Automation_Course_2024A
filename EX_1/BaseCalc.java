import java.util.Scanner;
public class BaseCalc {
	static Scanner sc = new Scanner(System.in);
	
	public static String hexToBin(String hexnum) {
		if (hexnum.equals("0")) {
			return hexnum;
		}
		String res="";
		hexnum=removeZeros(hexnum);
		for (int i=0; i<hexnum.length(); i++) {
			if (changeToBin(hexnum.charAt(i)).equals("")) {
				return "Not a hex number";
			}
			res+=changeToBin(hexnum.charAt(i));
		}
		return res;
	}
	//the function removes the unnecessary zeros at the start of the number
	public static String removeZeros(String s) {
		while (s.charAt(0)=='0' && s.length()>1) {
			s=s.substring(1);
		}
		return s;
	}

	//returns the hex digit as a bin number
	public static String changeToBin(char c) {
		String s="";
		if (c=='0') {
			return s="0000";
		}
		if (c=='1') {
			return s="0001";
		}
		if (c=='2') {
			return s="0010";
		}
		if (c=='3') {
			return s="0011";
		}
		if (c=='4') {
			return s="0100";
		}
		if (c=='5') {
			return s="0101";
		}
		if (c=='6') {
			return s="0110";
		}
		if (c=='7') {
			return s="0111";
		}
		if (c=='8') {
			return s="1000";
		}
		if (c=='9') {
			return s="1001";
		}
		if (c=='A' || c=='a') {
			return s="1010";
		}
		if (c=='B' || c=='b') {
			return s="1011";
		}
		if (c=='C' || c=='c') {
			return s="1100";
		}
		if (c=='D' || c=='d') {
			return s="1101";
		}
		if (c=='E' || c=='e') {
			return s="1110";
		}
		if (c=='F' || c=='f') {
			return s="1111";
		}
		return s;
	}

	public static String BinToHex(String binNum) {
		binNum=removeZeros(binNum);
		int add=0;
		if (binNum.length()%4!=0) {
			add=4-binNum.length()%4;
		}
		while (add>0) {
			binNum="0"+binNum;
			add--;
		}
		String res="";
		for (int i=0; i<binNum.length()-3; i+=4) {
			String num=binNum.substring(i, i+4);
			if (changeToHex(num).equals("")) {
				return "Not a binary number";
			}
			res+=changeToHex(num);
		}
		return res;
	}
	
	//returns the bin number as a hex digit
	public static String changeToHex(String num) {
		String s="";
		if (num.equals("0000")){
			return s="0";
		}
		if (num.equals("0001")){
			return s="1";
		}
		if (num.equals("0010")){
			return s="2";
		}
		if (num.equals("0011")){
			return s="3";
		}
		if (num.equals("0100")){
			return s="4";
		}
		if (num.equals("0101")){
			return s="5";
		}
		if (num.equals("0110")){
			return s="6";
		}
		if (num.equals("0111")){
			return s="7";
		}
		if (num.equals("1000")){
			return s="8";
		}
		if (num.equals("1001")){
			return s="9";
		}
		if (num.equals("1010")){
			return s="A";
		}
		if (num.equals("1011")){
			return s="B";
		}
		if (num.equals("1100")){
			return s="C";
		}
		if (num.equals("1101")){
			return s="D";
		}
		if (num.equals("1110")){
			return s="E";
		}
		if (num.equals("1111")){
			return s="F";
		}
		return s;
	}
	
	//prints the menu
	public static void menuPrint() {
		System.out.println(
				 "Please choose an option. \n"
				+ "1.Hexdecimal to Binary \n"
				+ "2.Binary to Hexdecimal \n"
				+ "3.Exit");
	}
	
	//check if the input is in the menu options
	public static boolean isInMenu(String s) {
		if (!(s.equals("1")) && !(s.equals("2")) && !(s.equals("3"))) {
			return true;
		}
		System.out.println("This is not a valid option please enter again");
		return false;
	}
	//check if the input is empty
	public static boolean isEmpty(String s) {
		if (s.length()==0) {
			System.out.println("please enter a number");
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) {
		String x="";
		System.out.println("Welcome to the Base conversion Calculator");
		//continues the program
		while (!(x.equals("3"))) {
		menuPrint();
		x=sc.nextLine();
		while(!isInMenu(x)) {
			x=sc.nextLine();
		}
		//finishes the program
		if (x.equals("3")){
			System.out.println("Thank You GoodBye");
			break;
		}
		String y="";
		while(isEmpty(y)) {
		y=sc.nextLine();
		}
		//converting the program to the users choice
		if (x.equals("1")) {
			System.out.println(hexToBin(y));
		}
		if (x.equals("2")) {
			System.out.println(BinToHex(y));
		}
		}
	}

}
