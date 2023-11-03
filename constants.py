'''
Constant class for all of the constants needed throughout the programs. These are
things that will remain the same no matter what user we are testing. The changes made
here must be the same as the changes on XCTU (Or if we decide to change them here to 
send an AT command)

'''
class Constants():

    baudrate = 115200
    timeout = 20