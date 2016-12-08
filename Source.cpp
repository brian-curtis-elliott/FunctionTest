#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

//Global config 
fstream file_config;
bool fileOutput = false;
bool debug = false;
stringstream stemp;

//Global constants 
const int NUM_MENU_ITEMS = 6;

//Global variables 
int menuNum = 0;
int typeNum = 0;
string typeName = "";
unsigned int numNum = 0;
string equation = "";
string op = "";
string opName = "";
bool bMenuLoop;

//Result Global variables 
int answerInt = 0;
double answerDouble = 0.0;
float answerFloat = 0.0F;

//Global vectors to store user inputted numbers for the equation 

vector<int> vectorInt(1, 0);
vector<double> vectorDouble(1, 0.0);
vector<float> vectorFloat(1, 0.0F);

//Global vectors used to store strings for output 

vector<string> vectorMenuItems(1, "");
vector<string> vectorOutput(1, "");

//Prototypes 

//Config functions 
void config(fstream&);
void debugOut(string);

//Menu functions 

bool menu(const int);
void menuItems();

void typeMenu();

void menuLoop();

//User Prompt functions 
void numNums(string, const long long, const long long);

//Calculation functions 

//Clear answer function
void clearAnswer(int = 0, double = 0.0, float = 0.0F);

//Add function
void add(int);

//Subtract function
void subtract(int);

//Multiply function
void multiply(int);

//Divide function
void divide(int);

//Modulus or Remainder function
void modulo(int);


//Input functions 
void in(int, string);
void in(int, int, string);

//Output functions 
void out();
string return_current_time_and_date();
void end();

//Main function
int main()
{
	file_config.open("config.txt", std::fstream::in);
	config(file_config);
	exit(1);									//Uncomment to debug config file parsing. 

	//Set values of vectorMenuItems 
	vectorMenuItems = vector<string>(NUM_MENU_ITEMS, "");

	vectorMenuItems[0] = "Addition";
	vectorMenuItems[1] = "Subtraction";
	vectorMenuItems[2] = "Multiplication";
	vectorMenuItems[3] = "Division";
	vectorMenuItems[4] = "Modulo";

	vectorMenuItems[5] = "Quit";

	//Set values of vectorOutput 
	vectorOutput = vector<string>(13, "");

	vectorOutput[0] = "You used the ";
	vectorOutput[2] = " function.\n";
	vectorOutput[3] = "You used ";
	vectorOutput[5] = "s as your data type.\n";
	vectorOutput[6] = "You entered ";
	vectorOutput[8] = " numbers.\n";
	vectorOutput[9] = "Your equation was ";
	vectorOutput[11] = " = ?\n";
	vectorOutput[12] = "Your result is:\t";


	bMenuLoop = true;


	do
	{
		//if (debug) { break; } //Uncomment this to debug end screen. 


		if (menu(NUM_MENU_ITEMS))
		{
			bMenuLoop = true;
		}
		else
		{
			bMenuLoop = false;
		}


		vectorOutput[1] = opName;
		vectorOutput[4] = typeName;
		vectorOutput[7] = numNum;

		out();


		if (bMenuLoop)
		{
			menuLoop();
		}

	} while (bMenuLoop);

	end();

}

