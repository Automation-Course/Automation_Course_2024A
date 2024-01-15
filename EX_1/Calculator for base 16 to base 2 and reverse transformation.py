#!/usr/bin/env python
# coding: utf-8

# In[1]:


def MoveBinToHexa(userInputNumber):
    # If the input number isn't divided by 4 perfectly, add zeros from the left until the number is a power of 2
    if len(userInputNumber) % 4 != 0:
        zerosToAdd = (4 - len(userInputNumber) % 4)
        userInputNumber = '0' * zerosToAdd + userInputNumber
    hexadecimal_result = ""
    # Group every 4 chars to one Hexadecimal number
    for i in range(0, len(userInputNumber), 4):
        group = userInputNumber[i:i+4]
        groupSum = 0
        for j in range(4):
            groupSum += int(group[j]) * (2 ** (3-j))
        if (groupSum > 9):
            if (groupSum == 10):
                hexadecimal_result += "A"
            if (groupSum == 11):
                hexadecimal_result += "B"
            if (groupSum == 12):
                hexadecimal_result += "C"
            if (groupSum == 13):
                hexadecimal_result += "D"
            if (groupSum == 14):
                hexadecimal_result += "E"
            if (groupSum == 15):
                hexadecimal_result += "F"
        else:
            hexadecimal_result += str(groupSum)

    print("Hexadecimal Result:", {hexadecimal_result})
    finishCalc()
        
        


# In[2]:


def finishCalc():
    # Menu to choose how to proceed after finishing transferring hexadecimal to binary or the opposite direction
    userInput = input("Do you want to transfer another number?\n 1 To Exit\n 2 To Advance")
    if userInput == '1':
        print("Goodbye")
    elif userInput == '2':
        getInput()
    else:
        print ("Error")
        finishCalc()


# In[ ]:





# In[3]:


def MoveHexaToBin(userInputNumber):
    binary_result = ""
    for c in userInputNumber:
        # If c is char - translate it to number
        if c.isalpha():
            sum = ord(c) -64 + 9
        else:
            sum = int(c)
        # Add ones or zeros to the string accordingly
        for i in range(3,-1,-1):
            if sum >= 2**(i):
                binary_result += '1'
                sum = sum - 2**(i)
            else:
                binary_result += '0'
    # Remove zeros until a one occures in the stirng
    foundOneFlag = False
    result_str = ""
    for char in binary_result:
        if char == '1':
            foundOneFlag = True
        if foundOneFlag:
            result_str += char 
    print("Binary Result:", {result_str})
    finishCalc()
 
                
                
                
            
        
        


# In[4]:


def getInput():
    # Receiving input from the user
    userInputBase = input("Please select your option:\n For moving from binary base to hexadecimal base enter '2'\n For moving from hexadecimal base to binary base enter '16'\n")
    # Translating input to binary or hexadecimal, depending on the input. The rest of the function - validation
    if userInputBase == '2':  
        userInputNumber = input("Please select a number to transform")
        if all(c == '1' or c == '0' for c in userInputNumber):
            MoveBinToHexa(userInputNumber)
        else:
            print("Invalid binary number, Please try again")
            getInput()
    elif userInputBase == '16':
        userInputNumber = input("Please select a number to transform")
        if any(c.isdigit() or (c.upper() in 'ABCDEF') for c in userInputNumber):
            MoveHexaToBin(userInputNumber)
        else:
            print("Invalid hexadecimal number, Please try again")
            getInput()
    else:
        print("Invalid input, please try again")
        getInput()


# In[5]:


getInput()


# In[ ]:





# In[ ]:




