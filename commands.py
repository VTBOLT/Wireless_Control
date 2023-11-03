'''
Define the functions/methods that we are going to use. This file
is split up between the functions to format and send our own data
and interpret the received data

'''
###############################################################
#-------------------------------------------------------------#
#                         Send Methods                        #
#-------------------------------------------------------------#
###############################################################


def convertCheckSum(inputWord): # Checksum calculation goes here
    checkSum = int(inputWord, 0)

    return checkSum

def convertLength(inputWord): # Length Calculation
    length = int(inputWord, 0)

    return length