//Config functions 
void config(fstream& input_file)
{
	vector< vector<string> > vec(1, vector<string>(2, ""));
	debugOut("beginning of config\n");
	std::stringstream is_file("");
	debugOut("is_file created\n");


	unsigned int counter = 0, numComments = 0;
	for (std::string line; std::getline(input_file, line);)
	{
		debugOut("beginning of while loop\n");
		std::stringstream is_line(line);
		debugOut("is_line created from line\n");
		std::string key;
		if (line.at(0) == '#')
		{
			numComments++;
			continue;
		}
		stemp = stringstream(""); stemp << "counter:\t" << counter << "\tvec.size():\t" << vec.size() << "\t";  debugOut(stemp.str());
		stemp = stringstream(""); stemp << "counter > vec.size():\t" << (counter > vec.size()) << "\n"; debugOut(stemp.str());
		stemp = stringstream(""); stemp << "Number of Comments:\t" << numComments << "\n\n"; debugOut(stemp.str());

		if (counter > (vec.size()-1))
		{
			vector<string> temp(2, "");
			debugOut("temp created\n");
			vec.push_back(temp);
			debugOut("vec.push_back(temp)\n");
		}
		if (std::getline(is_line, key, '='))
		{
			debugOut("1st if statment beginning\n");
			std::string value;
			if (std::getline(is_line, value))
			{
				debugOut("2nd if statement beginning\n");
				stemp = stringstream(""); stemp << "key:\t" << key << "\tvalue:\t" << value << "\n"; debugOut(stemp.str());
				vec[counter][0] = key;
				vec[counter][1] = value;
				stemp = stringstream(""); stemp << "key:\t" << vec[counter][0] << "\tvalue:\t" << vec[counter][1] << "\n"; debugOut(stemp.str());
				//store_line(key, value);
				debugOut("2nd if statement ending\n");
			}
			debugOut("1st if statement ending\n");
		}
		debugOut("ending of while loop\n");
		counter++;
	}
	debugOut("end of config\n");
}

void debugOut(string s)
{
	if (debug)
	{
		cout << s;
	}
}

//Menu functions 

//Main menu function
bool menu(const int MENU_MAX)
{
	const int MENU_MIN = 1;
	bool inputError = false;				//Used as a check to know if the do-while loop has executed more than once. If it has executed more than once then the user did not enter a number inside of the range. 
	do
	{
		if (inputError)						//Checks if the loop has executed more than once and prints a error message if they have. 
		{
			cout << "The number entered is not in the range of " << MENU_MIN << " and " << MENU_MAX << ".\n\n";
		}
		inputError = true;					//Since the check is before this statement any execution of the loop after this one will cause the check to print an error message. 
		cout << "Which operation would you like to perform?\n";
		menuItems();						//Calls menuItems() function. The menuItems() function is used to display the menu items. 

		cout << "\nEnter the number next to the operation you would like to perform: ";
		cin >> menuNum;

	} while (menuNum < MENU_MIN || menuNum > MENU_MAX);

	switch (menuNum)
	{
	case 1:
		opName = "addition";
		cout << "You have chosen " << opName << ".\n";
		numNums("added", 2, UINT_MAX);
		op = " + ";
		typeMenu();
		add(typeNum);
		break;
	case 2:
		opName = "subtraction";
		cout << "You have chosen " << opName << ".\n";
		numNums("subtracted", 2, UINT_MAX);
		op = " - ";
		typeMenu();
		subtract(typeNum);
		break;
	case 3:
		opName = "multiplication";
		cout << "You have chosen " << opName << ".\n";
		numNums("multiplied", 2, UINT_MAX);
		op = " * ";
		typeMenu();
		multiply(typeNum);
		break;
	case 4:
		opName = "division";
		cout << "You have chosen " << opName << ".\n";
		numNums("divided", 2, UINT_MAX);
		op = " / ";
		typeMenu();
		divide(typeNum);
		break;
	case 5:
		opName = "modulus";
		cout << "You have chosen " << opName << ".\n";
		numNums("computed", 2, UINT_MAX);
		op = " % ";
		typeMenu();
		modulo(typeNum);
		break;
	case 6:
		//Returns a value of false on the instance that the user entered the corresponding menu number for quit. 
		return false;
	default: cout << "\nThe number is not within the correct range.\n(Located within the menu function.)\n";
	}
	return true;
}

//Outputs the items listed on the menu and the range the user needs to input. 
void menuItems()
{
	for (unsigned int i = 0; i < vectorMenuItems.size(); i++)
	{
		cout << (i + 1) << ":\t" << vectorMenuItems[i] << "\n";
	}
}


