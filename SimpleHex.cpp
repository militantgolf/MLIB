//SimpleHex v1
//Samuel Giesbrecht 2020
//MilitantGolf


#include <iostream>
#include <fstream>


using namespace std;

//Set based on architecture
//x86 and AMD64/x64 is big-endian
//aarch64 (ARM64) is little-endian
#define LITTLEENDIAN
#ifndef LITTLEENDIAN
#define BIGENDIAN
#endif

#define BUFFERSIZE 64

//Value controls if functions output raw data without orginization.
bool rawData = false;

/// <summary>
/// Used to convert bytes to long
/// </summary>
union longHex
{
	long l;
	char c[sizeof(long)];
};

/// <summary>
/// Determines if a given string is a hex value.
/// Meaning that all values are within the 0-9 and A-F range
/// Not case sensitive
/// This program does not read 0x or h notations only the number it self.
/// </summary>
/// <param name="c">String to check</param>
/// <returns>true if is a hex value, false if not</returns>
bool isHex(char* c, int length = 2)
{
	for (int i = 0; i < length; i++)
	{
		//Checks if char is a number ascii value
		if ((c[i] >= 0x30 && c[i] <= 0x39) ||
			//Checks if char is an uppercase A-F
			(c[i] >= 0x41 && c[i] <= 0x46) ||
			//Checks if char is a lowercase a-f
			(c[i] >= 0x61 && c[i] <= 0x66))
			//Go on to next itteration if value is correct
			continue;
		//return false char is not a valid hex digit
		return false;
	}
	return true;
}

/// <summary>
/// Converts two char values representing a hexadecimal byte to a binary byte
/// </summary>
/// <param name="c">two chars representing a byte</param>
/// <returns>returns 0 if an invalid hex is given, if not the translated value is given</returns>
char stringToHex(char* c)
{
	unsigned char val = 0x00;
	 
	if (!isHex(c))
		return NULL;

	//Translates the two chars to a byte
	for (int i = 0; i < 2; i++)
	{
		//Shift low nibble to high nibble
		val = val << 4;

		//set lowest nibble
		switch (c[i])
		{
		case '0':
			val = val| 0x00;
			break;
		case '1':
			val = val | 0x01;
			break;
		case '2':
			val = val | 0x02;
			break;
		case '3':
			val = val | 0x03;
			break;
		case '4':
			val = val | 0x04;
			break;
		case '5':
			val = val | 0x05;
			break;
		case '6':
			val = val | 0x06;
			break;
		case '7':
			val = val | 0x07;
			break;
		case '8':
			val = val | 0x08;
			break;
		case '9':
			val = val | 0x09;
			break;
		case 'a':
			val = val | 0x0A;
			break;
		case 'A':
			val = val | 0x0A;
			break;
		case 'b':
			val = val | 0x0B;
			break;
		case 'B':
			val = val | 0x0B;
			break;
		case 'c':
			val = val | 0x0C;
			break;
		case 'C':
			val = val | 0x0C;
			break;
		case 'd':
			val = val | 0x0D;
			break;
		case 'D':
			val = val | 0x0D;
			break;
		case 'e':
			val = val | 0x0E;
			break;
		case 'E':
			val = val | 0x0E;
			break;
		case 'f':
			val = val | 0x0F;
			break;
		case 'F':
			val = val | 0x0F;
			break;
		}

	}
	
	return val;
}

/// <summary>
/// Prints a byte as a pair of hex digits
/// </summary>
/// <param name="val">Byte to print</param>
void printHexValue(char val)
{
	//Get Lowest Nibble
	char valA = val & 0x0F;
	//Get Highest Nibble
	char valB = (val & 0xF0) >> 4;
	//print Nibbles
	for (int i = 0; i < 2; i++)
	{
		switch (valB)
		{
		case 0x00:
			cout << "0";
			break;
		case 0x01:
			cout << "1";
			break;
		case 0x02:
			cout << "2";
			break;
		case 0x03:
			cout << "3";
			break;
		case 0x04:
			cout << "4";
			break;
		case 0x05:
			cout << "5";
			break;
		case 0x06:
			cout << "6";
			break;
		case 0x07:
			cout << "7";
			break;
		case 0x08:
			cout << "8";
			break;
		case 0x09:
			cout << "9";
			break;
		case 0x0A:
			cout << "A";
			break;
		case 0x0B:
			cout << "B";
			break;
		case 0x0C:
			cout << "C";
			break;
		case 0x0D:
			cout << "D";
			break;
		case 0x0E:
			cout << "E";
			break;
		case 0x0F:
			cout << "F";
			break;
		}
		valB = valA;
	}
}

