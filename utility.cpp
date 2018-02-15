//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	utility.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#include "utility.h"
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "lib_val.h"

#include <string>
#include <iostream>
#include <stdexcept>
#include <iomanip>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	PauseAndReturn()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int UtilityFunctions::PauseAndReturn()
{
    char quit = '\0';
    while (quit != 'q')
    {
        std::cout << "Enter q to quit: ";
        std::cin >> quit;
    }

    return 0;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	PauseAndContinue()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::PauseAndContinue()
{
    std::cout << "Press return to continue";
	std::cin.get();
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	bool UtilityFunctions::do_again()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool UtilityFunctions::do_again()
{
	std::cout << std::endl;
	char input = '\0';
    
	std::cout << "Enter r to run again,  anything else to quit: ";
    
	std::cin >> input;
    
	std::cout << std::endl << std::endl;
	
    return input == 'r';
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	sign()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long UtilityFunctions::sign(double x)
{
	 if (x >= 0 ) return 1;
	 return -1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX     char functions
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

char UtilityFunctions::GetChar(const char * str)
{
    std::cout << std::endl << str << " = ";
    char d;
    std::cin >> d;

    return d;
}

char UtilityFunctions::get_char_in_range(const std::string & mess, const std::string & valid_chars)
{
	std::string input = "\0";

	while (!ut::check_char(input, valid_chars)) input = GetString(mess);

	return input[0];
}

std::string UtilityFunctions::DecorateString(const std::string & label)
{
	const static long max_length = 24;

	std::string lab = label + ":";
	lab.resize(max_length);
    return lab;
}

bool UtilityFunctions::check_char(const std::string & x, const std::string & valid_chars)
{
    if (x.size() != 1) return false;

    return valid_chars.find(x) != std::string::npos;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	GetString()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

std::string UtilityFunctions::GetString(std::istream & in)
{
	std::string text;
    if (!(in >> text)) throw std::runtime_error("ut::GetString:  Bad string");
    return text;
}

std::string UtilityFunctions::GetString(std::istream & in, const std::string & mess)
{
    std::cout << std::endl << mess + ":  ";

	std::string text;
    if (!(in >> text)) throw std::runtime_error("ut::GetString:  Bad string");
    return text;
}

std::string UtilityFunctions::GetString(const char * mess)
{
    std::cout << std::endl << mess << ":  ";

	std::string text;
    std::getline(std::cin, text);
    return text;
}

std::string UtilityFunctions::GetString(const std::string & mess)
{
    std::cout << std::endl << mess + ":  ";

	std::string text;
    std::getline(std::cin, text);
    return text;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	GetDouble()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double UtilityFunctions::GetDouble(std::istream & in)
{
	double num;
    if (!(in >> num)) throw std::runtime_error("ut::GetDouble:  Bad double");
	return num;
}

double UtilityFunctions::GetDouble(const std::string & prompt)
{
	bool valid_input = false;
	double value;
	
	while (!valid_input)
	{
		std::string input = GetString(prompt);
 		value = lv::StringToDouble(input, valid_input);
	}

	return value;
}

double UtilityFunctions::GetDouble(std::istream & in, const std::string & prompt)
{
	bool valid_input = false;
	double value;

	while (!valid_input)
	{
		std::string input = GetString(in, prompt);
 		value = lv::StringToDouble(input, valid_input);
	}

	return value;
}

double UtilityFunctions::GetDouble(char * prompt)
{
	bool valid_input = false;
	double value;

	while (!valid_input)
	{
		std::string input = GetString(prompt);
 		value = lv::StringToDouble(input, valid_input);
	}

	return value;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	GetLong()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long UtilityFunctions::GetLong(std::istream & in)
{
	long num;
    if (!(in >> num)) throw std::runtime_error("ut::GetLong:  Bad long");
	return num;
}

long UtilityFunctions::GetLong(const std::string & prompt)
{
	bool valid_input = false;
	long value;
	
	while (valid_input == false)
	{
		std::string input = GetString(prompt);
 		value = lv::StringToLong(input, valid_input);
	}

	return value;
}

long UtilityFunctions::GetLong(std::istream & in, const std::string & prompt)
{
	bool valid_input = false;
	long value;

	while (valid_input == false)
	{
		std::string input = GetString(in, prompt);
 		value = lv::StringToLong(input, valid_input);
	}

	return value;
}

long UtilityFunctions::GetLong(const char * str)
{
	bool valid_input = false;
	long value;

	while (valid_input == false)
	{
		std::string input = GetString(str);
 		value = lv::StringToLong(input, valid_input);
	}

	return value;
}

long UtilityFunctions::GetLongInRange(const std::string & prompt, long l, long u)
{
	if (u < l) throw std::runtime_error("GetLongInRange: incorrect range");

	long val;
	bool valid_index = false;

	while (!valid_index)
	{
		val = ut::GetLong(prompt);
		if (val >= l && val <= u)
		{
			valid_index = true;
		}
		else
		{
			ut::OutputLine("Not in range");
		}
	}
    return val;
}

long UtilityFunctions::GetPositiveLong(const std::string & prompt)
{
	bool valid_input = false;
	long value;

	while (valid_input == false)
	{
		std::string input = GetString(prompt);
 		value = lv::StringToLong(input, valid_input);
 		if (value <= 0)
        {
            valid_input = false;
            ut::OutputLine("Require positive input");
        }
	}

	return value;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	GetBool
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool UtilityFunctions::GetBool(std::istream & in)
{
	std::string text;
    if (!(in >> text)) throw std::runtime_error("ut::GetString:  Bad string");

    return lv::StringToBool(text);
}

bool UtilityFunctions::GetBool(const std::string & prompt)
{
	bool valid_input = false;
	bool value;

	while (valid_input == false)
	{
		std::string input = GetString(prompt);
 		value = lv::StringToBool(input, valid_input);
	}

	return value;
}

bool UtilityFunctions::GetBool(std::istream & in, const std::string & prompt)
{
	bool valid_input = false;
	bool value;

	while (valid_input == false)
	{
		std::string input = GetString(in, prompt);
 		value = lv::StringToBool(input, valid_input);
	}

	return value;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Putters
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputLine(std::ostream & out, const std::string & text)
{
    out << text << std::endl;
}

void UtilityFunctions::OutputLine(std::ostream & out, const std::string & text, const double & num)
{
    out << text << " " << num << std::endl;
}

void UtilityFunctions::OutputLine(std::ostream & out, const std::string & text, const double & num1, const double & num2)
{
    out << text << " " << num1 << " " << num2 << std::endl;
}

void UtilityFunctions::OutputLine(std::ostream & out, const std::string & text, const double & num1, const double & num2, const double & num3)
{
    out << text << " " << num1 << " " << num2 << " " << num3 << std::endl;
}

void UtilityFunctions::OutputLine(std::ostream & out, const double & num1, const double & num2)
{
    out << num1 << " " << num2 << std::endl;
}

void UtilityFunctions::OutputLine(std::ostream & out, const double & num1, const double & num2, const double & num3)
{
    out << num1 << " " << num2 << " " << num3 << std::endl;
}

void UtilityFunctions::OutputLine()
{
    std::cout << std::endl;
}

void UtilityFunctions::OutputLine(const std::string & text)
{
    std::cout << text << std::endl;
}

void UtilityFunctions::OutputLine(const std::string & text, const double & num)
{
    std::cout << text << " " << num << std::endl;
}

void UtilityFunctions::OutputLine(const std::string & t1, const std::string & t2)
{
    std::cout << t1 << " " << t2 << std::endl;
}

void UtilityFunctions::OutputLine(const std::string & text, const double & num, const long & prec)
{
    std::cout << std::setprecision(prec) << text << " " << num << std::endl;
}

void UtilityFunctions::OutputLine(const std::string & a , const long & i , const std::string & b , const std::string & c)
{
    std::cout << a << i << b << c << std::endl;
}

void UtilityFunctions::OutputLine(const long & a, const long & b)
{
    std::cout << a << " " << b << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void OutputDouble();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputDouble(const std::string & str, const double & c)
{
    std::cout << std::setprecision(12) << str << " = " << c << std::endl;
}

void UtilityFunctions::OutputDouble(const char * str, const double & c)
{
    std::cout << std::setprecision(12) << str << " = " << c << std::endl;
}

void UtilityFunctions::OutputDouble(const double & c)
{
    std::cout << std::setprecision(12) << c << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void OutputLong(const long & c, const long & w);
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputLong(const long & c, const long & w)
{
    std::cout << std::setw(w) << c;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void OutputLongSequence();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputLongSequence(const long & d1, const long & d2)
{
     for(long i = d1; i <= d2; ++i)
     {
         std::cout << std::setw(9) << i;
     }
     std::cout << std::endl;    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void OutputLongRow();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputLongRow(long ** mat, long & d1, long & d2, long & i)
{
     for(long j = 0; j < d2; ++j)
     {
         std::cout << std::setw(9) << mat[i][j];
     }
     std::cout << std::endl;    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void OutputLongRow();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputSlice(long *** mat, const long & d1, const long & d2, const long & d3, const long & i)
{
     for(long j = 0; j < d1; ++j)
     {
         for(long k = 0; k < d2; ++k)
         {
             std::cout << std::setw(9) << mat[j][k][i];
         }
         std::cout << std::endl;
     }
     std::cout << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void OutputDoubleRow();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputDoubleRow(double ** mat, long & d1, long & d2, long & i)
{
     for(long j = 0; j < d1; ++j)
     {
         std::cout << std::setw(9) << mat[i][j];
     }
     std::cout << std::endl;    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void OutputLongMatrix();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputLongMatrix(long ** mat, long & d1, long & d2)
{
     for(long i = 0; i < d1; ++i)
     {
         ut::OutputLongRow(mat, d1, d2, i);
     }  
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void OutputDoubleMatrix();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputDoubleMatrix(double ** mat, long & d1, long & d2)
{
     for(long i = 0; i < d1; ++i)
     {
         for(long j = 0; j < d2; ++j)
         {
             std::cout << std:: setw(12) << mat[i][j] << " ";
         }
         std::cout << std::endl;
     }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	void OutputDoubleMatrixCoords();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputDoubleMatrixCoords(double ** mat, long & d1, long & d2)
{
     std::cout << std::setw(9) << "";
     ut::OutputLongSequence(1, d2);
     
     for(long i = 0; i < d1; ++i)
     {
         std::cout << std::setw(9) << i+1;
         ut::OutputDoubleRow(mat, d1, d2, i);
     }  
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	OutputCounter();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::OutputCounter(long i, long N, long OutputStepInterval)
{
	if (0 == i%OutputStepInterval) std::cout <<  "..." << i;

	if (i == N) std::cout <<  "..." << i << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	ReachedHere();
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void UtilityFunctions::ReachedHere(long i)
{
	std::cout <<  "Reached here:  " << i << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
