# SimpleHex
Console based hexadecimal tool designed to aid in working with partially decrypted files.

Built using the std libraries of C++ for cross compatablility.

# Features
[+] View binary files in hexadecimal format with its associated ascii values.

[+] Output the contents of the file as a string of pure hex values (Ideal for piping).

[+] Apply AND, OR, and XOR masks to sections of the file.

[+] Save alterations to the file

# How to use

SimpleHex "FILENAME" "ARGUMENTS"

Arguments:

-e Enables editing, if this is not given the program will simply output the file to the console and terminate.

-d Data Dump, this flags removes all formating of the output, Printing only the file in hex format.

-w Sets the Word size, this argument is given with a parameter, being either 1, 2, 4, 8, 16. This sets how many bytes are bound together in the formating. Default is 2. Example -w 2

Editing mode

Command Parameters:

-w Word Size, Same as the program argument

-d Data Dump, Same as the program argument

-r Range Parameter, -r <HEXVALUE>-<HEXVALUE> parameter are two hex values separated by a dash '-'. Hex values are not to have the '0x' suffix or 'h' postfix, as of this moment they are not supported. if -r is not given command will effect whole file.

When in edit mode you will see the cursor "SimpleHex>". The program accepts the following commands:

print: Prints the file or a section of the file to the screen. Parameters accepted are -d, -w, and -r

xor:   Applies the XOR operation on a given byte and the file or a section of the file. Parameters accepted are -r. Use: xor <Mask = 00-FF> Parameters
  
or:    Applies the OR operation on a given byte and the file or a section of the file. Parameters accepted are -r. Use: or <Mask = 00-FF> Parameters
  
and:   Applies the AND operation on a given byte and the file or a section of the file. Parameters accepted are -r. Use: and <Mask = 00-FF> Parameters

save:  Saves the file

find:  Searches the file for the given hex string, and outputs the amount of occurences as well as their positions in the file

quit:  Quits the program, may also use "exit"
  
  