//Prints a long value in hexadecimal form
void printLong(long val)
{
	//Used to translate a long to 4-8 bytes
	longHex v;
	v.l = val;

	//prints values
	for (int i = 1; i <= sizeof(long);i++)
	{
#ifdef LITTLEENDIAN
		printHexValue(v.c[sizeof(long)-i]);
#endif
#ifdef BIGENDIAN
		printHexValue(v.c[i-1]);
#endif
	}
}


/// <summary>
/// Processes a large string of hex values, and creates a translated byte string.
/// </summary>
/// <param name="input">Hex string to be processed</param>
/// <returns>An byte array containing half the number of elements of the input string. Is the translation of input</returns>
char* processHexString(char* input)
{
	//Get the length of the input string
	int length = 0;
	while (input[length] != 0x00)
		length++;

	//Processing array
	char* original = input;

	//Is array modified. used for determining if array is to be deleted at the end of the method.
	bool modified = false;

	//if the input string is not even 
	if ((length % 2) != 0)
	{
		//Shift array up one, inserting '0' to the first digit
  		original[0] = '0';
		for (int i = 0; i < length; i++)
		{
			original[i + 1] = input[i];
		}
		length++;
		//signals to delete array at end of function
		modified = true;
	}

	//output array for the byte values
	char* output = new char[length / 2];

	//Translate input to output
	for (int i = 0, b = 0; i < length; i += 2, b++)
	{
		output[b] = stringToHex(&original[i]);
	}

	//clean up
	if (modified)
		delete[] original;

	return output;
}

/// <summary>
/// Translates a hexadecimal string to a DWORD/QWORD based on respective architecture.
/// No difference between 0x01 and 0x1
/// </summary>
/// <param name="input">the string to be translated</param>
/// <param name="index">split string index, Aids with range parameters, 0 for first string, 1 for second string, ...</param>
/// <param name="separator">Character to split the string by</param>
/// <returns></returns>
long getLongFromHex(char* input, int index = 0, char separator = '-')
{

//Process string-----------------------------------------------------
	//Starting index of the string to convert.
	int pos = 0;
	//Length of the string to convert.
	int count = 0;

	//If index is set to 0 start counting
	bool counting = (index == 0) ? true : false;

	//finds the start point of the string, and finds its length.
	//segments is what segment the index is currently positioned in.
	for (int i = 0, segments = 0; input[i] != 0x0; i++)
	{
		//If string seperator is found at current index
		if (input[i] == separator)
		{
			//moves into next segment
			segments++;

			//if current segment is the desired one
			if (segments == index)
			{
				//Set up starting position, and enable counting
				pos = i + 1;
				counting = true;
				continue;
			}
			//if not the desired segment, stops counting
			counting = false;
		}

		//add one to counter if counting
		if (counting)
			count++;
	}

	//Checks if string is balanced, meaning bytes are complete
	if ((count % 2) != 0)
	{
		return 0;
	}

	//Translator for long to char[]
	longHex data;
	//clears data
	data.l = 0x0;

	//Holds byte ascii values
	char temp[2];

	//gets the offset of the far endpoint of the string
	int l = pos + count;

	//gets the byte count
	int c = count / 2;
	
	//if longer than the system supports step it down
	if (c > sizeof(long))
		c = sizeof(long);

	//Translate string and story bytes
	for (int i = pos, b = 1; i < l && b < 5; i += 2, b++)
	{
		//loads ascii bytes
		temp[0] = input[i];
		temp[1] = input[i + 1];

		//checks if values are in the 0-9 and a-f range
		if (!isHex(temp))
		{
			return 0;
		}

		//Stores the data
#ifdef LITTLEENDIAN
		data.c[c - b] = stringToHex(temp);
#endif
#ifdef BIGENDIAN
		data.c[b-1] = stringToHex(temp);
#endif
	}

	return data.l;
}





/// <summary>
/// Checks if a parameter is present in a string
/// </summary>
/// <param name="buffer">buffer to seek through</param>
/// <param name="param">parameter to search for</param>
/// <param name="prefix">prefix char default = '-'</param>
/// <returns>True if parameter flag is present, False if not</returns>
bool paramExists(char* buffer, char param, char prefix = '-')
{
	//Search buffer for parameter flag
	for (int i = 0;buffer[i] != 0x00; i++)
		if (buffer[i] == prefix && buffer[i + 1] == param)
			return true;

	return false;
}