void numNums(string s, const long long MIN, const long long MAX)
{
	long long inputNumber;
	//cout << "MIN:\t" << MIN << "\tMAX:\t" << MAX << "\n";
	cout << "\nHow many numbers do you want " << s << "?\n";
	cin >> inputNumber;
	while (inputNumber < MIN || inputNumber > MAX)
	{
		cout << "Please enter a whole number between " << (MIN) << " and " << (MAX) << ".\n";
		cin >> inputNumber;
	}
	numNum = inputNumber;
}

void typeMenu()
{
	const int MENU_MIN = 1;
	const int MENU_MAX = 3;
	int c = 0;
	do
	{
		if (c++ != 0) {
			cout << "The number entered is not in the range of " << MENU_MIN << " and " << MENU_MAX << ".\n\n";
		}
		cout << "Which type of variables are you entering?\n";
		cout << "1:\tint\n";
		cout << "2:\tdouble\n";
		cout << "3:\tfloat\n";
		cout << "\nEnter a number between " << MENU_MIN << " and " << MENU_MAX << ". (Inclusive)\n";
		cin >> typeNum;
	} while (typeNum < MENU_MIN || typeNum > MENU_MAX);

	switch (typeNum)
	{
	case 1:
		vectorInt = vector<int>(numNum, 0);
		typeName = "int";
		break;
	case 2:
		vectorDouble = vector<double>(numNum, 0.0);
		typeName = "double";
		break;
	case 3:
		vectorFloat = vector<float>(numNum, 0.0F);
		typeName = "float";
		break;
	default: cout << "\nThe number is not within the correct range.\nLocated within the typeMenu function.\n";
	}

	in(typeNum, "\nEnter number ");
}

void menuLoop()
{
	cout << "\n\n\n\n\n\n\n\nWould you like to do another calculation?\n\nEnter 'Y' or 'y' to continue. Enter anything else to exit.\n";
	cin.ignore();

	string prompt;
	getline(cin, prompt);

	cout << "prompt: " << prompt << "\n";							//Uncomment to debug the repeat program string input. 

	bool temp1 = (prompt == "Y");									//Sets boolean temp1 to the answer of: Is the user inputted string equal to the string "Y" //Did the user input "Y"
	bool temp2 = (prompt == "y");									//Sets boolean temp2 to the answer of: Is the user inputted string equal to the string "y" //Did the user input "y"

	cout << "temp1: " << temp1 << "\ttemp2: " << temp2 << "\n";	//Uncomment to debug the repeat program boolean check. 

	if (temp1 == false && temp2 == false)							//Checks if temp1 == false or temp2 == false //Used to stop the loop if the user does not inout either "Y" or "y"
	{
		bMenuLoop = false;
	}
	cout << "Boolean bMenuLoop: " << bMenuLoop << endl;			//Uncomment to debug the result of this function. 
}

//Calculation functions 

//Clear answer data function
void clearAnswer(int a, double b, float c)
{
	answerInt = a;
	answerDouble = b;
	answerFloat = c;
}

//Add function
void add(int t)
{
	clearAnswer();
	switch (t)
	{
	case 1:
		for (unsigned int i = 0; i < vectorInt.size(); i++)
		{
			if (i == 0)
			{
				answerInt = vectorInt[0];
			}
			else
			{
				answerInt += vectorInt[i];
			}
		}
		break;
	case 2:
		for (unsigned int d = 0; d < vectorDouble.size(); d++)
		{
			if (d == 0)
			{
				answerDouble = vectorDouble[0];
			}
			else
			{
				answerDouble += vectorDouble[d];
			}
		}
		break;
	case 3:
		for (unsigned int f = 0; f < vectorFloat.size(); f++)
		{
			if (f == 0)
			{
				answerFloat = vectorFloat[0];
			}
			else
			{
				answerFloat += vectorFloat[f];
			}
		}
		break;
	default: cout << "\nThe number is not within the correct range.\nLocated within the add function.\n";
	}
}

