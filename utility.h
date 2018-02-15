//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  utility.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef utilityH
#define utilityH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <iostream>
#include <string>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  namespace UtilityFunctions
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

namespace UtilityFunctions
{
	int PauseAndReturn();
	void PauseAndContinue();

	bool do_again();

	long sign(double x);

	char GetChar(const char * str);

	std::string DecorateString(const std::string &);
	char get_char_in_range(const std::string &, const std::string &);
	bool check_char(const std::string &, const std::string &);

	std::string GetString(std::istream &);
	std::string GetString(std::istream &, const std::string &);
	std::string GetString(const std::string &);
	std::string GetString(const char *);

	double GetDouble(std::istream &);
	double GetDouble(const std::string &);
	double GetDouble(std::istream &, const std::string &);
	double GetDouble(char * str);

	long GetLong(std::istream &);
	long GetLong(const std::string &);
	long GetLong(std::istream &, const std::string &);
	long GetLongInRange(const std::string &, long l, long u);
	long GetLong(const char * str);

	long GetPositiveLong(const std::string & prompt);

	bool GetBool(std::istream &);
	bool GetBool(const std::string &);
	bool GetBool(std::istream &, const std::string &);

	void OutputLine(std::ostream &, const std::string &);
	void OutputLine(std::ostream &, const std::string &, const double &);
	void OutputLine(std::ostream &, const std::string &, const double &, const double &);
	void OutputLine(std::ostream &, const std::string &, const double &, const double &, const double &);
	void OutputLine(std::ostream &, const double &, const double &);
	void OutputLine(std::ostream &, const double &, const double &, const double &);
	void OutputLine();
	void OutputLine(const std::string &);
	void OutputLine(const std::string &, const std::string &);
	void OutputLine(const std::string &, const double &);
	void OutputLine(const std::string &, const double &, const long &);
	void OutputLine(const std::string &, const long &, const std::string &, const std::string &);
	void OutputLine(const long &, const long &);

	void OutputDouble(const std::string & str, const double & c);
	void OutputDouble(const char * str, const double & c);
	void OutputDouble(const double & c);
	
    void OutputLong(const long & c, const long & w);
    void OutputLongSequence(const long & d1, const long & d2);
    void OutputSlice(long *** mat, const long & d1, const long & d2, const long & d3, const long & i);

    void OutputLongRow(long ** mat, long & d1, long & d2, long & i);
    void OutputLongMatrix(long ** mat, long & d1, long & d2);
    void OutputLongMatrixCoords(long ** mat, long & d1, long & d2);
    
    void OutputDoubleRow(double ** mat, long & d1, long & d2, long & i);
    void OutputDoubleMatrix(double ** mat, long & d1, long & d2);
    void OutputDoubleMatrixCoords(double ** mat, long & d1, long & d2);

    void OutputCounter(long i, long N, long OutputStepInterval);
    
    void ReachedHere(long i);
}

namespace ut = UtilityFunctions;    //alias

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
