def get_user_input():
    while True:
        # Get user input
        user_input = input("Enter a number in base 2 or 16 (or 'exit' to quit): ")

        # Check if the user wants to exit
        if user_input.lower() == 'exit':
            break

        # Check if the user entered anything
        if not user_input:
            print("No input provided. Please enter a number.")
            continue

        # Check if the input consists of only '0's
        if all(char == '0' for char in user_input):
            print("Please enter a number other than zero.")
            continue

        # Call the convert_base function
        convert_base(user_input)


def convert_base(user_input):
    # Remove the '0b' or '0x' prefix if present
    user_input = user_input.lstrip("0b").lstrip("0x")

    # Check if the input is a valid binary number
    if all(bit in '01' for bit in user_input):
        try:
            # Convert binary to decimal
            decimal_number = binary_to_decimal(user_input)
            hex_number = decimal_to_hexadecimal(decimal_number)

            # Print the result
            print(f"The number {user_input} in base 2 translates to {hex_number} in base 16.")
            return
        except ValueError:
            pass

    # Check if the input is a valid hexadecimal number
    if all(hex_digit.upper() in '0123456789ABCDEF' for hex_digit in user_input):
        try:
            # Convert hexadecimal to decimal
            decimal_number = hexadecimal_to_decimal(user_input)
            binary_number = decimal_to_binary(decimal_number)

            # Print the result
            print(f"The number {user_input} in base 16 translates to {binary_number} in base 2.")
            return
        except ValueError:
            pass

    # Prompt the user to enter a new number if not in base 2 or 16
    print("Number not in base 2 or 16. Please enter a new number.")


def binary_to_decimal(binary):
    """
    Converts a binary number to decimal.

    Parameters:
    binary (str): The binary number as a string.

    Returns:
    int: The decimal equivalent of the binary number.
    """
    decimal_number = 0
    power = len(binary) - 1

    for digit in binary:
        decimal_number += int(digit) * (2 ** power)
        power -= 1

    return decimal_number


def decimal_to_hexadecimal(decimal):
    """
    Converts a decimal number to hexadecimal.

    Parameters:
    decimal (int): The decimal number.

    Returns:
    str: The hexadecimal equivalent of the decimal number.
    """
    hex_digits = "0123456789ABCDEF"
    hex_number = ""

    while decimal > 0:
        remainder = decimal % 16
        hex_digit = hex_digits[remainder]
        hex_number = hex_digit + hex_number
        decimal //= 16

    return hex_number


def hexadecimal_to_decimal(hexadecimal):
    """
    Converts a hexadecimal number to decimal.

    Parameters:
    hexadecimal (str): The hexadecimal number as a string.

    Returns:
    int: The decimal equivalent of the hexadecimal number.
    """
    hex_digits = "0123456789ABCDEF"
    decimal_number = 0
    power = len(hexadecimal) - 1

    for digit in hexadecimal:
        decimal_number += hex_digits.index(digit.upper()) * (16 ** power)
        power -= 1

    return decimal_number


def decimal_to_binary(decimal):
    """
    Converts a decimal number to binary.

    Parameters:
    decimal (int): The decimal number.

    Returns:
    str: The binary equivalent of the decimal number.
    """
    binary_number = ""

    while decimal > 0:
        binary_digit = str(decimal % 2)
        binary_number = binary_digit + binary_number
        decimal //= 2

    return binary_number


# Call the get_user_input function
get_user_input()