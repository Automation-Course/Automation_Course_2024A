#!/usr/bin/env python
# coding: utf-8

# ### Functions:

# #### binary to hex functions:

# In[2]:


# the function check if the string contains only 0's and 1's:
def check_binary(num_str):
    for char in num_str:
        if char != '0':
            if char != '1':
                return False
    return True


# In[20]:


# the function divide the string to nibbles, if needed it will add 0's in the start of the string. return a list of strings:
def divide_into_nibbles(binary):
    while len(binary) % 4 != 0:
        binary = '0' + binary
    str_list = []
    for i in range(0, len(binary), 4):
        str_list.append(binary[i:i+4])
    return str_list


# In[18]:


# the function recieve a list of strings representing the binary num and convert it to hex number represented as string:
def binary_to_hex(str_list):
    hex_str = ""
    for nibble in str_list:
        temp_sum = 0
        counter = 3
        for char in nibble:
            temp_sum = temp_sum + int(char)*(2**counter) #conversion stage
            counter = counter - 1
        if (temp_sum <= 9) & (temp_sum > 0): #numbers above nine
            hex_str = hex_str + str(temp_sum)
        elif temp_sum == 10:
            hex_str = hex_str + 'A'
        elif temp_sum == 11:
            hex_str = hex_str + 'B'
        elif temp_sum == 12:
            hex_str = hex_str + 'C'
        elif temp_sum == 13:
            hex_str = hex_str + 'D'
        elif temp_sum == 14:
            hex_str = hex_str + 'E'
        elif temp_sum == 15:
            hex_str = hex_str + 'F'
    return hex_str


# #### hex to binary functions:

# In[64]:


def hex_to_binary(hex_number):
    hex_options = '0123456789ABCDEF'
    for i in hex_number: #check if valid
        if i not in hex_options:
            return "\nPlease insert valid value"
    #initial varible     
    num_base_10 = 0
    binary_number = ''
    position = 0
    hex_dict = {'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15} #dictionary to convert letters to values
    ## stage 1 - convert to decimal base
    for char in hex_number[::-1]:
        if char.isalpha(): #if it is a letter
            num_base_10 += hex_dict[char.upper()] * (16 ** position)
        else:
            num_base_10 += int(char) * (16 ** position)
        position += 1

    temp = num_base_10 ##save value for check
    ## stage 2 - convert from decimal base to hex base
    while num_base_10 > 0:
        remainder = num_base_10 % 2
        binary_number = str(remainder) + binary_number
        num_base_10 = int(num_base_10 / 2)

#add 0 if even
    if temp % 2 == 0:
        binary_number = '0' + binary_number
#remove 0 in the biginning for disply porpesses      
    if binary_number[0] == '0':
        binary_number = binary_number[1:]

    return binary_number


# ### Main:

# In[41]:


def main():
    while True:
        choice = input("Choose converter option: \n1. Hexadecimal to binary \n2. Binary to hexcadecimal \n3. Exit\nEnter your choice: ")
        if choice == '1':
            user_num = input("Enter your hexadecimal number: ")
            print(hex_to_binary(user_num))
        elif choice == '2':
            user_num = input("Enter your binary number: ")
            if check_binary(user_num):
                nibbles = divide_into_nibbles(user_num)
                result = binary_to_hex(nibbles)
                print("\nYour hexcadecimal number is: ", result)
            else:
                print("\nThe number you entered is not valid.")
        elif choice == '3':
            print("\nExiting converter. Goodbye!")
            break
        else:
            print("\nThis is not an option provided to you.")
        


# In[ ]:


main()

