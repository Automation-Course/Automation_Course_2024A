
def hexedizimalTobinar(hex_number):
    """Converts a hexadecimal number to binary."""

    binary_result = ""
    hex_number = hex_number.upper()  # Convert to uppercase for case-insensitivity

    """Table of transitions between bases 16-->2"""
    for i in hex_number:
        if i == "0":
            binary_result = binary_result + "0000"
        if i == "1":
            binary_result += "0001"
        if i == "2":
            binary_result += "0010"
        if i == "3":
            binary_result += "0011"
        if i == "4":
            binary_result += "0100"
        if i == "5":
            binary_result += "0101"
        if i == "6":
            binary_result += "0110"
        if i == "7":
            binary_result += "0111"
        if i == "8":
            binary_result += "1000"
        if i == "9":
            binary_result += "1001"
        if i == "A":
            binary_result += "1010"
        if i == "B":
            binary_result += "1011"
        if i == "C":
            binary_result += "1100"
        if i == "D":
            binary_result += "1101"
        if i == "E":
            binary_result += "1110"
        if i == "F":
            binary_result += "1111"

    """display the number without 0 at the beginning"""
    if binary_result == '0000':
        print(0)
    else:
        for i in binary_result:
            if i != "0":
                print(binary_result)
                break
            else:
                """ return the string without the first char """
                binary_result = binary_result[1:] 



def TransictionBinaryToHexe(binary_number):
    """Table of transitions between bases 2-->16"""

    hexe_result = ""
    if binary_number == "0000":
        hexe_result = "0"
    if binary_number == "0001":
        hexe_result = "1"
    if binary_number == "0010":
        hexe_result = "2"
    if binary_number == "0011":
        hexe_result = "3"
    if binary_number == "0100":
        hexe_result = "4"
    if binary_number == "0101":
        hexe_result = "5"
    if binary_number == "0110":
        hexe_result = "6"
    if binary_number == "0111":
        hexe_result = "7"
    if binary_number == "1000":
        hexe_result = "8"
    if binary_number == "1011":
        hexe_result = "9"
    if binary_number == "1010":
        hexe_result = "A"
    if binary_number == "1011":
        hexe_result = "B"
    if binary_number == "1100":
        hexe_result = "C"
    if binary_number == "1101":
        hexe_result = "D"
    if binary_number == "1110":
        hexe_result = "E"
    if binary_number == "1111":
        hexe_result = "F"
    return hexe_result

def split_string(input_string, chunk_size):
    """split the binary number to chunk of 4 items"""
    reversed_string = input_string[::-1] 
    chunks = [reversed_string[i:i + chunk_size] for i in range(0, len(reversed_string), chunk_size)] 
    #loop that includes steps which is the chunk size
    return [chunk[::-1] for chunk in chunks[::-1]]


def binarTohexedizimal(binar_number):
    """Converts a binar number to hexedizimal."""
    hexedizimal_result = ""
    chunked_binary_number = split_string(binar_number,4)
    for chunk in chunked_binary_number:
        if len(chunk) == 4:
            hexedizimal_result += TransictionBinaryToHexe(chunk)
        else:
            new_Chunk = chunk.zfill(4)   # adds zeros on the left until reaches 4 characters
            hexedizimal_result += TransictionBinaryToHexe(new_Chunk)

    print(hexedizimal_result)


def validate_Hex_input(user_input):
    "validation input"
    allowed_characters = {"0",'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'E', 'e',
                          'f', 'F'}
    for char in user_input:
        if char not in allowed_characters:
            return False
    return True

def validate_Bin_input(user_input):
    "validation input"
    allowed_characters = {"0",'1' }
                        
    for char in user_input:
        if char not in allowed_characters:
            return False
    return True

def zero_Check(binary_result):
     """check for unnessasery zeroes at the first input"""
     for i in binary_result:
             if i != "0":
              return binary_result
             else:
                """ return the string without the first char """
                binary_result = binary_result[1:] 

                """if the input inclode only zeros"""
                if binary_result == "":
                  return "0"

def main_function_Calculator():
    "The Calculator"
    need_to_exit = False
    while not need_to_exit:
        user_input = input("""Hello, you have arrived at the best base calculator in the world 
        1: hexadecimal base -> binary base
        2: binary base -> hexadecimal base 
        3: Exit \nPlease enter your choise: """)
        if user_input == "1":
            # Request input from the user until valid input is provided
            new_user_input = input("Select a number ")
            if validate_Hex_input(new_user_input):
                hexedizimalTobinar(new_user_input)
            else:
                print("Invalid input. Hexdecimal number must be with digits 0-9 and A-F")


        elif user_input == "2":
            # Request input from the user until valid input is provided
            new_user_input = input("Select a number ")
            
            if validate_Bin_input(new_user_input):
                new_user_input = zero_Check(new_user_input)      
                binarTohexedizimal(new_user_input)
            else:
                print("Invalid input. The input can only include 0,1")

        elif user_input == "3":
            print("Exiting the program. Goodbye!")
            need_to_exit = True

        else: print("Invalid input. You can either press 1 or 2")


main_function_Calculator()