/// <summary>
/// Gets the arguments of the given parameter
/// </summary>
/// <param name="buffer">Buffer where data is stored</param>
/// <param name="param">Parameter to search for</param>
/// <param name="prefix">Prefix char default = '-'</param>
/// <returns>the arguments for the parameter </returns>
char* getParameter(char* buffer, char param, char prefix = '-')
{
	for (int i = 0; buffer[i] != 0x00; i++)
	{
		//if Parameter is found
		if (buffer[i] == prefix && buffer[i + 1] == param)
		{
			i += 3;
			//Create buffer to hold arguments
			char* data = new char[32];
			int b = 0;

			//copy argument data to temperary buffer
			while (i < 64&&buffer[i]!=0x0&&buffer[i]!=' ')
			{
				data[b] = buffer[i];
				b++;
				i++;
			}
			//Cap off and return string
			data[b] = 0x0;
			return data;
		}
	}
	return 0x00;
}


/// <summary>
/// Prints a line of hex values with its location and ascii data
/// </summary>
/// <param name="values">File Data</param>
/// <param name="address">Address to print from</param>
/// <param name="seperation">Word size</param>
/// <param name="length">Bytes to print</param>
void printHexLine(char* values,int address, int seperation,int length = 16)
{
	//If not printing raw data, print address
	if (!rawData) 
	{
		printLong(address);
		cout << ": ";
	}
	//Print Bytes to screen with spaces in between the words
	for (int i = 0, j = 0; i < length; i++, ++j)
	{
		if (j >= seperation)
		{
			if (!rawData)
				cout << " ";
			j = 0;
		}
		printHexValue(values[i]);
	}

	//If the whole line is not printed, fill the unocupied space with spaces
	if (length < 16 && !rawData)
	{
		int disp = 16-length;
		int t = disp / 2;
		t += disp * 2;
		for (int j = 0; j < t; j++)
			cout << ' ';
	}
	//Print the ascii values to the right side if rawData is false
	if (!rawData)
	{
		cout << "    ";
		for (int i = 0; i < length; i++)
		{
			if (values[i] <= 0x1F)
			{
				cout << "."; //Prevents control characters from interfering with the console
			}
			else
			{
				cout << values[i];
			}
		}
		cout << "\n";
	}
}

/// <summary>
/// Prints the file, or Section of the file to the screen
/// </summary>
/// <param name="data">File data</param>
/// <param name="length">Section end or file lenght</param>
/// <param name="start">Section Start default = 0</param>
/// <param name="wordSize">Byte groupings defualt = 2 Must be 1,2,4,8,or 16</param>
void printHexFile(char* data, long length,long start =0,long wordSize= 2)
{
	//Checks if wordSize is not valid
	if (wordSize != 1 && wordSize != 2 && wordSize != 4 && wordSize != 8 && wordSize != 16)
	{
		//if not valid set to 2
		wordSize = 2;
	}

	//Determine number of lines needed
	int limit = length / 16;

	//Gets the total without the remainders
	limit = limit * 16;

	//sets i to start
	int i = start;
	
	//Print the file line by line
	for (; i < limit; i += 16)
	{
		char* t = &data[i];
		printHexLine(t, i, wordSize);
	}
	//Print the last partial line of the file
	if (i < length)
	{
		int t = length - limit;
			printHexLine(&data[i], i, wordSize,t);
	}
}

/// <summary>
/// Compares two strings, but only if the first segment of the source, matches the origin string. source may be longer.
/// Designed for parsing commands.
/// </summary>
/// <param name="source">Long string</param>
/// <param name="origin">String to compare the first segment of the source to</param>
/// <returns></returns>
bool compareSegment(char* source, const char origin[])
{
	for (int i = 0; ; i++)
	{
		//if origin has run out
		if (origin[i] == 0x00)
			return true;
		//if two strings are different
		//if two strings are different
		if (source[i] != origin[i])
			return false;
	}
}