//Subtract function
void subtract(int t)
{
	//Inefficient way to make writing this easier. In the end this takes two times the first number and subtracts it from itself just to keep from writing 5 more lines. 

	switch (t)
	{
	case 1:
		for (unsigned int i = 1; i < vectorInt.size(); i++)
		{
			vectorInt[i] = -1 * vectorInt[i];
		}
		add(t);
		break;
	case 2:
		for (unsigned int d = 1; d < vectorDouble.size(); d++)
		{
			vectorDouble[d] = -1 * vectorDouble[d];
		}
		add(t);
		break;
	case 3:
		for (unsigned int f = 1; f < vectorFloat.size(); f++)
		{
			vectorFloat[f] = -1 * vectorFloat[f];
		}
		add(t);
		break;
	default: cout << "\nThe number is not within the correct range.\nLocated within the subtract function.\n";
	}
}

//Multiply function
void multiply(int t)
{
	clearAnswer();

	switch (t)
	{
	case 1:

		for (unsigned int i = 0; i < vectorInt.size(); i++)
		{
			if (i == 0)
			{
				answerInt = vectorInt[0];
			}
			else
			{
				answerInt *= vectorInt[i];
			}
		}
		break;
	case 2:
		for (unsigned int d = 0; d < vectorDouble.size(); d++)
		{
			if (d == 0)
			{
				answerDouble = vectorDouble[0];
			}
			else
			{
				answerDouble *= vectorDouble[d];
			}
		}
		break;
	case 3:
		for (unsigned int f = 0; f < vectorFloat.size(); f++)
		{
			if (f == 0)
			{
				answerFloat = vectorFloat[0];
			}
			else
			{
				answerFloat *= vectorFloat[f];
			}
		}
		break;
	default: cout << "\nThe number is not within the correct range.\nLocated within the multiply function.\n";
	}
}

//Divide function
void divide(int t)
{
	clearAnswer();

	switch (t)
	{
	case 1:

		for (unsigned int i = 0; i < vectorInt.size(); i++)
		{
			if (i == 0)
			{
				answerInt = vectorInt[0];
			}
			else
			{
				answerInt /= vectorInt[i];
			}
		}
		break;
	case 2:

		for (unsigned int d = 0; d < vectorDouble.size(); d++)
		{
			if (d == 0)
			{
				answerDouble = vectorDouble[0];
			}
			else
			{
				answerDouble /= vectorDouble[d];
			}
		}
		break;
	case 3:
		for (unsigned int f = 0; f < vectorFloat.size(); f++)
		{
			if (f == 0)
			{
				answerFloat = vectorFloat[0];
			}
			else
			{
				answerFloat /= vectorFloat[f];
			}
		}
		break;
	default: cout << "\nThe number is not within the correct range.\nLocated within the divide function.\n";
	}
}

//Modulo function
void modulo(int t)
{
	clearAnswer();

	switch (t)
	{
	case 1:

		for (unsigned int i = 0; i < vectorInt.size(); i++)
		{
			if (i == 0)
			{
				answerInt = vectorInt[0];
			}
			else
			{
				answerInt %= vectorInt[i];
			}
		}

		break;
	case 2:

		for (unsigned int d = 0; d < vectorDouble.size(); d++)
		{
			if (d == 0)
			{
				answerDouble = vectorDouble[0];
			}
			else
			{
				answerDouble = remainder(answerDouble, vectorDouble[d]);
			}
		}
		break;
	case 3:
		for (unsigned int f = 0; f < vectorFloat.size(); f++)
		{
			if (f == 0)
			{
				answerFloat = vectorFloat[0];
			}
			else
			{
				answerFloat = remainder(answerFloat, vectorFloat[f]);
			}
		}
		break;
	default: cout << "\nThe number is not within the correct range.\nLocated within the modulus function.\n";
	}
}


//Input functions 

void in(int t, string s)
{
	for (unsigned int counter = 0; counter < numNum; counter++)
	{
		in(t, counter, s);
	}
}
void in(int t, int c, string s)
{
	cout << s << c + 1 << ": ";
	switch (t)
	{
	case 1:
		cin >> vectorInt[c];
		break;
	case 2:
		cin >> vectorDouble[c];
		break;
	case 3:
		cin >> vectorFloat[c];
		break;
	default: cout << "\nThe number is not within the correct range.\nLocated within the overloaded \"in\" function.\n";
	}
}

