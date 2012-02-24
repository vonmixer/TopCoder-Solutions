"""
File: make-win-starter.py
Author: doug@neverfear.org
Version: 1.0
 
This file is a utility script for building an executable script that users 
of the Windows operating system can double click on to start their Python
application. This utility can be especially useful if your Python application
does not need to display the command prompt.
 
The method used here is adapted from the method discussed on the Python Windows
FAQ (see link below) by employing the pythonw.exe executable rather than
python.exe and by putting double quotes around %~f0 to allow for working
directories with whitespace in the pathname.
 
Python Windows FAQ:
http://www.python.org/doc/faq/windows/#how-do-i-make-python-scripts-executable
 
Example usage from the command line:
    python make-win-starter.py -i mypythonfile.py -o mypythonfile-starter.cmd
 
"""
 
 
 
from sys import argv
from sys import exit
from getopt import getopt
from getopt import GetoptError
 
__version__ = "1.0"
__author__ = "doug@neverfear.org"
 
def usage():
    print "usage: python make-win-starter.py [-w|-t] -i inputfile [-o outputfile]"
    print "Options and arguments:"
    print "-h        Display this help."
    print "-i        The input file. This should be a Python script to make"
    print "          executable."
    print "-o        The output file. This should be a file ending with the"
    print "          .bat or .cmd extension."
    print "-w        Use this option if the Python script you are making"
    print "          executable for is a GUI application and you do not want"
    print "          the command prompt to popup. Opposite of -t. (default)"
    print "-t        Use this option if the Python script you are making a"
    print "          executable for is a command line application that "
    print "          requires the command prompt to be displayed. Opposite"
    print "          of -w."
    print
 
 
try:
 
    opts, args = getopt(argv[1:], "ho:i:wt")
 
except GetoptError, err:
    print str(err)
    usage()
    exit(1)
 
OutputFile, InputFile = 'TopCoder.cmd','TopCoder_script.py' 
PythonBin = "pythonw"
 
for (opt, value) in opts:
    if opt == "-o":
        OutputFile = value
    elif opt == "-i":
        InputFile = value
    elif opt == "-w":
        print "Using pythonw.exe as interpreter"
        PythonBin = "pythonw"
    elif opt == "-t":
        print "Using python.exe as interpreter"
        PythonBin = "python"
    elif opt == "-h":
        usage()
        exit(0)
 
if not InputFile:
    print "Error: No input file set."
    exit(2)
 
if not OutputFile:
    OutputFile = "win-starter.cmd"
    print "Warning: No output file set. Assuming", OutputFile
 
InputFd = open(InputFile, "r")
if not InputFd:
    print "Error: Failed to open", InputFile, "for reading"
    exit(3)
 
OutputFd = open(OutputFile, "w")
if not OutputFd:
    print "Error: Failed to open", OutputFile, "for writing"
    exit(4)
 
OutputFd.write("@setlocal enableextensions & start %(PYBIN)s -x "
               "\"%%~f0\" %%* & goto :EOF\r\n" %
               {"PYBIN": PythonBin})
 
OutputFd.write(InputFd.read())
 
OutputFd.close()
InputFd.close()
 
print "Operation was successful"