/// <summary>
/// Entry point of the program
/// </summary>
/// <param name="argc">Argument count</param>
/// <param name="argv">Argument strings</param>
/// <returns></returns>
int main(int argc, char* argv[])
{
	//controls if the program is just outputting to the console(false), or opening to edit(true)
	bool editing = false;
	long wordSize = 2;

	//Process Parameters
	if (argc > 2)
	{
		for (int i = 2; i < argc; i++)
		{
			//If -e flag or edit flag is set, this opens the program in editor mode, cannot be used with dump flag
			if (paramExists(argv[i],'e'))
			{
				if (!rawData)
					editing = true;
			}
			
			//if -d flag or raw dump is set, when enabled outputs the raw hexadecimal data to the console, cannot be used with the editing flag
			if (paramExists(argv[i], 'd'))
			{
				if (!editing)
					rawData = true;
			}
			
			//if -w or Wordsize Flag is set, get the word size parameter
			if (paramExists(argv[i], 'w'))
			{
				//splits range into two components
				wordSize = getLongFromHex(argv[i+1], 0);

				if (wordSize != 1 && wordSize != 2 && wordSize != 4 && wordSize != 8 && wordSize != 16)
				{
					wordSize = 2;
				}

			}

			//if -r flag or range flage is set, when set, the program outputs only what is within the range specified, range must be in AABBCCDD-AABBCCDD format, each side may have between 1-4 sets of hex values, VALUES MUST BE IN PAIRS!
			if (paramExists(argv[i], 'r'))
			{
				//Gets range
				char* p = getParameter(argv[i], 'r');
				//splits range into two components
				long j = getLongFromHex(p, 0);
				long k = getLongFromHex(p, 1);
				//deletes the temporary array object
				delete[] p;

			}
		}
	}
	
	//stream construct for file IO
	std::fstream stream;
	
	//opens file passed by parameter
	if (argc >= 2)
	{
		stream.open(argv[1], std::ios::binary| std::ios::in);
	}
	
	//If unable to read file, print error
	if (!stream.is_open())
	{
		cout << "Could not open File!\n";
		stream.close();
		return 1;
	}

	//Calculate size of file
	long length = 0;
	
	//get end position
	stream.seekg(0,ios_base::end);
	length = stream.tellg();

	//subtract the beginning from the end position
	stream.seekg(0,ios_base::beg);
	length -= stream.tellg();

	//create array to hold the files data
	char* data = new char[length];

	//Load the files data into the array
	stream.read(data, length);

	//Print file to screen if editing is not enabled
	if (!editing)
		printHexFile(data, length);

	//close the stream
	stream.close(); 

	//Program running loop
	while (editing)
	{
		//Input command
		cout << "SimpleHex>";
		char input[BUFFERSIZE];
		cin.getline(input, BUFFERSIZE);

		//if quit command is given
		if (compareSegment(input, "quit")|| compareSegment(input, "exit"))
		{
			editing = false;
			break;
		}

		//if print command is given
		if (compareSegment(input, "print"))
		{
			//Process parameters of the print function
			//rawDump flag, outputs raw hex values
			if (paramExists(input, 'd'))
			{
				//The auxiary print functions use this value to determin how to print.
				//By setting this to true, then calling the print file function, it will output the raw hex
				rawData = true;
			}

			//if -w or Wordsize Flag is set, get the word size parameter
			if (paramExists(input, 'w'))
			{
				//Gets range
				char* p = getParameter(input, 'w');
				//splits range into two components
				wordSize = getLongFromHex(p, 0);
				//deletes the temporary array object
				delete[] p;

				if (wordSize != 1 && wordSize != 2 && wordSize != 4 && wordSize != 8 && wordSize != 16)
				{
					wordSize = 2;
				}

			}

			//Range flag, prints the range specified
			if (paramExists(input, 'r'))
			{
				char* p = getParameter(input, 'r');

				long j = getLongFromHex(p, 0);
				long k = getLongFromHex(p, 1);
				delete[] p;
				//Prints file with range
				printHexFile(data, k,j, wordSize);
			}
			else
				//Print 
				printHexFile(data, length,0,wordSize);
			rawData = false;
			cout << "\n";
		}

		//xor command, applies an and mask to a selected segment of the file
		if (compareSegment(input, "xor"))
		{
			//xor mask
			char t[2];
			t[0] = input[4];
			t[1] = input[5];

			//checks if mask is a hex value
			if (!isHex(t))
			{
				cout << t << " is not a hexadecimal value\n";
				continue;
			}

			//Sets start and stop point to the begining and end of the file respectivley
			long j = 0;
			long k = length;

			//Checks if a range was given
			if (paramExists(input, 'r'))
			{
				//Gets the parameters
				char* p = getParameter(input, 'r');
				
				//Sets the start and stop points to the given parameters
				j = getLongFromHex(p,0);
				k = getLongFromHex(p, 1);

				//clean up
				delete[] p;
				
			}
			
			//apply mask to section
			char m = stringToHex(t);
			for (; j < k; j++)
			{
				data[j] = data[j] ^ m;
			}
		}

		//and command, applies an and mask to a selected segment of the file
		if (compareSegment(input, "and"))
		{
			//and mask
			char t[2];
			t[0] = input[4];
			t[1] = input[5];

			//Verify that the mask is a hex value
			if (!isHex(t))
			{
				cout << t << " is not a hexadecimal value\n";
				continue;
			}

			//set start and stop points to the begining and end of the file respectivly
			long j = 0;
			long k = length;

			//Checks if a range was given.
			if (paramExists(input, 'r'))
			{
				//Gets the parameters
				char* p = getParameter(input, 'r');

				//Sets the start and stop points to the parameters
				j = getLongFromHex(p, 0);
				k = getLongFromHex(p, 1);

				//clean up
				delete[] p;

			}

			//Apply mask to section
			char m = stringToHex(t);
			for (; j < k; j++)
			{
				data[j] = data[j] & m;
			}
		}

		//or command, applies an or mask to a selected segment of the file
		if (compareSegment(input, "or"))
		{
			//or Mask
			char t[2];
			t[0] = input[4];
			t[1] = input[5];

			//Verify that it is a hex vaue
			if (!isHex(t))
			{
				cout << t << " is not a hexadecimal value\n";
				continue;
			}

			//Set begining and end points for the operation, being the begining and end of the file
			long j = 0;
			long k = length;

			//Check if a range is given
			if (paramExists(input, 'r'))
			{
				//Get the parameter data
				char* p = getParameter(input, 'r');

				//process the parameter data and apply them the the ranges
				j = getLongFromHex(p, 0);
				k = getLongFromHex(p, 1);

				//clean up
				delete[] p;

			}

			//apply mask to section
			char m = stringToHex(t);
			for (; j < k; j++)
			{
				data[j] = data[j] | m;
			}
		}

		//Save command, Saves to the given file
		if (compareSegment(input, "save"))
		{
			//Opens file to write
			if (argc >= 2)
			{
				stream.open(argv[1], std::ios::binary | std::ios::out);
			}
			//if not able to open, print error to screen and prompt for new command
			if (!stream.is_open())
			{
				cout << "Could not open File!\n";
				stream.close();
			}
			else
			{
				//write data to file and close stream
				stream.write(data, length);
				stream.close();
			}
		}

		//find command, finds a given hex string in the file
		if (compareSegment(input, "find"))
		{
			bool printResults = true;
			if (paramExists(input, 'h'))
			{
				printResults = false;
			}
			

			int i = 5;
			//array to hold the parameter
			char temp[BUFFERSIZE];
			for (; input[i] != 0&& input[i] != ' ' && i < BUFFERSIZE; i++)
			{
				temp[i - 5] = input[i];
			}
			temp[i - 5] = NULL;

			//Length of temp array
			int tempL = i - 5;

			int tempL2 = tempL / 2;
			//Holds the binary values to search against
			char *temp2 = new char[tempL2];

			//Convert String to Binary
			for (int I = 0; I < tempL2; I++)
			{
				//If character Pair is hexadecimal, add to binary string
				if (isHex(&temp[I * 2]))
					temp2[I] = stringToHex(&temp[I * 2]);
				//Else finish string
				else
				{
					tempL2 = I;
					break;
				}
			}

			//How many matches were found
			int totalFound = 0;

			//Linear search of the file
			for (int b = 0; b < length; b++)
			{
				//For each byte chech if equals string, when a descrepency is found this loop terminates, keeping an efficiency of O(n) where possible
				for (int I = 0; I < tempL2; I++)
				{
					//If strings are not equal, break loop
					if (data[b + I] != temp2[I])
					{
						break;
					}

					//if comparison reaches the end of the string
					if (I == tempL2 - 1)
					{
						//Print results if needed
						if (printResults)
						{
							printHexFile(data, b + 16, b, wordSize);
						}
						//increment total by one
						totalFound++;
					}
				}
			}
			//output total found
			cout << totalFound << " Matches Found!\n";

			//clean up
			delete[] temp2;
		}
	}

	return 0;
}