//Output functions 
void out()
{
	//bool fileOutput = false;
	fstream calcOut;


	if (fileOutput)
	{
		string s = "";
		s = return_current_time_and_date();


		stemp = stringstream(""); stemp << "s: " << s << "\n";
		/*
		for (char &c : s)
		{
			if (c == 58)
			{
				c = 45;
			}
		}
		*/

		string filename = "";
		stringstream file = stringstream(filename);
		file << "output-" << s << ".txt";
		filename = file.str();
		stemp = stringstream(""); stemp << "Filename: " << filename << "\n";

		//Creates the filestream that is used for output. 

		calcOut.open(filename, std::fstream::out | std::fstream::app);
		stemp = stringstream(""); stemp << "calcOut.is_open():\t" << calcOut.is_open() << "\n";
	}
	if (fileOutput)
	{
		switch (typeNum)
		{
		case 1:
			calcOut << "\nposition:\t";
			for (unsigned int i = 0; i < vectorInt.size(); i++)
			{
				calcOut << "\t" << i;
			}
			calcOut << "\nvectorInt:\t";
			for (unsigned int i = 0; i < vectorInt.size(); i++)
			{
				calcOut << "\t" << vectorInt[i];
			}
			break;
		case 2:
			calcOut << "\nposition:\t";
			for (unsigned int d = 0; d < vectorDouble.size(); d++)
			{
				calcOut << "\t" << d;
			}
			calcOut << "\nvectorDouble:\n";
			for (unsigned int d = 0; d < vectorDouble.size(); d++)
			{
				calcOut << "\t" << vectorDouble[d];
			}
			break;
		case 3:
			calcOut << "\nposition:\t";
			for (unsigned int f = 0; f < vectorDouble.size(); f++)
			{
				calcOut << "\t" << f;
			}
			calcOut << "\nvectorFloat:\n";
			for (unsigned int f = 0; f < vectorDouble.size(); f++)
			{
				calcOut << "\t" << vectorFloat[f];
			}
			break;
		}
		calcOut << "\n\n";








		//Main text section
		calcOut << vectorOutput[0] << opName << vectorOutput[2] << vectorOutput[3] << typeName
			<< vectorOutput[5] << vectorOutput[6] << numNum << vectorOutput[8] << vectorOutput[9];

		//Equation section
		switch (typeNum)
		{
		case 1:
			for (unsigned int counter = 0; counter < numNum; counter++)
			{
				if (counter != 0)
				{
					calcOut << op << abs(vectorInt[counter]);
				}
				else
				{
					calcOut << vectorInt[0];
				}
			}
			break;
		case 2:
			for (unsigned int counter = 0; counter < numNum; counter++)
			{
				if (counter != 0)
				{
					calcOut << op << abs(vectorDouble[counter]);
				}
				else
				{
					calcOut << vectorDouble[0];
				}
			}
			break;
		case 3:
			for (unsigned int counter = 0; counter < numNum; counter++)
			{
				if (counter != 0)
				{
					calcOut << op << abs(vectorFloat[counter]);
				}
				else
				{
					calcOut << vectorFloat[0];
				}
			}
			break;
		default: calcOut << "\nThe number is not within the correct range.\nLocated within the equation section of the \"out\" function.\n";
		}

		//More text
		calcOut << vectorOutput[11] << vectorOutput[12];

		//Result section
		switch (typeNum)
		{
		case 1:
			calcOut << answerInt << "\n\n";
			break;
		case 2:
			calcOut << answerDouble << "\n\n";
			break;
		case 3:
			calcOut << answerFloat << "\n\n";
			break;
		default: calcOut << "\nThe number is not within the correct range.\nLocated within the result section of the \"out\" function.\n";
		}

		calcOut.close();
	}
	else
	{
		cout << "\n\n";
		switch (typeNum)
		{
		case 1:
			cout << "\nposition:\t";
			for (unsigned int i = 0; i < vectorInt.size(); i++)
			{
				cout << "\t" << i;
			}
			cout << "\nvectorInt:\t";
			for (unsigned int i = 0; i < vectorInt.size(); i++)
			{
				cout << "\t" << vectorInt[i];
			}
			break;
		case 2:
			cout << "\nposition:\t";
			for (unsigned int d = 0; d < vectorDouble.size(); d++)
			{
				cout << "\t" << d;
			}
			cout << "\nvectorDouble:\n";
			for (unsigned int d = 0; d < vectorDouble.size(); d++)
			{
				cout << "\t" << vectorDouble[d];
			}
			break;
		case 3:
			cout << "\nposition:\t";
			for (unsigned int f = 0; f < vectorDouble.size(); f++)
			{
				cout << "\t" << f;
			}
			cout << "\nvectorFloat:\n";
			for (unsigned int f = 0; f < vectorDouble.size(); f++)
			{
				cout << "\t" << vectorFloat[f];
			}
			break;
		}
		cout << "\n\n";








		//Main text section
		cout << vectorOutput[0] << opName << vectorOutput[2] << vectorOutput[3] << typeName
			<< vectorOutput[5] << vectorOutput[6] << numNum << vectorOutput[8] << vectorOutput[9];

		//Equation section
		switch (typeNum)
		{
		case 1:
			for (unsigned int counter = 0; counter < numNum; counter++)
			{
				if (counter != 0)
				{
					cout << op << abs(vectorInt[counter]);
				}
				else
				{
					cout << vectorInt[0];
				}
			}
			break;
		case 2:
			for (unsigned int counter = 0; counter < numNum; counter++)
			{
				if (counter != 0)
				{
					cout << op << abs(vectorDouble[counter]);
				}
				else
				{
					cout << vectorDouble[0];
				}
			}
			break;
		case 3:
			for (unsigned int counter = 0; counter < numNum; counter++)
			{
				if (counter != 0)
				{
					cout << op << abs(vectorFloat[counter]);
				}
				else
				{
					cout << vectorFloat[0];
				}
			}
			break;
		default: cout << "\nThe number is not within the correct range.\nLocated within the equation section of the \"out\" function.\n";
		}

		//More text
		cout << vectorOutput[11] << vectorOutput[12];

		//Result section
		switch (typeNum)
		{
		case 1:
			cout << answerInt << "\n\n";
			break;
		case 2:
			cout << answerDouble << "\n\n";
			break;
		case 3:
			cout << answerFloat << "\n\n";
			break;
		default: cout << "\nThe number is not within the correct range.\nLocated within the result section of the \"out\" function.\n";
		}
	}

}

