# automation-exe-1 README

## Introduction

This README provides instructions for using the automation-exe-1 tool, designed for converting numbers between binary, hexadecimal, and decimal bases. The tool supports both 16-to-binary and 2-to-hexadecimal conversions.

## Usage

1. **Input:**
   - Enter a number.
   - Choose between 16, 2, or X:
     - If 16 is selected: convert from hexadecimal to binary.
     - If 2 is selected: convert from binary to hexadecimal.
     - If X is selected: exit the system.

2. **If 2 is selected:**
   1. Validate the input to ensure it is a valid binary number.
   2. If valid, check if the number of digits is divisible by 4; if not, pad zeros to the left.
   3. Define values:
      - BitPos: position within the group of 4 bits.
      - StartPos: ensure all digits in the number are processed.
      - hexString: resulting hexadecimal number.
   d. For each group of 4 bits:
      - Raise 2 to the power of the bit position and multiply it by the bit value.
      - Sum all values obtained.
   e. If the sum is < 10, add to hexString; else, convert to ASCII character and add to hexString.
   f. Once all groups are processed, return hexString.

3. **If 16 is selected:**
   1. Convert hexadecimal to decimal and then to binary.
   2. Validate input to ensure it is a valid hexadecimal number.
   3. If a number, convert to binary by dividing by 2 and appending remainders until result is 0.
   4. If a letter, convert to decimal using ASCII (subtracting 55).
   5. Convert decimal to binary.

## Installation

No specific installation steps are required. Simply execute the provided executable file.

## Troubleshooting

For issues or questions, refer to the Troubleshooting section or contact kiglerr#gmail.com.

## Exit

To exit the system when prompted, select X.
