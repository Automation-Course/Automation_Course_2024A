def binary_to_hex(binary):
    hex_result = ""
    binary = binary.zfill((len(binary) // 4 + 1) * 4)  # Pad the binary string to make its length a multiple of 4
    for i in range(0, len(binary), 4):
        nibble = binary[i:i + 4]  # taking 4 digits each time
        hex_digit = decimal_to_hex(binary_to_decimal(nibble)) # decimal to binary and then from decimal to hex
        hex_result += hex_digit
    return hex_result.upper()

def hex_to_binary(hex_string):
    binary_result = ""
    for hex_digit in hex_string:
        binary_result += decimal_to_binary(hex_to_decimal(hex_digit)).zfill(4) # zfill to get 4 digits for each number
    return binary_result

def decimal_to_hex(decimal):
    hex_value = ""
    while decimal > 0:
        rem = decimal % 16
        if rem < 10:
            hex_value = str(rem) + hex_value
        else: # is between A to F
            hex_value = chr(ord('A') + rem - 10) + hex_value # getting the value from ascii table as a char and adding it to the string
        decimal = decimal // 16
    return hex_value

def hex_to_decimal(hex_char):
    if '0' <= hex_char <= '9':
        last_val = ord(hex_char) - ord('0') # ascii value of '0' is 48 (by subtracting zero, we get the original digit)
    elif 'a' <= hex_char <= 'f':
        last_val = ord(hex_char) - ord('a') + 10
    elif 'A' <= hex_char <= 'F':
        last_val = ord(hex_char) - ord('A') + 10
    return last_val

def binary_to_decimal(binary):
    decimal_value = 0
    binary = binary[::-1]  # reverse the binary string for easier calculation
    for i in range(len(binary)):
        if binary[i] == '1':
            decimal_value += 2 ** i # power in position
    return decimal_value

def decimal_to_binary(decimal):
    binary_value = ""
    while decimal > 0:
        binary_value = str(decimal % 2) + binary_value # adding the reminer to the string
        decimal = decimal // 2 # to get a complete number
    return binary_value

def main():
    choice = 0
    while choice != 3: # if one of the options is not exit
        print("Please select your option:\n1. Binary to Hexadecimal\n2. Hexadecimal to Binary\n3. Exit")
        try:
            choice = int(input())
            if choice == 1:
                binary_input = input("Enter a binary number: ")
                if all(bit in "01" for bit in binary_input): # checking valid values
                    hex_result = binary_to_hex(binary_input)
                    print(f"Hexadecimal: {hex_result}") # printing the final answer
                else:
                    print("Invalid input! Please enter a binary number.")
            elif choice == 2:
                hex_input = input("Enter a hexadecimal number: ")
                if all(c.upper() in "0123456789ABCDEF" for c in hex_input): # checking valid values
                    binary_result = hex_to_binary(hex_input.upper())
                    print(f"Binary: {binary_result}") # printing the final answer
                else:
                    print("Invalid input! Please enter a hexadecimal number.")
            elif choice == 3:
                print("Goodbye!")
            else:
                print("Invalid choice!")
        except ValueError:
            print("Invalid input! Please enter an integer.")

if __name__ == "__main__":
    main()