std::string return_current_time_and_date() {
	using namespace std::chrono;
	errno_t err;

	system_clock::time_point today = system_clock::now();
	time_t tt = system_clock::to_time_t(today);
	struct tm timeinfo;
	err = localtime_s(&timeinfo, &tt);
	if (err)
	{
		printf("Invalid argument to _localtime_s.");
		exit(1);
	}
	string outString = "";
	stringstream ss;
	char buffer[256];

	//ctime_s(buffer, sizeof buffer, &tt);
	strftime(buffer, sizeof buffer, "%a, %b %d, %Y___%H-%M-%S_%Z", &timeinfo);
	puts(buffer);

	for (char &c : buffer)
	{
		if (c == ':')
		{
			c = '-';
		}
		/*
		if (c == ' ')
		{
			c = '_';
		}
		*/
	}

	ss << buffer;
	//cout << "ss:\t" << ss.str() << "\n";

	outString = ss.str();
	//cout << "outString:\t" << outString << "\n";

	return outString;
}

void end()
{
	for (unsigned int count = 0; count < /*100*/2; count++) { cout << "\n"; }			//Output new lines to clear the screen
	cout << "\n\nThank you for using this experimental calculator.\nIf you encounter any problems please contact me by email.\nEmail: brian.elliott406@my.tccd.edu\n\n";
}